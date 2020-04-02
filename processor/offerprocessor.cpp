#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
//
#include "commondef.h"
#include "offerprocessor.h"
#include "offerskillprocesor.h"
#include "dto/offerbasedto.h"
#include "dbsupport/dbacccesssafe.h"
//
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
#include "config/configdef.h"


OfferProcessor::OfferProcessor(QObject *parent) : QObject(parent)
{
    m_ptrLog = nullptr;
}

OfferProcessor& OfferProcessor::getInstance(){
    static OfferProcessor processor;
    return processor;
}
//
bool OfferProcessor::init(){
    m_ptrLog = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    bool b_res = readAllFromDB();
    return b_res;
}

int OfferProcessor::add(OfferBaseDTO* pos_description){
    //
    if(nullptr == pos_description){
        return VALUE_UNDEFINED;
    };
    //
    //search existing
    OfferStorage::const_iterator i = m_mapStorage.find(pos_description->getId());
    //
    if (i != m_mapStorage.constEnd()){
        return pos_description->getId(); //already exists;
    };
    //if not exists - add new one.
    int i_insert_id = insertIntoDB(pos_description);
    return i_insert_id;
}

int OfferProcessor::insertIntoDB(OfferBaseDTO* pos_description){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_fields        = QString("(creation_date, pos_title, description, comments, id_country, id_town, id_agent, id_status, attractivity, rate)");
    const QString str_bind_values   = QString("(:CREATION_DATE, :POS_TITLE, :DESCRIPTION, :COMMENTS, :ID_COUNTRY, :ID_TOWN, :ID_AGENT, :ID_STATUS, :ID_ATTRACTIVITY, :RATE)");
    const QString str_insert_string = QString("INSERT INTO offers_tbl %1 values %2;").arg(str_fields).arg(str_bind_values);
    //
    if( !qry.prepare( str_insert_string ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":CREATION_DATE", pos_description->getCreationDate());
    qry.bindValue(":POS_TITLE", pos_description->getPositionTitle());
    qry.bindValue(":DESCRIPTION", pos_description->getDescription());
    qry.bindValue(":COMMENTS", pos_description->getComments());
    qry.bindValue(":ID_COUNTRY", pos_description->getCountryId());
    qry.bindValue(":ID_TOWN", pos_description->getTownId());
    qry.bindValue(":ID_AGENT", pos_description->getAgentId());
    qry.bindValue(":ID_STATUS", pos_description->getStatusId());
    qry.bindValue(":ID_ATTRACTIVITY", pos_description->getAttractivity());
    qry.bindValue(":RATE", pos_description->getRate());
    //
    if( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    int i_last_id = qry.lastInsertId().toInt();
    //
    addNewValueToStorage(i_last_id,
                         pos_description->getCreationDate(),
                         pos_description->getPositionTitle(),
                         pos_description->getDescription(),
                         pos_description->getComments(),
                         pos_description->getCountryId(),
                         pos_description->getTownId(),
                         pos_description->getAgentId(),
                         pos_description->getStatusId(),
                         pos_description->getAttractivity(),
                         pos_description->getRate());
    //
    //OfferSkillProcesor::getInstance().add(i_last_id, pos_description->getSkillsListIDs());
    //
    return i_last_id;
}

bool OfferProcessor::readAllFromDB(){
    bool b_res = true;
    m_mapStorage.clear();
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_query = QString("select id, creation_date, pos_title, description, comments, id_country, id_town, id_agent, id_status, attractivity, rate from offers_tbl;");
    //
    if ( !qry.prepare( str_query ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_query).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        b_res = false;
    };
    //
    if( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_query).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        b_res = false;
    };
    //
    while( qry.next() )
    {
        addNewValueToStorage(qry.value(0).toInt(),      //id
                             qry.value(1).toDate(),     //creation_date
                             qry.value(2).toString(),   //pos_title
                             qry.value(3).toString(),   //description
                             qry.value(4).toString(),   //comments
                             qry.value(5).toInt(),      //id_country
                             qry.value(6).toInt(),      //id_town
                             qry.value(7).toInt(),      //id_agent
                             qry.value(8).toInt(),      //id_status
                             qry.value(9).toInt(),      //attractivity
                             qry.value(10).toInt());     //rate
    };
    //
    return b_res;
}

void OfferProcessor::addNewValueToStorage(int i_id,                             //0
                                          const QDate& d_creation_date,         //1
                                          const QString& str_pos_title,         //2
                                          const QString &str_pos_decription,    //3
                                          const QString &str_pos_comments,      //4
                                          int i_id_country,                     //5
                                          int i_id_town,                        //6
                                          int i_id_agent,                       //7
                                          int i_id_status,                      //8
                                          int i_attractivity,                   //9
                                          int i_rate){                          //10
    OfferBaseDTO* ptr_offer = new OfferBaseDTO() ;
    ptr_offer->setId(i_id);
    ptr_offer->setCreationDate(d_creation_date);
    ptr_offer->setPositionTitle(str_pos_title);
    ptr_offer->setDescription(str_pos_decription);
    ptr_offer->setComments(str_pos_comments);
    ptr_offer->setCountryId(i_id_country);
    ptr_offer->setTownId(i_id_town);
    ptr_offer->setAgentId(i_id_agent);
    ptr_offer->setStatusId(i_id_status);
    ptr_offer->setAttractivity(i_attractivity);
    ptr_offer->setRate(i_rate);
    //
    m_mapStorage.insert(i_id, ptr_offer);
}

const OfferStorage& OfferProcessor::getStorage() const{
    return m_mapStorage;
}

bool OfferProcessor::updateTown(int i_offer_id, int i_town_id){
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET id_town = %1 WHERE id = %2;").arg(i_town_id).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setTownId(i_town_id);
    };
    //
    return true;
}

bool OfferProcessor::updateCountry(int i_offer_id, int i_country_id){
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET id_country = %1 WHERE id = %2;").arg(i_country_id).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setCountryId(i_country_id);
    };
    //
    return true;
}

bool OfferProcessor::updatePositionTitle(int i_offer_id, const QString& str_position_title){
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET pos_title = '%1' WHERE id = %2;").arg(str_position_title).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setPositionTitle(str_position_title);
    };
    //
    return true;
}


bool OfferProcessor::updateComment(int i_offer_id, const QString& str_comment){
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET comments = '%1' WHERE id = %2;").arg(str_comment).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setComments(str_comment);
    };
    //
    return true;
}

bool OfferProcessor::updateDescription(int i_offer_id, const QString& str_descripiton){
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET description = '%1' WHERE id = %2;").arg(str_descripiton).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setDescription(str_descripiton);
    };
    //
    return true;
}

bool OfferProcessor::updateAttractivity(int i_offer_id, int i_offer_attractivity){
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET attractivity = %1 WHERE id = %2;").arg(i_offer_attractivity).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setAttractivity(i_offer_attractivity);
    };
    //
    return true;
}

bool OfferProcessor::updateOfferStatus(int i_offer_id, int i_offer_status){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET id_status = %1 WHERE id = %2;").arg(i_offer_status).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setStatusId(i_offer_status);
    };
    //
    return true;
}

bool OfferProcessor::updateRate(int i_offer_id, int i_rate){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE offers_tbl SET rate = %1 WHERE id = %2;").arg(i_rate).arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    OfferBaseDTO* ptr_offer =  this->getOfferById(i_offer_id);
    if (nullptr != ptr_offer){
        ptr_offer->setRate(i_rate);
    };
    //
    return true;
}

bool OfferProcessor::removeOffer(int i_offer_id){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("DELETE FROM offers_tbl WHERE id = %1;").arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_update_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return false;
    };
    //
    m_mapStorage.remove(i_offer_id);
    //
    return true;
}

OfferBaseDTO*  OfferProcessor::getOfferById(int i_offer_id){
    OfferBaseDTO* ptr_offer = nullptr;
    //
    OfferStorage::iterator i = m_mapStorage.find(i_offer_id);
    if (i != m_mapStorage.end()){
        ptr_offer = i.value();
    };
    //
    return ptr_offer;
}

void OfferProcessor::log(const QString& str_message) const{
    if (nullptr != m_ptrLog){
        (*m_ptrLog)<<"OfferProcessor: "<<str_message<<"\n";
    };
}

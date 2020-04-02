#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
//
#include "commondef.h"
#include "dto/agentbasedto.h"
#include "agentprocessor.h"
#include "dbsupport/dbacccesssafe.h"
//
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
#include "config/configdef.h"


AgentProcessor::AgentProcessor(QObject *parent) : QObject(parent)
{

}

AgentProcessor&  AgentProcessor::getInstance(){
    static AgentProcessor processor;
    return processor;

}

int AgentProcessor::add(AgentBaseDTO* ptr_agent_base_info_dto){
    if (nullptr == ptr_agent_base_info_dto){
        return VALUE_UNDEFINED;
    };
    //
    AgentStorage::const_iterator i = m_mapStorage.find(ptr_agent_base_info_dto->getEMail());
    if  (i != m_mapStorage.end() ){
        return i.value()->getId();
    };
    //
    int i_id = insertIntoDB(ptr_agent_base_info_dto);

    return i_id;
}


int AgentProcessor::insertIntoDB(AgentBaseDTO* ptr_agent_base_info_dto){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO agents_tbl (name, description, e_mail, phone_1, phone_2, id_agency, level, web_profile) values (:NAME, :DESCRIPTION, :EMAIL, :PHONE1, :PHONE2, :ID_AGENCY, :LEVEL, :WEB);");
    //
    if( !qry.prepare( str_insert_string ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":NAME",          ptr_agent_base_info_dto->getName());
    qry.bindValue(":DESCRIPTION",   ptr_agent_base_info_dto->getDescription());
    qry.bindValue(":EMAIL",         ptr_agent_base_info_dto->getEMail());
    qry.bindValue(":PHONE1",        ptr_agent_base_info_dto->getPhone1());
    qry.bindValue(":PHONE2",        ptr_agent_base_info_dto->getPhone2());
    qry.bindValue(":ID_AGENCY",     ptr_agent_base_info_dto->getAgencyId());
    qry.bindValue(":LEVEL",         ptr_agent_base_info_dto->getRank());
    qry.bindValue(":WEB",           ptr_agent_base_info_dto->getWebProfile());
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
                         ptr_agent_base_info_dto->getName(),
                         ptr_agent_base_info_dto->getEMail(),
                         ptr_agent_base_info_dto->getPhone1(),
                         ptr_agent_base_info_dto->getPhone2(),
                         ptr_agent_base_info_dto->getDescription(),
                         ptr_agent_base_info_dto->getAgencyId(),
                         ptr_agent_base_info_dto->getRank(),
                         ptr_agent_base_info_dto->getWebProfile());
    //
    return i_last_id;
}

bool AgentProcessor::init(){
    m_ptrLog = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    bool b_res = readAllFromDB();

    return b_res;
}

bool AgentProcessor::readAllFromDB(){
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
    const QString str_query = QString("select id, name, e_mail, phone_1, phone_2, description, id_agency, level, web_profile from agents_tbl;");
    //
    if ( !qry.prepare( str_query ) )
    {
        QMessageBox::critical(nullptr, "Error", str_query, QMessageBox::Ok);
        b_res = false;
    };
    //
    if( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_query).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        //
        b_res = false;
    };
    //
    while( qry.next() )
    {
        addNewValueToStorage(qry.value(0).toInt(),      //id
                             qry.value(1).toString(),   //name
                             qry.value(2).toString(),   //e-mail
                             qry.value(3).toString(),   //phone_1
                             qry.value(4).toString(),   //phone_2
                             qry.value(5).toString(),   //description
                             qry.value(6).toInt(),      //id_agency
                             qry.value(7).toInt(),      //level
                             qry.value(8).toString());  //web_profile
    };
    //
    return b_res;
}

void AgentProcessor::addNewValueToStorage(int id,
                                          const QString& str_name,
                                          const QString& str_email,
                                          const QString& str_phone1,
                                          const QString& str_phone2,
                                          const QString& str_description,
                                          int i_agency_id,
                                          int i_rank,
                                          const QString& str_web_profile){

    AgentBaseDTO* ptr_agent = new AgentBaseDTO();
    ptr_agent->setId(id);
    ptr_agent->setName(str_name);
    ptr_agent->setEMail(str_email);
    ptr_agent->setPhone1(str_phone1);
    ptr_agent->setPhone2(str_phone2);
    ptr_agent->setDescription(str_description);
    ptr_agent->setAgencyId(i_agency_id);
    ptr_agent->setRank(i_rank);
    ptr_agent->setWebProfile(str_web_profile);
    //
    m_mapStorage.insert(ptr_agent->getEMail(), ptr_agent);
}

bool AgentProcessor::updateRank(int i_agent_id, int i_rank){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE agents_tbl SET level = %1 WHERE id = %2;").arg(i_rank).arg(i_agent_id);
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
    AgentBaseDTO* ptr_agent = getAgentByID(i_agent_id);
    if (nullptr != ptr_agent){
        ptr_agent->setRank(i_rank);
    };
    //
    return true;
}

bool AgentProcessor::updateName(int i_agent_id, const QString& str_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE agents_tbl SET name = '%1' WHERE id = %2;").arg(str_name).arg(i_agent_id);
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
    AgentBaseDTO* ptr_agent = getAgentByID(i_agent_id);
    if (nullptr != ptr_agent){
        ptr_agent->setName(str_name);
    };
    //
    return true;
}

bool AgentProcessor::updateDecription(int i_agent_id, const QString& str_description){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE agents_tbl SET description = '%1' WHERE id = %2;").arg(str_description).arg(i_agent_id);
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
    AgentBaseDTO* ptr_agent = getAgentByID(i_agent_id);
    if (nullptr != ptr_agent){
        ptr_agent->setDescription(str_description);
    };
    //
    return true;
}

bool AgentProcessor::updatePhone(int i_agent_id, const QString& phone_number, PHONE_NUM en_phone_num){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_update_string;
    switch(en_phone_num){
    case PHONE_NUM_1:
        str_update_string = QString("UPDATE agents_tbl SET phone_1 = '%1' WHERE id = %2;").arg(phone_number).arg(i_agent_id);
        break;
    case PHONE_NUM_2:
        str_update_string = QString("UPDATE agents_tbl SET phone_2 = '%1' WHERE id = %2;").arg(phone_number).arg(i_agent_id);
        break;
    };
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
    AgentBaseDTO* ptr_agent = getAgentByID(i_agent_id);
    if (nullptr != ptr_agent){
        switch(en_phone_num){
        case PHONE_NUM_1:
            ptr_agent->setPhone1(phone_number);
            break;
        case PHONE_NUM_2:
            ptr_agent->setPhone2(phone_number);
            break;
        };
    };
    //
    return true;
}

bool AgentProcessor::updateEmail(int i_agent_id, const QString& str_email){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE agents_tbl SET e_mail = '%1' WHERE id = %2;").arg(str_email).arg(i_agent_id);
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
    AgentBaseDTO* ptr_agent = getAgentByID(i_agent_id);
    if (nullptr != ptr_agent){
        m_mapStorage.remove(ptr_agent->getEMail()); //remove old key e-mail
        ptr_agent->setEMail(str_email);             //update  e-mail
        m_mapStorage.insert(str_email, ptr_agent);  //insert new value with the new key in the storage
    }
    //
    return true;
}

bool AgentProcessor::updateWebProfile(int i_agent_id, const QString& web_profile){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE agents_tbl SET web_profile = '%1' WHERE id = %2;").arg(web_profile).arg(i_agent_id);
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
    AgentBaseDTO* ptr_agent = getAgentByID(i_agent_id);
    if (nullptr != ptr_agent){
        ptr_agent->setWebProfile(web_profile);
    }
    //
    return true;
}

AgentBaseDTO* AgentProcessor::getAgentByEmail(const QString& str_email){
    AgentBaseDTO* ptr_agent = nullptr;
    AgentStorage::iterator i = m_mapStorage.find(str_email);
    if (i != m_mapStorage.constEnd()){
        ptr_agent = i.value();
    };
    //
    return ptr_agent;
}

AgentBaseDTO* AgentProcessor::getAgentByID(int i_id) const{
    AgentBaseDTO* ptr_ret = nullptr;
    //
    AgentStorage::const_iterator i = m_mapStorage.constBegin();

    while (i != m_mapStorage.constEnd()) {

        AgentBaseDTO* ptr_agent = i.value();
        if (ptr_agent->getId() == i_id){
            ptr_ret = ptr_agent;
            break;
        };
        i++;
    };
    //
    return ptr_ret;
}

const AgentStorage& AgentProcessor::getStorage() const{
    return m_mapStorage;
}

void AgentProcessor::log(const QString& str_message) const{
    if (nullptr != m_ptrLog){
        (*m_ptrLog)<<"AgentProcessor: "<<str_message<<"\n";
    };
}

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
#include <QMapIterator>
//
#include "commondef.h"
#include "agencyprocessor.h"
#include "dbsupport/dbacccesssafe.h"
#include "dto/agencydto.h"
//
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
#include "config/configdef.h"


AgencyProcessor::AgencyProcessor(QObject *parent) : QObject(parent)
{
    m_ptrLog = nullptr;
}

AgencyProcessor& AgencyProcessor::getInstance(){
    static AgencyProcessor processor;
    return processor;
}

bool AgencyProcessor::init(){
    m_ptrLog = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    bool b_res = readAllFromDB();
    return b_res;
}

int AgencyProcessor::add(const QString& str_agency_name){
    //search existing

    QMapIterator<int, AgencyDTO*> i(m_mapStorage);
    while (i.hasNext()){
        i.next();
        AgencyDTO* ptr_agency = i.value();
        if (ptr_agency->getName().compare(str_agency_name,Qt::CaseInsensitive) == 0){
            return ptr_agency->getId();
        };
    };
    //if not exists - add new one.
    int i_res = insertIntoDB(str_agency_name);
    //
    return i_res;
}

int AgencyProcessor::insertIntoDB(const QString& str_agency_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO agencies_tbl (name) values (:NAME);");
    //
    if( !qry.prepare( str_insert_string ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":NAME", str_agency_name);
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
    addNewValueToStorage(i_last_id, str_agency_name, "");
    //
    return i_last_id;
}

bool AgencyProcessor::readAllFromDB(){
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
    const QString str_query = QString("select id, name, description from agencies_tbl;");
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
        //
        b_res = false;
    };
    //
    while( qry.next() )
    {
        addNewValueToStorage(qry.value(0).toInt(), qry.value(1).toString(), qry.value(2).toString());
    };
    //
    return b_res;
}

void AgencyProcessor::addNewValueToStorage(int id, const QString& str_name, const QString& str_description){
    AgencyDTO* ptr_agency = new AgencyDTO();
    ptr_agency->setId(id);
    ptr_agency->setName(str_name);
    ptr_agency->setDescription(str_description);
    m_mapStorage.insert(ptr_agency->getId(), ptr_agency);
}

QString AgencyProcessor::getAgencyNameByID(int i_id){
    QString str_res;
    AgencyStorage::const_iterator i = m_mapStorage.find(i_id);
    if (i != m_mapStorage.constEnd()){
        str_res = i.value()->getName();
    };
    return str_res;
}

const AgencyStorage& AgencyProcessor::getStorage() const{
    return m_mapStorage;
}

void AgencyProcessor::log(const QString& str_message) const{
    if (nullptr != m_ptrLog){
        (*m_ptrLog)<<"AgencyProcessor: "<<str_message<<"\n";
    };
}

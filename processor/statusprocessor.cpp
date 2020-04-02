#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "dbsupport/dbacccesssafe.h"
#include "commondef.h"
#include "statusprocessor.h"
#include "dto/statusdto.h"
//
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
#include "config/configdef.h"

StatusProcessor::StatusProcessor(QObject *parent) : QObject(parent)
{
    m_ptrLog = nullptr;
}

StatusProcessor& StatusProcessor::getInstance(){
    static StatusProcessor processor;
    return processor;

}

bool StatusProcessor::init(){
    m_ptrLog = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    bool b_res = readAllFromDB();
    return b_res;
}

int StatusProcessor::add(const QString& str_status_name){
    //search existing
    StatusStorage::const_iterator i = m_mapStorage.constBegin();
    while (i != m_mapStorage.constEnd()) {

        StatusDTO* ptr_status = i.value();
        if (ptr_status->getName().compare(str_status_name,Qt::CaseInsensitive) == 0){
            return ptr_status->getId();
        };
        i++;
    };
    //if not exists - add new one.
    int i_res = insertIntoDB(str_status_name);
    //
    return i_res;
}

int StatusProcessor::insertIntoDB(const QString& str_status_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO statuses_tbl (name) values (:NAME);");
    //
    if( !qry.prepare( str_insert_string ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);

        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":NAME", str_status_name);
    //
    if( !qry.exec() )
    {
        const QString str_msg_log = QString("can not execute request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return -1;
    };
    //
    int i_last_id = qry.lastInsertId().toInt();
    //
    addNewValueToStorage(i_last_id, str_status_name);
    //
    return i_last_id;
}

bool StatusProcessor::readAllFromDB(){
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
    const QString str_query = QString("select id, name from statuses_tbl;");
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
        addNewValueToStorage(qry.value(0).toInt(), qry.value(1).toString());
    };
    //
    return b_res;
}

void StatusProcessor::addNewValueToStorage(int id, const QString& str_name){

    StatusDTO* ptr_status = new StatusDTO() ;
    ptr_status->setId(id);
    ptr_status->setName(str_name);
    m_mapStorage.insert(ptr_status->getId(), ptr_status);
}

const StatusStorage& StatusProcessor::getStorage() const{
    return m_mapStorage;
}

const QString StatusProcessor::getStatusNameByID(int i_id){
    QString str_res;
    StatusStorage::const_iterator i = m_mapStorage.find(i_id);
    if (i != m_mapStorage.constEnd()){
        str_res = i.value()->getName();
    };
    return str_res;
}

void StatusProcessor::log(const QString& str_message) const{
    if (nullptr != m_ptrLog){
        (*m_ptrLog)<<"StatusProcessor: "<<str_message<<"\n";
    };
}

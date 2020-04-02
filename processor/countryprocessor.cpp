#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "dbsupport/dbacccesssafe.h"
#include "commondef.h"
#include "countryprocessor.h"
#include "dto/countrydto.h"
//
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
#include "config/configdef.h"

CountryProcessor::CountryProcessor(QObject *parent) : QObject(parent)
{
    m_ptrLog = nullptr;
}

CountryProcessor& CountryProcessor::getInstance(){
    static CountryProcessor processor;
    return processor;

}

bool CountryProcessor::init(){
    m_ptrLog = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    bool b_res = readAllFromDB();
    return b_res;
}

int CountryProcessor::add(const QString& str_country_name){
    //search existing
    int i_res = isCountryAlreadyExists(str_country_name);
    if(VALUE_UNDEFINED != i_res){
        return i_res;
    };
    //
    i_res = insertIntoDB(str_country_name);
    //
    return i_res;
}

int CountryProcessor::isCountryAlreadyExists(const QString& str_country_name){

    CountryStorage::const_iterator i = m_mapStorage.constBegin();
    while (i != m_mapStorage.constEnd()) {

        CountryDTO* ptr_country = i.value();
        if (ptr_country->getName().compare(str_country_name,Qt::CaseInsensitive) == 0){
            return ptr_country->getId();
        };
        i++;
    };
    return VALUE_UNDEFINED;
}

int CountryProcessor::insertIntoDB(const QString& str_country_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO countries_tbl (name) values (:NAME);");
    //
    if( !qry.prepare( str_insert_string ) )
    {
        const QString str_msg_log = QString("can not prepare request [%1]. Error: [%2]").arg(str_insert_string).arg(qry.lastError().text());
        log(str_msg_log);
        QMessageBox::critical(nullptr, "Error", str_msg_log , QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":NAME", str_country_name);
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
    addNewValueToStorage(i_last_id, str_country_name);
    //
    return i_last_id;
}

bool CountryProcessor::readAllFromDB(){
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
    const QString str_query = QString("select id, name from countries_tbl;");
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

bool CountryProcessor::updateCountryName(int i_country_id, const QString& str_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("UPDATE countries_tbl SET name='%1' WHERE id=%2;").arg(str_name).arg(i_country_id);
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
    CountryStorage::iterator it = m_mapStorage.find(i_country_id);
    it.value()->setName(str_name);
    //
    return true;
}

void CountryProcessor::addNewValueToStorage(int id, const QString& str_name){
    CountryDTO* ptr_country = new CountryDTO() ;
    ptr_country->setId(id);
    ptr_country->setName(str_name);
    m_mapStorage.insert(ptr_country->getId(), ptr_country);
}

QString CountryProcessor::getCountryNameByID(int id){
    QString str_ret;
    //
    CountryStorage::const_iterator i = m_mapStorage.find(id);
    //
    if (i != m_mapStorage.constEnd()){
        str_ret = i.value()->getName();
    };
    //
    return str_ret;
}

const CountryStorage& CountryProcessor::getStorage(){
    return m_mapStorage;
}

void CountryProcessor::log(const QString& str_message) const{
    if (nullptr != m_ptrLog){
        (*m_ptrLog)<<"CountryProcessor: "<<str_message<<"\n";
    };
}

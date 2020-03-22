#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "dbsupport/dbacccesssafe.h"
#include "commondef.h"
#include "countryprocessor.h"
#include "dto/countrydto.h"

CountryProcessor::CountryProcessor(QObject *parent) : QObject(parent)
{

}

CountryProcessor& CountryProcessor::getInstance(){
    static CountryProcessor processor;
    return processor;

}

bool CountryProcessor::init(){
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
        QMessageBox::critical(nullptr, "Error", str_insert_string, QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":NAME", str_country_name);
    //
    if( !qry.exec() )
    {
        QMessageBox::critical(nullptr, "Error", qry.lastError().text(), QMessageBox::Ok);
        return -1;
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
        QMessageBox::critical(nullptr, "Error", str_query, QMessageBox::Ok);
        b_res = false;
    };
    //
    if( !qry.exec() )
    {
        QMessageBox::critical(nullptr, "Error", "Unable to get exec the query\n" + str_query, QMessageBox::Ok);
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

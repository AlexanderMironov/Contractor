#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "dbsupport/dbacccesssafe.h"
#include "commondef.h"
#include "townprocessor.h"
#include "dto/towndto.h"

TownProcessor::TownProcessor(QObject *parent) : QObject(parent)
{

}

TownProcessor& TownProcessor::getInstance(){
    static TownProcessor processor;
    return processor;

}

bool TownProcessor::init(){
    bool b_res = readAllFromDB();

    return b_res;
}

int TownProcessor::add(const QString& str_town_name){
    //search existing
    TownStorage::const_iterator i = m_mapStorage.constBegin();
    //
    while (i != m_mapStorage.constEnd()) {

        TownDTO* ptr_town = i.value();
        if (ptr_town->getName().compare(str_town_name,Qt::CaseInsensitive) == 0){
            return ptr_town->getId();
        };
        i++;
    };
    //if not exists - add new one.
    int i_res = insertIntoDB(str_town_name);
    //
    return i_res;
}

int TownProcessor::insertIntoDB(const QString& str_country_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO towns_tbl (name) values (:NAME);");
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

bool TownProcessor::readAllFromDB(){
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
    const QString str_query = QString("select id, name from towns_tbl;");
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

void TownProcessor::addNewValueToStorage(int id, const QString& str_name){

    TownDTO* ptr_town = new TownDTO() ;
    ptr_town->setId(id);
    ptr_town->setName(str_name);
    m_mapStorage.insert(ptr_town->getId(), ptr_town);
}

QString TownProcessor::getTownNameByID(int i_id) const{
    QString str_ret;
    //
    TownStorage::const_iterator i = m_mapStorage.find(i_id);
    //
    if (i != m_mapStorage.constEnd()){
        str_ret = i.value()->getName();
    };
    //
    return str_ret;
}

const TownStorage& TownProcessor::getStorage() const{
    return m_mapStorage;
}

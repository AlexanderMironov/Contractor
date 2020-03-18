#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMapIterator>
#include <QMessageBox>
//
#include "dbsupport/dbacccesssafe.h"
#include "commondef.h"
#include "skillprocessor.h"
//
SkillProcessor::SkillProcessor(QObject *parent) : QObject(parent)
{

}

SkillProcessor& SkillProcessor::getInstance(){
    static SkillProcessor processor;
    return processor;

}

bool SkillProcessor::init(){
    bool b_res = readAllFromDB();

    return b_res;
}

SkillsList SkillProcessor::add(const QStringList& str_list_skills){
    SkillsList ret;
    for (const auto& i : str_list_skills){
        int i_id = add(i);
        ret.push_back(i_id);
    };
    //
    return ret;
}

int SkillProcessor::add(const QString& str_skill_name){
    //search existing
    QMapIterator<int, SkillDTO*> i(m_mapStorage);
    while (i.hasNext()){
        i.next();
        SkillDTO* ptr_skill = i.value();
        if (ptr_skill->getName().compare(str_skill_name,Qt::CaseInsensitive) == 0){
            return ptr_skill->getId();
        };
    };
    //if not exists - add new one.
    int i_res = insertIntoDB(str_skill_name);
    //
    return i_res;
}

int SkillProcessor::insertIntoDB(const QString& str_country_name){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO skills_tbl (name) values (:NAME);");
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

bool SkillProcessor::readAllFromDB(){
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
    const QString str_query = QString("select id, name from skills_tbl;");
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

void SkillProcessor::addNewValueToStorage(int id, const QString& str_name){
    SkillDTO* ptr_skill = new SkillDTO() ;
    ptr_skill->setId(id);
    ptr_skill->setName(str_name);
    m_mapStorage.insert(ptr_skill->getId(), ptr_skill);
}

QString SkillProcessor::getSkillNameById(int id){
    QString str_ret;
    SkillStorage::const_iterator i = m_mapStorage.find(id);
    //
    if (i != m_mapStorage.constEnd()){
        str_ret = i.value()->getName();
    };
    //
    return str_ret;
}

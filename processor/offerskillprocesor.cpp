#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//
#include "commondef.h"
#include "offerskillprocesor.h"
#include "dbsupport/dbacccesssafe.h"

OfferSkillProcesor::OfferSkillProcesor(QObject *parent) : QObject(parent)
{

}

OfferSkillProcesor&  OfferSkillProcesor::getInstance(){
    static OfferSkillProcesor processor;
    return processor;
}

bool OfferSkillProcesor::init(){
    bool b_res = readAllFromDB();

    return b_res;
}

void OfferSkillProcesor::add(int i_offer_id, const SkillsList& skill_list){
    const int i_skill_list_size = skill_list.size();
    for (int i = 0; i < i_skill_list_size; i++){
        if (isExist(i_offer_id,skill_list[i]) == true){
            continue; // already exist;
        };
        //
        insertIntoDB(i_offer_id, skill_list[i]);
    };
}

bool OfferSkillProcesor::isExist(int i_offer_id, int i_skill_id){
    bool b_res = false;

    for (int i = 0; i < m_vStorage.size(); ++i){
        if (m_vStorage[i]->getOfferId() == i_offer_id){
            if (m_vStorage[i]->getSkillId() == i_skill_id){
                b_res = true;
                break;
            };
        };
    };
    //
    return b_res;
}


bool OfferSkillProcesor::readAllFromDB(){
    bool b_res = true;
    //
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_query = QString("select id, id_offer, id_skill from offers_skills_tbl;");
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
        addNewValueToStorage(qry.value(0).toInt(), qry.value(1).toInt(), qry.value(2).toInt());
    };
    //
    return b_res;
}

int OfferSkillProcesor::insertIntoDB(int i_offer_id, int i_skill_id){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return VALUE_UNDEFINED;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    QString str_insert_string = QString("INSERT INTO offers_skills_tbl (id_offer, id_skill) values (:ID_OFFER, :ID_SKILL);");
    //
    if( !qry.prepare( str_insert_string ) )
    {
        QMessageBox::critical(nullptr, "Error", str_insert_string, QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":ID_OFFER", i_offer_id);
    qry.bindValue(":ID_SKILL", i_skill_id);
    //
    if( !qry.exec() )
    {
        QMessageBox::critical(nullptr, "Error", qry.lastError().text(), QMessageBox::Ok);
        return -1;
    };
    //
    const int i_last_id = qry.lastInsertId().toInt();
    //
    addNewValueToStorage(i_last_id, i_offer_id, i_skill_id);
    //
    return i_last_id;
}

void OfferSkillProcesor::addNewValueToStorage(int id, int i_offer_id, int i_skill_id){
    OfferSkillDTO* ptr_offer_skill = new OfferSkillDTO() ;
    ptr_offer_skill->setId(id);
    ptr_offer_skill->setOfferId(i_offer_id);
    ptr_offer_skill->setSkillId(i_skill_id);
    //
    m_vStorage.push_back(ptr_offer_skill);
}

SkillsList OfferSkillProcesor::getSkillsList(int i_offer_id){
    SkillsList ret_vector;
    //
    for (int i = 0; i <m_vStorage.size(); i++){
        if (m_vStorage[i]->getOfferId() == i_offer_id){
            ret_vector.push_back(m_vStorage[i]->getSkillId());
        };
    };
    return ret_vector;
}

bool OfferSkillProcesor::removeOffer(int i_offer_id){
    DBAcccessSafe dbAccess;
    QSqlDatabase* ptr_db =  dbAccess.getDB();
    if (nullptr == ptr_db){
        return false;
    };
    //
    QSqlQuery qry(*ptr_db);
    //
    const QString str_update_string = QString("DELETE FROM offers_skills_tbl WHERE id_offer = %1;").arg(i_offer_id);
    //
    if ( !qry.prepare( str_update_string  ) )
    {
        QMessageBox::critical(nullptr, "Error prepare", str_update_string, QMessageBox::Ok);
        return false;
    };
    //
    if ( !qry.exec() )
    {
        QMessageBox::critical(nullptr, "Error exec", str_update_string + "\n" + qry.lastError().text(), QMessageBox::Ok);
        return false;
    };
    //

    for (int i = 0; i < m_vStorage.size(); ++i){
        if(m_vStorage[i]->getOfferId() == i_offer_id){
            m_vStorage.remove(i);
            i = 0;
        };
    };
    //
    return true;
}

bool OfferSkillProcesor::replaceSkillsList(int i_offer_id, const SkillsList& skill_list){
    removeOffer(i_offer_id);
    add(i_offer_id,skill_list);
}

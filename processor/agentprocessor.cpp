#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
//
#include "commondef.h"
#include "dto/agentbasedto.h"
#include "agentprocessor.h"
#include "dbsupport/dbacccesssafe.h"

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
    QString str_insert_string = QString("INSERT INTO agents_tbl (name, e_mail, phone_1, phone_2, id_agency) values (:NAME, :EMAIL, :PHONE1, :PHONE2, :ID_AGENCY);");
    //
    if( !qry.prepare( str_insert_string ) )
    {
        QMessageBox::critical(nullptr, "Error", str_insert_string, QMessageBox::Ok);
        return VALUE_UNDEFINED;
    };
    //
    qry.bindValue(":NAME",   ptr_agent_base_info_dto->getName());
    qry.bindValue(":EMAIL",  ptr_agent_base_info_dto->getEMail());
    qry.bindValue(":PHONE1", ptr_agent_base_info_dto->getPhone1());
    qry.bindValue(":PHONE2", ptr_agent_base_info_dto->getPhone2());
    qry.bindValue(":ID_AGENCY", ptr_agent_base_info_dto->getAgencyId());
    //
    if( !qry.exec() )
    {
        QMessageBox::critical(nullptr, "Error", qry.lastError().text(), QMessageBox::Ok);
        return -1;
    };
    //
    int i_last_id = qry.lastInsertId().toInt();
    //
    addNewValueToStorage(i_last_id,
                         ptr_agent_base_info_dto->getName(),
                         ptr_agent_base_info_dto->getEMail(),
                         ptr_agent_base_info_dto->getPhone1(),
                         ptr_agent_base_info_dto->getPhone2(),
                         "", //description
                         ptr_agent_base_info_dto->getAgencyId(),
                         VALUE_UNDEFINED);
    //
    return i_last_id;
}

bool AgentProcessor::init(){
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
    const QString str_query = QString("select id, name, e_mail, phone_1, phone_2, description, id_agency, level from agents_tbl;");
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
        addNewValueToStorage(qry.value(0).toInt(),
                             qry.value(1).toString(),
                             qry.value(2).toString(),
                             qry.value(3).toString(),
                             qry.value(4).toString(),
                             qry.value(5).toString(),
                             qry.value(6).toInt(),
                             qry.value(7).toInt());
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
                                          int i_level){

    AgentBaseDTO* ptr_agent = new AgentBaseDTO();
    ptr_agent->setId(id);
    ptr_agent->setName(str_name);
    ptr_agent->setEMail(str_email);
    ptr_agent->setPhone1(str_phone1);
    ptr_agent->setPhone2(str_phone2);
    ptr_agent->setDescription(str_description);
    ptr_agent->setAgencyId(i_agency_id);
    ptr_agent->setLevel(i_level);
    //
    m_mapStorage.insert(ptr_agent->getEMail(), ptr_agent);
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

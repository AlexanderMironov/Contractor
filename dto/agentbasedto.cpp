#include "agentbasedto.h"
#include "processor/agencyprocessor.h"
#include "commondef.h"

AgentBaseDTO::AgentBaseDTO()
{
    m_iAgencyId = VALUE_UNDEFINED;
    m_iId = VALUE_UNDEFINED;
}

int AgentBaseDTO::getId() const{
    return m_iId;
}

void  AgentBaseDTO::setId(int i_id){
    m_iId = i_id;
}

const QString&  AgentBaseDTO::getName() const{
    return m_strName;
}

void AgentBaseDTO::setName(const QString& str_name){
    m_strName = str_name;
}

const QString&  AgentBaseDTO::getEMail() const{
    return m_strEMail;
}

void AgentBaseDTO::setEMail(const QString& str_email){
    m_strEMail = str_email;
}

const QString&  AgentBaseDTO::getPhone1() const{
    return m_strPhone1;
}

void  AgentBaseDTO::setPhone1(const QString& str_phone_1){
    m_strPhone1 = str_phone_1;
}

const QString&  AgentBaseDTO::getPhone2() const{
    return m_strPhone2;
}

void AgentBaseDTO::setPhone2(const QString& str_phone_2){
    m_strPhone2 = str_phone_2;
}

const QString& AgentBaseDTO::getDescription() const{
    return m_strDescription;
}
void AgentBaseDTO::setDescription(const QString& str_description){
    m_strDescription = str_description;
}


int AgentBaseDTO::getAgencyId() const{
    return m_iAgencyId;
}

void AgentBaseDTO::setAgencyId(int i_agency_id){
    m_iAgencyId = i_agency_id;
}

int  AgentBaseDTO::getLevel() const{
    return m_iLevel;
}

void AgentBaseDTO::setLevel(int i_level){
    m_iLevel = i_level;
}

#include "agencydto.h"

AgencyDTO::AgencyDTO()
{
}

AgencyDTO::AgencyDTO (AgencyDTO const& val){
    m_iId               = val.m_iId;
    m_strName           = val.m_strName;
    m_strDescription    = val.m_strDescription;
}

int AgencyDTO::getId() const{
    return  m_iId;
}

void AgencyDTO::setId(int i_id){
    m_iId = i_id;
}

const QString&  AgencyDTO::getName() const{
    return m_strName;
}

void AgencyDTO::setName(const QString& str_name){
    m_strName = str_name;
}

const QString&  AgencyDTO::getDescription() const{
    return m_strDescription;
}

void AgencyDTO::setDescription(const QString& str_description){
    m_strDescription = str_description;
}

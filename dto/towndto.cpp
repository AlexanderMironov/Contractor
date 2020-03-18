#include "towndto.h"

TownDTO::TownDTO()
{

}

int TownDTO::getId() const{
    return m_iID;
}

void  TownDTO::setId(int i_id){
    m_iID = i_id;
}

const QString&  TownDTO::getName() const{
    return m_strName;
}

void TownDTO::setName(const QString& str_name){
    m_strName = str_name;
}

#include "countrydto.h"

CountryDTO::CountryDTO()
{

}

int CountryDTO::getId() const{
    return m_iID;
}

void  CountryDTO::setId(int i_id){
    m_iID = i_id;
}

const QString&  CountryDTO::getName() const{
    return m_strName;
}

void CountryDTO::setName(const QString& str_name){
    m_strName = str_name;
}

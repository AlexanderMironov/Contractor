#include "statusdto.h"

StatusDTO::StatusDTO()
{

}

int StatusDTO::getId() const{
    return m_iId;
}

void StatusDTO::setId(int i_id){
    m_iId = i_id;
}
//
const QString& StatusDTO::getName() const{
    return m_strName;
}
//
void StatusDTO::setName(const QString& str_name){
    m_strName = str_name;
}

#include "skilldto.h"

SkillDTO::SkillDTO()
{

}

int SkillDTO::getId() const{
    return m_iID;
}

void  SkillDTO::setId(int i_id){
    m_iID = i_id;
}

const QString&  SkillDTO::getName() const{
    return m_strName;
}

void SkillDTO::setName(const QString& str_name){
    m_strName = str_name;
}

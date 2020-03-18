#include "offerskilldto.h"

OfferSkillDTO::OfferSkillDTO()
{

}
//
int OfferSkillDTO::getId() const{
    return m_iID;
}

void OfferSkillDTO::setId(int i_id){
    m_iID = i_id;
}

int OfferSkillDTO::getOfferId() const{
    return m_iOfferID;
}
void OfferSkillDTO::setOfferId(int i_offer_id){
    m_iOfferID = i_offer_id;
}
//
int OfferSkillDTO::getSkillId() const{
    return m_iSkillID;
}

void OfferSkillDTO::setSkillId(int i_skill_id){
    m_iSkillID = i_skill_id;
}

#include "offerbasedto.h"
#include "commondef.h"

OfferBaseDTO::OfferBaseDTO()
{
    m_iId           = VALUE_UNDEFINED;
    m_iCountryId    = VALUE_UNDEFINED;
    m_iCountryId    = VALUE_UNDEFINED;
    m_iRate         = 0;
    m_iStatusId     = VALUE_UNDEFINED;
    m_iAgentId      = VALUE_UNDEFINED;
    m_iAttractivity = VALUE_UNDEFINED;
}

int OfferBaseDTO::getId() const{
    return m_iId;
}

void OfferBaseDTO::setId(int i_id){
    m_iId = i_id;
}

const QDate& OfferBaseDTO::getCreationDate() const{
    return m_dCreationDate;
}
void  OfferBaseDTO::setCreationDate(const QDate& creation_date){
    m_dCreationDate = creation_date;
}

const QString& OfferBaseDTO::getPositionTitle() const{
    return m_strPositionTitle;
}

void OfferBaseDTO::setPositionTitle(const QString& str_pos_title){
    m_strPositionTitle = str_pos_title;
}

const QString& OfferBaseDTO::getDescription() const{
    return m_strDescription;
}

void OfferBaseDTO::setDescription(const QString& str_pos_description){
    m_strDescription = str_pos_description;
}

const QString& OfferBaseDTO::getComments() const{
    return m_strComments;
}

void OfferBaseDTO::setComments(const QString& str_pos_comments){
    m_strComments = str_pos_comments;
}

int OfferBaseDTO::getCountryId() const{
    return m_iCountryId;
}

void OfferBaseDTO::setCountryId(int i_country){
    m_iCountryId = i_country;
}

int OfferBaseDTO::getTownId() const{
    return m_iTownId;
}

void OfferBaseDTO::setTownId(int i_pos_town){
    m_iTownId = i_pos_town;
}

int OfferBaseDTO::getRate() const{
    return m_iRate;
}

void OfferBaseDTO::setRate(int rate){
    m_iRate = rate;
}

int OfferBaseDTO::getStatusId() const{
    return m_iStatusId;
}

void OfferBaseDTO::setStatusId(int i_status){
    m_iStatusId = i_status;
}

int  OfferBaseDTO::getAgentId() const{
    return m_iAgentId;
}

void OfferBaseDTO::setAgentId(int i_agent_id){
    m_iAgentId = i_agent_id;
}

int OfferBaseDTO::getAttractivity() const{
    return m_iAttractivity;
}

void OfferBaseDTO::setAttractivity(int i_attractivity){
    m_iAttractivity = i_attractivity;
}

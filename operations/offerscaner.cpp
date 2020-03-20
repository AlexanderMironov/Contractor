#include "offerscaner.h"
//
#include "commondef.h"
//
#include "processor/skillprocessor.h"
//
#include "dto/agentbasedto.h"
#include "processor/agentprocessor.h"
//
#include "processor/agencyprocessor.h"
//
#include "dto/towndto.h"
#include "processor/townprocessor.h"


OfferScaner::OfferScaner(QObject *parent) : QObject(parent)
{

}

void OfferScaner::parse(const QString& str_original_text){
    m_strModifiedText = str_original_text;
    resetFields();
    //
    removeEmptyStrings();
    generateSkillsList();
    generateAgentInfo();
    generateTownInfo();
}

const QString& OfferScaner::getTownName() const{
    return m_strTown;
}

const QString& OfferScaner::getModifiedText() const{
    return m_strModifiedText;
}

const QString& OfferScaner::getSkills() const{
    return m_strSkills;
}

int OfferScaner::getAgentId() const{
    return m_iAgentId;
}

int  OfferScaner::getAgencyId() const{
    return m_iAgencyId;
}

const QString& OfferScaner::getAgentName() const{
    return m_strAgentName;
}

const QString& OfferScaner::getAgentEmail() const{
    return m_strAgentEmail;
}

const QString& OfferScaner::getAgentPhone1() const{
    return m_strAgentPhone1;
}
const QString& OfferScaner::getAgentPhone2() const{
    return m_strAgentPhone2;
}

const QString& OfferScaner::getAgencyName() const{
    return m_strAgencyName;
}

void OfferScaner::resetFields(){
    m_strTown           = "";
    m_strSkills         = "";
    m_iAgentId          = VALUE_UNDEFINED;
    m_iAgencyId         = VALUE_UNDEFINED;
    m_strAgentName      = "";
    m_strAgentEmail     = "";
    m_strAgentPhone1    = "";
    m_strAgentPhone2    = "";
    //
    m_strAgencyName     = "";
}

void OfferScaner::generateTownInfo(){
    const TownStorage& town_storage = TownProcessor::getInstance().getStorage();
    TownStorage::const_iterator i = town_storage.constBegin();
    //
    for(;i != town_storage.constEnd(); i++){
        TownDTO* ptr_town = i.value();
        const QString str_current_town = ptr_town->getName();
        const int i_found_pos = m_strModifiedText.indexOf(str_current_town,Qt::CaseInsensitive);
        if (-1 != i_found_pos){
            m_strTown = str_current_town;
            break;
        };
    };
}

void OfferScaner::generateAgentInfo(){
    const AgentStorage& agent_storage = AgentProcessor::getInstance().getStorage();
    AgentBaseDTO* ptr_agent = nullptr;
    AgentStorage::const_iterator i = agent_storage.constBegin();
    for (;i != agent_storage.constEnd(); i++){
        const QString str_current_email = i.key();
        const int i_found_pos = m_strModifiedText.indexOf(str_current_email);
        if (-1 != i_found_pos){
            ptr_agent = i.value();
            break;
        };
    };
    //
    if (nullptr == ptr_agent){
        return;
    };
    //
    m_iAgentId          = ptr_agent->getId();
    m_iAgencyId         = ptr_agent->getAgencyId();
    m_strAgentName      = ptr_agent->getName();
    m_strAgentEmail     = ptr_agent->getEMail();
    m_strAgentPhone1    = ptr_agent->getPhone1();
    m_strAgentPhone2    = ptr_agent->getPhone2();
    //
    m_strAgencyName     = AgencyProcessor::getInstance().getAgencyNameByID(m_iAgencyId);
}

void OfferScaner::generateSkillsList(){
    //
    const SkillStorage& skill_storage = SkillProcessor::getInstance().getStorage();
    SkillStorage::const_iterator i = skill_storage.constBegin();
    for (;i != skill_storage.constEnd(); i++){
        const QString str_current_skill = i.value()->getName();
        if (str_current_skill.length() > 1){
            const int i_found_pos = m_strModifiedText.indexOf(str_current_skill, Qt::CaseInsensitive);
            if (-1 != i_found_pos){
                if (m_strSkills.length() > 0){
                    m_strSkills += ",";
                };
                m_strSkills += str_current_skill;
            };
        };
    };
}

void OfferScaner::removeEmptyStrings(){
    const int i_not_found = -1;
    const QString str_cr_lf = "\n";
    const QString str_space = " ";
    //
    const QString str_double_cr_lf = "\n\n";
    const QString str_double_space = "  ";
    const QString str_double_cr_lf_and_space = "\n \n";
    //
    while(true){
        m_strModifiedText.replace(str_double_cr_lf, str_cr_lf );
        m_strModifiedText.replace(str_double_space, str_space);
        m_strModifiedText.replace(str_double_cr_lf_and_space,str_cr_lf);
        //
        const int i_double_cr_ls_pos        = m_strModifiedText.indexOf(str_double_cr_lf);
        const int i_double_space            = m_strModifiedText.indexOf(str_double_space);
        const int i_double_cr_lf_and_space  = m_strModifiedText.indexOf(str_double_cr_lf_and_space);
        //
        if ((i_not_found == i_double_cr_ls_pos) && (i_not_found == i_double_space) && (i_not_found == i_double_cr_lf_and_space)){
            break;
        };
    }
}

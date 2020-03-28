#include <QMessageBox>
//
#include "dlgeditviewoffer.h"
#include "commondef.h"
#include "config/configuration.h"
//
#include "dto/offerbasedto.h"
#include "processor/offerprocessor.h"
//
#include "dto/countrydto.h"
#include "processor/countryprocessor.h"
//
#include "processor/townprocessor.h"
//
#include "processor/skillprocessor.h"
#include "processor/offerskillprocesor.h"
//
#include "dto/statusdto.h"
#include "processor/statusprocessor.h"
//
#include "dto/agentbasedto.h"
#include "processor/agentprocessor.h"
//
#include "processor/agencyprocessor.h"


DlgEditViewOffer::DlgEditViewOffer(QWidget *parent) :
    QDialog(parent)
{
    m_ptrDtoOffer   = nullptr;
    m_ptrDtoAgent   = nullptr;
}

DlgEditViewOffer::~DlgEditViewOffer(){

}

void DlgEditViewOffer::init(int i_offer_id){
    if(nullptr != m_ptrDtoOffer){
        return; //already initialized
    };
    //
    m_bOfferUpdated = false;
    m_bOfferChanged = false;
    //
    m_bChangeDescription = false;
    m_bChangeComment = false;
    m_bChangePositionTitle = false;
    m_bChangeCountry = false;
    m_bChangeTown = false;
    m_bChangeSkillsList = false;
    m_bChangeRate = false;
    m_bChangeStatus = false;
    m_bChangeAttractivity = false;
    //
    this->setWindowTitle("View/Edit job offer");
    //
    m_ptrDtoOffer = OfferProcessor::getInstance().getOfferById(i_offer_id);
    //
    if (nullptr == m_ptrDtoOffer){
        return;
    };
    //
    m_ptrDtoAgent = AgentProcessor::getInstance().getAgentByID(m_ptrDtoOffer->getAgentId());
    //
    if (nullptr == m_ptrDtoAgent){
        return;
    };
    //
    setDlgSizes();
    setElementSizes();
    setDlgLayout();
    setMenuAction();
    //
    createWidgets();
    addWidgetsToLayout();
}

void DlgEditViewOffer::setDlgSizes(){
    const int i_height = 600;
    //
    this->setMinimumHeight(i_height);
    this->setMinimumWidth(1200);
}

void DlgEditViewOffer::setElementSizes(){
    m_iMinButtonWidth   = 60;
    m_iMinLabelWidth    = 80;
    m_iMinEditWidth     = 80;
    m_iMaxLabelHeight   = 25;
    m_iMaxElementWidth = 350;
}

void DlgEditViewOffer::setDlgLayout(){
    this->setLayout(&m_MainLayout);
}

void DlgEditViewOffer::setMenuAction(){

}

void DlgEditViewOffer::createWidgets(){
    createOfferWidgets();
    createAgentWidgets();
    createControlButtons();
}

void DlgEditViewOffer::createOfferWidgets(){
    const int i_left_side_max_width = 700;
    m_LblnsertOffer.setText("Job offer description:");
    m_LblnsertOffer.setMinimumWidth(i_left_side_max_width);
    m_OfferEdit.setMinimumWidth(i_left_side_max_width);
    m_OfferEdit.setPlainText(m_ptrDtoOffer->getDescription());
    connect(&m_OfferEdit, SIGNAL(textChanged()), this, SLOT(onChangeDescription()));

    //m_OfferEdit.setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(&m_OfferEdit, &QPlainTextEdit::copyAvailable, this, &DlgNewOffer::onSelectText);
    //connect(&m_OfferEdit, &QWidget::customContextMenuRequested, this, &DlgNewOffer::onRequestUserMenu);
    //
    m_LblnsertComment.setText("Offer comments:");
    m_LblnsertComment.setMinimumWidth(i_left_side_max_width);
    m_CommentEdit.setMinimumWidth(i_left_side_max_width);
    m_CommentEdit.setPlainText(m_ptrDtoOffer->getComments());
    connect(&m_CommentEdit, SIGNAL(textChanged()), this, SLOT(onChangeComment()));
    //
    m_LblOfferInfo.setText("Offer info");
    m_LblOfferInfo.setMinimumWidth(300);
    m_LblOfferInfo.setMaximumWidth(m_iMaxElementWidth);
    m_LblOfferInfo.setMaximumHeight(m_iMaxLabelHeight);
    m_LblOfferInfo.setAlignment(Qt::AlignLeft);
    //create offer core
    m_LblOfferCore.setText("Position title");
    m_LblOfferCore.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditOfferCore.setMinimumWidth(m_iMinEditWidth);
    m_EditOfferCore.setMaximumWidth(m_iMaxElementWidth);
    m_EditOfferCore.setText(m_ptrDtoOffer->getPositionTitle());
    connect(&m_EditOfferCore, SIGNAL(textChanged(const QString &)), this, SLOT(onChangePositionTitle()));
    //
    m_ButtonAcceptOfferCore.setText("Accept selection");
    m_ButtonAcceptOfferCore.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptOfferCore.setEnabled(false);
    //connect(&m_ButtonAcceptOfferCore, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptPositionDescription);
    //create offer country  line
    m_LblCountry.setText("Country");
    m_LblCountry.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ComboCountry.setMinimumWidth(m_iMinEditWidth);
    m_ComboCountry.setMaximumWidth(m_iMaxElementWidth);
    fillCountryCombo();
    connect(&m_ComboCountry, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeCountry()));

    //..
    //create town country line
    m_LblTown.setText("Town");
    m_LblTown.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditTown.setToolTip("Town country name");
    m_EditTown.setMinimumWidth(m_iMinEditWidth);
    m_EditTown.setMaximumWidth(m_iMaxElementWidth);
    m_EditTown.setText(TownProcessor::getInstance().getTownNameByID(m_ptrDtoOffer->getTownId()));
    connect(&m_EditTown, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeTown()));
    //..
    m_ButtonAcceptTown.setText("Accept selection");
    m_ButtonAcceptTown.setMinimumWidth(m_iMinButtonWidth);
    //connect(&m_ButtonAcceptTown, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptTown);
    m_ButtonAcceptTown.setEnabled(false);
    //
    m_LblSkills.setText("Skills");
    m_LblSkills.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditSkills.setToolTip("Example:Java, C++, Qt...");
    m_EditSkills.setMinimumWidth(m_iMinEditWidth);
    m_EditSkills.setMaximumWidth(m_iMaxElementWidth);
    fillSkillList();
    connect(&m_EditSkills, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeSkillsList()));
    //..
    m_ButtonAcceptSkills.setText("Add selection ");
    m_ButtonAcceptSkills.setMinimumWidth(m_iMinButtonWidth);
    //connect(&m_ButtonAcceptSkills, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptSkills);
    m_ButtonAcceptSkills.setEnabled(false);
    //
    m_LblRate.setText("Rate");
    m_LblRate.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditRate.setToolTip("add estimated rate for this position");
    m_EditRate.setMinimumWidth(30);
    m_EditRate.setMaximumWidth(40);
    m_EditRate.setAlignment(Qt::AlignRight);
    m_EditRate.setText(QString("%1").arg(m_ptrDtoOffer->getRate()));
    connect(&m_EditRate, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeRate()));
    //
    m_LblStatus.setText("Status");
    m_LblStatus.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ComboStatus.setMinimumWidth(m_iMinEditWidth);
    m_ComboStatus.setMaximumWidth(m_iMaxElementWidth);
    fillStatusCombo();
    connect(&m_ComboStatus, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeStatus()));
    //
    m_LblAttractivity.setText("Attractivity");
    m_LblAttractivity.setMinimumWidth(m_iMinLabelWidth);
    //
    m_ComboAttractivity.setMinimumWidth(m_iMinEditWidth);
    m_ComboAttractivity.setMaximumWidth(m_iMaxElementWidth);
    fillAttractivityCombo();
    connect(&m_ComboAttractivity, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeAttractivity()));
    //
}

void DlgEditViewOffer::fillAttractivityCombo(){
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_UNKNOWN), QVariant(static_cast<int>(ATTRACTIVITY_UNKNOWN)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_LOW), QVariant(static_cast<int>(ATTRACTIVITY_LOW)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_STANDARD), QVariant(static_cast<int>(ATTRACTIVITY_STANDARD)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_HIGH), QVariant(static_cast<int>(ATTRACTIVITY_HIGH)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_VERY_HIGH), QVariant(static_cast<int>(ATTRACTIVITY_VERY_HIGH)));
    //
    int i_current_index = 0;
    if (static_cast<int>(ATTRACTIVITY_UNKNOWN) == m_ptrDtoOffer->getAttractivity()){
        i_current_index = 0;
    }else if(static_cast<int>(ATTRACTIVITY_LOW) == m_ptrDtoOffer->getAttractivity()){
        i_current_index = 1;
    }else if(static_cast<int>(ATTRACTIVITY_STANDARD) == m_ptrDtoOffer->getAttractivity()){
        i_current_index = 2;
    }else if(static_cast<int>(ATTRACTIVITY_HIGH) == m_ptrDtoOffer->getAttractivity()){
        i_current_index = 3;
    }else if(static_cast<int>(ATTRACTIVITY_VERY_HIGH) == m_ptrDtoOffer->getAttractivity()){
        i_current_index = 4;
    };
    //
    m_ComboAttractivity.setCurrentIndex(i_current_index);
}

void DlgEditViewOffer::fillStatusCombo(){
    int i_active_index = 0;
    int i_current_index = 0;
    const StatusStorage& status_list = StatusProcessor::getInstance().getStorage();
    for (const auto& i : status_list){
        const int i_key = i->getId();
        const QString& str_status = i->getName();
        m_ComboStatus.addItem(str_status, QVariant(i_key));
        if (i->getId() == m_ptrDtoOffer->getStatusId()){
            i_active_index = i_current_index;
        };
        //
        i_current_index++;
    };
    //
    m_ComboStatus.setCurrentIndex(i_active_index);
}

void DlgEditViewOffer::fillSkillList(){
    SkillsList skills_list = OfferSkillProcesor::getInstance().getSkillsList(m_ptrDtoOffer->getId());
    QString str_skills_list;
    for (const auto& i: skills_list){
        const QString skill_name = SkillProcessor::getInstance().getSkillNameById(i);
        if(str_skills_list.length() > 0){
            str_skills_list +=",";
        };
        str_skills_list += skill_name;
    };
    m_EditSkills.setText(str_skills_list);
}

void  DlgEditViewOffer::createAgentWidgets(){
    m_ptrSpacer = new QSpacerItem(100,325);
    //
    m_LblAgentInfo.setText("Agent info");
    m_LblAgentInfo.setMinimumWidth(300);
    m_LblAgentInfo.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgentInfo.setMaximumHeight(m_iMaxLabelHeight);
    m_LblAgentInfo.setAlignment(Qt::AlignLeft);
    //
    m_LblAgentName.setText("Name");
    m_LblAgentName.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_LblAgentNameValue.setMinimumWidth(m_iMinEditWidth);
    m_LblAgentNameValue.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgentNameValue.setText(m_ptrDtoAgent->getName());
    //
    m_LblAgentEmail.setText("E-mail");
    m_LblAgentEmail.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_LblAgentEmailValue.setMinimumWidth(m_iMinEditWidth);
    m_LblAgentEmailValue.setMaximumWidth(m_iMaxElementWidth);
    QString str_email = QString("<a href='mailto:%1?subject=%2'>%3</a>").arg(m_ptrDtoAgent->getEMail()).arg(m_ptrDtoOffer->getPositionTitle()).arg(m_ptrDtoAgent->getEMail());
    m_LblAgentEmailValue.setText(str_email);
    m_LblAgentEmailValue.setOpenExternalLinks(true);
    //..
    m_LblAgentPhone1.setText("Phone 1");
    m_LblAgentPhone1.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_LblAgentPhone1Value.setMinimumWidth(m_iMinEditWidth);
    m_LblAgentPhone1Value.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgentPhone1Value.setText(m_ptrDtoAgent->getPhone1());
    //
    m_LblAgentPhone2.setText("Phone 2");
    m_LblAgentPhone2.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_LblAgentPhone2Value.setMinimumWidth(m_iMinEditWidth);
    m_LblAgentPhone2Value.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgentPhone2Value.setText(m_ptrDtoAgent->getPhone2());
    //
    m_LblAgencyName.setText("Agency");
    m_LblAgencyName.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_LblAgencyNameValue.setMinimumWidth(m_iMinEditWidth);
    m_LblAgencyNameValue.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgencyNameValue.setText(AgencyProcessor::getInstance().getAgencyNameByID(m_ptrDtoAgent->getAgencyId()));
    //
    m_LblAgentRank.setText("Rank");
    m_LblAgentRank.setMinimumWidth(m_iMinLabelWidth);
    m_LblAgentRank.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_LblAgentRankValue.setText(Configuration::getInstance().getAgentRankAsString(static_cast<AGENT_RANK>(m_ptrDtoAgent->getRank())));
    m_LblAgentRankValue.setMinimumWidth(m_iMinButtonWidth);
    m_LblAgentRankValue.setMaximumWidth(m_iMaxElementWidth);
}

void DlgEditViewOffer::fillCountryCombo(){
    m_ComboCountry.clear();
    //
    const CountryStorage&  country_storage = CountryProcessor::getInstance().getStorage();
    CountryStorage::const_iterator i = country_storage.constBegin();
    //
    int i_active_index = 0;
    int i_current_index = 0;
    //
    while(i != country_storage.constEnd()){
        CountryDTO* ptr_country = i.value();
        m_ComboCountry.addItem(ptr_country->getName(), QVariant(ptr_country->getId()));
        if (m_ptrDtoOffer->getCountryId() == ptr_country->getId()){
            i_active_index = i_current_index;
        }
        i++;
        i_current_index++;
    };
    //
    m_ComboCountry.setCurrentIndex(i_active_index);
}

void DlgEditViewOffer::createControlButtons(){
    //
    m_ButtonUpdateOffer.setText("Update offer ");
    m_ButtonUpdateOffer.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonUpdateOffer.setEnabled(false);
    connect(&m_ButtonUpdateOffer, &QPushButton::released, this, &DlgEditViewOffer::onClickBtnUpdateOffer);
    //
    m_ButtonClose.setText("Close window");
    connect(&m_ButtonClose, &QPushButton::released, this, &DlgEditViewOffer::close);
}

void DlgEditViewOffer::addWidgetsToLayout(){
    //offer text
    //
    int i_row = 0;
    //->addWidget(ptr_widget, row,column,rowSpan,columnSpan, aligment);
    m_MainLayout.addWidget(&m_LblnsertOffer,i_row,0,1,1);
    m_MainLayout.addWidget(&m_LblOfferInfo,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_OfferEdit,i_row,0,11,1);
    //
    m_MainLayout.addWidget(&m_LblOfferCore,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditOfferCore,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptOfferCore,i_row,3,1,1);
    //
    i_row++;
    //
    m_MainLayout.addWidget(&m_LblCountry,i_row,1,1,1);
    m_MainLayout.addWidget(&m_ComboCountry,i_row,2,1,1);
    //
    i_row++;
    //
    m_MainLayout.addWidget(&m_LblTown,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditTown,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptTown,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblSkills,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditSkills,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptSkills,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblRate,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditRate,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblStatus,i_row,1,1,1);
    m_MainLayout.addWidget(&m_ComboStatus,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAttractivity,i_row,1,1,1);
    m_MainLayout.addWidget(&m_ComboAttractivity,i_row,2,1,1);
    //--------------------------------------------------------------------------
    i_row++;
    m_MainLayout.addItem(m_ptrSpacer,i_row,1,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentInfo,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentName,i_row,1,1,1);
    m_MainLayout.addWidget(&m_LblAgentNameValue,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentEmail,i_row,1,1,1);
    m_MainLayout.addWidget(&m_LblAgentEmailValue,i_row,2,1,2);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblnsertComment,i_row,0,1,1);
    //
    m_MainLayout.addWidget(&m_LblAgentPhone1,i_row,1,1,1);
    m_MainLayout.addWidget(&m_LblAgentPhone1Value,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_CommentEdit,i_row,0,6,1);
    //
    m_MainLayout.addWidget(&m_LblAgentPhone2,i_row,1,1,1);
    m_MainLayout.addWidget(&m_LblAgentPhone2Value,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgencyName,i_row,1,1,1);
    m_MainLayout.addWidget(&m_LblAgencyNameValue,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentRank,i_row,1,1,1);
    m_MainLayout.addWidget(&m_LblAgentRankValue,i_row,2,1,1);
    //------------------------------------------------------------------------------
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonUpdateOffer,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonClose,i_row,1,1,3);
}

void DlgEditViewOffer::onChangeDescription(){
    m_bChangeDescription = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeComment(){
    m_bChangeComment = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangePositionTitle(){
    m_bChangePositionTitle = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeCountry(){
    m_bChangeCountry = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeTown(){
    m_bChangeTown = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeSkillsList(){
    m_bChangeSkillsList = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeRate(){
    m_bChangeRate = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeStatus(){
    m_bChangeStatus = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onChangeAttractivity(){
    m_bChangeAttractivity = true;
    m_bOfferChanged = true;
    m_ButtonUpdateOffer.setEnabled(true);
}

void DlgEditViewOffer::onClickBtnUpdateOffer(){
    if(false == isSomethingChanged()){
        QMessageBox box;
        box.setStandardButtons( QMessageBox::Ok);
        box.setText("Nothing has been changed");
        box.exec();
        return;
    };
    //
    updateDesctiption();
    updateComment();
    updatePositionTitle();
    updateCountry();
    updateTown();
    updateSkillList();
    updateRate();
    updateStatus();
    updateAttractivity();
    //
    m_bOfferUpdated = true;
/*

*/
    //
    return;
}

void DlgEditViewOffer::updateAttractivity(){
    if(true == m_bChangeAttractivity){
        const int i_new_attractivity = m_ComboAttractivity.currentData().toInt();
        if (i_new_attractivity != m_ptrDtoOffer->getAttractivity()){
            OfferProcessor::getInstance().updateAttractivity(m_ptrDtoOffer->getId(),i_new_attractivity);
        };
    };
}

void DlgEditViewOffer::updateStatus(){
    if(true == m_bChangeStatus){
        const int i_new_status = m_ComboStatus.currentData().toInt();
        if (i_new_status != m_ptrDtoOffer->getStatusId()){
            OfferProcessor::getInstance().updateOfferStatus(m_ptrDtoOffer->getId(), i_new_status);
        };
    };
}

void DlgEditViewOffer::updateRate(){
    if(true == m_bChangeRate){
        const int i_rate = m_EditRate.text().toInt();
        if(i_rate != m_ptrDtoOffer->getRate()){
            OfferProcessor::getInstance().updateRate(m_ptrDtoOffer->getId(), i_rate);
        };
    };
}

void DlgEditViewOffer::updateSkillList(){
    if(true == m_bChangeSkillsList){
        const QString str_skill_list_row = m_EditSkills.text().trimmed();
        SkillsList skills_list_old = OfferSkillProcesor::getInstance().getSkillsList(m_ptrDtoOffer->getId());
        QStringList skill_list_new_str = str_skill_list_row.split(",", QString::SkipEmptyParts);
        //
        SkillsList skills_list_new;
        for(const auto& i : skill_list_new_str){
            const int i_skill_id = SkillProcessor::getInstance().add(i.trimmed());
            skills_list_new.push_back(i_skill_id);
        };
        //
        const int i_skill_list_new_size = skills_list_new.size();
        const int i_skill_list_old_size = skills_list_old .size();
        //
        bool b_need_to_replace = false;
        //
        if (i_skill_list_new_size == i_skill_list_old_size){
            for (int i=0; i<skills_list_new.size(); ++i){
                bool b_skill_found = false;
                for (int j=0; j<skills_list_old.size(); ++j){
                    if (skills_list_new[i] == skills_list_old[j]){
                        b_skill_found = true;
                        break;
                    };
                };
                if(false == b_skill_found){
                    b_need_to_replace = true;
                    break;
                };
            };
        }else{ //new and old list is not the same size
            OfferSkillProcesor::getInstance().replaceSkillsList(m_ptrDtoOffer->getId(), skills_list_new);
            return;
        };
        //
        if(true == b_need_to_replace){
            OfferSkillProcesor::getInstance().replaceSkillsList(m_ptrDtoOffer->getId(), skills_list_new);
        };
    }
};

void DlgEditViewOffer::updateTown(){
    if(true == m_bChangeTown){
        const int i_town_id = TownProcessor::getInstance().add(m_EditTown.text().trimmed());
        if (i_town_id != m_ptrDtoOffer->getTownId()){
            OfferProcessor::getInstance().updateTown(m_ptrDtoOffer->getId(), i_town_id);
        };
    };
}

void DlgEditViewOffer::updateCountry(){
    if(true == m_bChangeCountry){
        const int i_country_id  = m_ComboCountry.currentData(Qt::UserRole).toInt();
        if(i_country_id != m_ptrDtoOffer->getCountryId()){
            OfferProcessor::getInstance().updateCountry(m_ptrDtoOffer->getId(), i_country_id);
        };
    };
}

void DlgEditViewOffer::updatePositionTitle(){
    if(true == m_bChangePositionTitle){
        const QString str_pos_title_text = m_EditOfferCore.text();
        //
        if(m_ptrDtoOffer->getPositionTitle().compare(str_pos_title_text,Qt::CaseInsensitive) !=0){
            OfferProcessor::getInstance().updatePositionTitle(m_ptrDtoOffer->getId(), str_pos_title_text);
        };
    };
}

void DlgEditViewOffer::updateDesctiption(){
    if(true == m_bChangeDescription){
        QString str_offer_text = m_OfferEdit.toPlainText();
        if (str_offer_text.length() > 2000){
            str_offer_text = str_offer_text.mid(MAX_TEXT_LENGTH);
        };
        //
        if(m_ptrDtoOffer->getDescription().compare(str_offer_text,Qt::CaseInsensitive) !=0){
            OfferProcessor::getInstance().updateDescription(m_ptrDtoOffer->getId(), str_offer_text);
        };
    };
}

void DlgEditViewOffer::updateComment(){
    if(true == m_bChangeComment){
        QString str_comment_text = m_CommentEdit.toPlainText();
        if (str_comment_text.length() > 2000){
            str_comment_text = str_comment_text.mid(MAX_TEXT_LENGTH);
        };
        //
        if(m_ptrDtoOffer->getComments().compare(str_comment_text,Qt::CaseInsensitive) !=0){
            OfferProcessor::getInstance().updateComment(m_ptrDtoOffer->getId(), str_comment_text);
        };
    };
}

bool DlgEditViewOffer::isSomethingChanged() const{
    if( (true == m_bChangeDescription)      ||
        (true == m_bChangeComment)          ||
        (true == m_bChangePositionTitle)    ||
        (true == m_bChangeCountry)          ||
        (true == m_bChangeTown)             ||
        (true == m_bChangeSkillsList)       ||
        (true == m_bChangeRate)             ||
        (true == m_bChangeStatus)           ||
        (true == m_bChangeAttractivity)){
        return true;
    };
    return false;
}

void DlgEditViewOffer::closeEvent(QCloseEvent *event){
    //
    if ((m_bOfferUpdated == false) && (m_bOfferChanged == true)){
        QString str_msg = "Job description not saved. Do you want to close window?";
        QMessageBox box;
        box.setStandardButtons( QMessageBox::Yes|QMessageBox::No );
        box.setText(str_msg);
        const int ret = box.exec();
        if (ret != QMessageBox::Yes){
            event->ignore();
            return;
        };
    };
    //
    event->accept();
}

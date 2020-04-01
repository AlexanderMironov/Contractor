#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
//
#include "dlgnewagent.h"
#include "commondef.h"
#include "config/configuration.h"
//
#include "dto/agentbasedto.h"
#include "processor/agentprocessor.h"
//
#include "dto/agencydto.h"
#include "processor/agencyprocessor.h"

DlgNewAgent::DlgNewAgent()
{
    m_bFillModeOn = false;
    m_iAgentId = VALUE_UNDEFINED;
    m_bDataChanged = false;
}

DlgNewAgent::~DlgNewAgent(){
    detachElements();
    //delete m_MainLayout;
}


/*
not in use right now, just experiment
*/
void DlgNewAgent::detachElements(){
    m_MainLayout.removeWidget(&m_LblDescription);
    m_MainLayout.removeWidget(&m_EditDescription);
    m_MainLayout.removeWidget(&m_LblName);
    m_MainLayout.removeWidget(&m_EditName);
    m_MainLayout.removeWidget(&m_LblEmail);
    m_MainLayout.removeWidget(&m_EditEmail);
    m_MainLayout.removeWidget(&m_LblPhone1);
    m_MainLayout.removeWidget(&m_EditPhone1);
    m_MainLayout.removeWidget(&m_LblPhone2);
    m_MainLayout.removeWidget(&m_EditPhone2);
    m_MainLayout.removeWidget(&m_LblWebProfile);
    m_MainLayout.removeWidget(&m_EditWebProfile);
    m_MainLayout.removeWidget(&m_LblAgency);
    m_MainLayout.removeWidget(&m_EditAgency);
    m_MainLayout.removeWidget(&m_LblRank);
    m_MainLayout.removeWidget(&m_comboRank);
    m_MainLayout.removeWidget(&m_ButtonCheckEmail);
    m_MainLayout.removeWidget(&m_ButtonUpdateSaveOffer);
    m_MainLayout.removeWidget(&m_ButtonClose);
    //
    /*
    delete m_LblDescription;
    delete m_EditDescription;
    delete m_LblName;
    delete m_EditName;
    delete m_LblEmail;
    delete m_EditEmail;
    delete m_LblPhone1;
    delete m_EditPhone1;
    delete m_LblPhone2;
    delete m_EditPhone2;
    delete m_LblWebProfile;
    delete m_EditWebProfile;
    delete m_LblAgency;
    delete m_EditAgency;
    delete m_LblRank;
    delete m_comboRank;
    delete m_ButtonCheckEmail;
    delete m_ButtonUpdateSaveOffer;
    delete m_ButtonClose;
    */
}

void DlgNewAgent::init (int i_agent_id){
    //
    m_iAgentId = i_agent_id;
    m_bFillModeOn = true;
    //
    setInitialFlags();
    setDlgSizes();
    setDlgLayout();
    createGraficElements();
    //
    if (VALUE_UNDEFINED == m_iAgentId){
        this->setWindowTitle("Create new agent");
    }else{
        this->setWindowTitle("Show/Edit agent");
        fillInitialData();
    };
    //
    addWidgetsToLayout();
    m_bFillModeOn = false;
}

void DlgNewAgent::setInitialFlags(){
    m_bDataChanged          = false;
    m_bDescriptionChanged   = false;
    m_bNameChanged          = false;
    m_bEmailChanged         = false;
    m_bPhone1Changed        = false;
    m_bPhone2Changed        = false;
    m_bWebProfileChanged    = false;
    m_bRankChanged          = false;
}

bool DlgNewAgent::isSomethingChanged() const{
    if((true == m_bDescriptionChanged)  ||
       (true == m_bNameChanged)         ||
       (true == m_bEmailChanged)        ||
       (true == m_bPhone1Changed)       ||
       (true == m_bPhone2Changed )      ||
       (true == m_bWebProfileChanged )  ||
       (true == m_bRankChanged)){
        return true;
    };
    //
    return false;
}

void DlgNewAgent::createGraficElements(){
    const int i_left_side_max_width = 350;
    //m_LblDescription = new QLabel();
    m_LblDescription.setText("Agent description:");
    m_LblDescription.setMinimumWidth(i_left_side_max_width);
    //m_EditDescription = new QPlainTextEdit();
    m_EditDescription.setMinimumWidth(i_left_side_max_width);
    m_EditDescription.setMaximumWidth(i_left_side_max_width*2);
    connect(&m_EditDescription, SIGNAL(textChanged()), this, SLOT(onChangeDescription()));
    //
    //m_LblName = new QLabel();
    m_LblName.setText("Name");
    m_LblName.setMinimumWidth(m_iMinLabelWidth);
    m_LblName.setMaximumWidth(m_iMaxElementWidth);
    m_LblName.setMaximumHeight(m_iMaxLabelHeight);
    m_LblName.setAlignment(Qt::AlignLeft);
    //
    //m_EditName = new QLineEdit();
    m_EditName.setMinimumWidth(m_iMinEditWidth);
    m_EditName.setMaximumWidth(m_iMaxElementWidth);
    connect(&m_EditName, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeName()));
    //
    //m_LblEmail = new QLabel();
    m_LblEmail.setText("E-mail");
    m_LblEmail.setMinimumWidth(m_iMinLabelWidth);
    m_LblEmail.setMaximumWidth(m_iMaxElementWidth);
    m_LblEmail.setMaximumHeight(m_iMaxLabelHeight);
    m_LblEmail.setAlignment(Qt::AlignLeft);
    //
    //m_EditEmail = new QLineEdit();
    m_EditEmail.setMinimumWidth(m_iMinEditWidth);
    m_EditEmail.setMaximumWidth(m_iMaxElementWidth);
    connect(&m_EditEmail, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeEmail()));
    //
    //m_LblPhone1= new QLabel();
    m_LblPhone1.setText("Phone 1");
    m_LblPhone1.setMinimumWidth(m_iMinLabelWidth);
    m_LblPhone1.setMaximumWidth(m_iMaxElementWidth);
    m_LblPhone1.setMaximumHeight(m_iMaxLabelHeight);
    m_LblPhone1.setAlignment(Qt::AlignLeft);
    //
    //m_EditPhone1 = new QLineEdit();
    m_EditPhone1.setMinimumWidth(m_iMinEditWidth);
    m_EditPhone1.setMaximumWidth(m_iMaxElementWidth);
    connect(&m_EditPhone1, SIGNAL(textChanged(const QString &)), this, SLOT(onChangePhone1()));
    //
    //m_LblPhone2 = new QLabel();
    m_LblPhone2.setText("Phone 2");
    m_LblPhone2.setMinimumWidth(m_iMinLabelWidth);
    m_LblPhone2.setMaximumWidth(m_iMaxElementWidth);
    m_LblPhone2.setMaximumHeight(m_iMaxLabelHeight);
    m_LblPhone2.setAlignment(Qt::AlignLeft);
    //
    //m_EditPhone2 = new QLineEdit();
    m_EditPhone2.setMinimumWidth(m_iMinEditWidth);
    m_EditPhone2.setMaximumWidth(m_iMaxElementWidth);
    connect(&m_EditPhone2, SIGNAL(textChanged(const QString &)), this, SLOT(onChangePhone2()));
    //
    //m_LblWebProfile = new QLabel();
    m_LblWebProfile.setText("Web profile");
    m_LblWebProfile.setMinimumWidth(m_iMinLabelWidth);
    m_LblWebProfile.setMaximumWidth(m_iMaxElementWidth);
    m_LblWebProfile.setMaximumHeight(m_iMaxLabelHeight);
    m_LblWebProfile.setAlignment(Qt::AlignLeft);
    //
    //m_EditWebProfile = new QLineEdit();
    m_EditWebProfile.setMinimumWidth(m_iMinEditWidth);
    m_EditWebProfile.setMaximumWidth(m_iMaxElementWidth);
    connect(&m_EditWebProfile, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeWebProfile()));
    //
    //m_LblAgency = new QLabel();
    m_LblAgency.setText("Agency");
    m_LblAgency.setMinimumWidth(m_iMinLabelWidth);
    m_LblAgency.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgency.setMaximumHeight(m_iMaxLabelHeight);
    m_LblAgency.setAlignment(Qt::AlignLeft);
    //
    //m_EditAgency = new QLineEdit();
    m_EditAgency.setMinimumWidth(m_iMinEditWidth);
    m_EditAgency.setMaximumWidth(m_iMaxElementWidth);
    //
    //m_LblRank = new QLabel();
    m_LblRank.setText("Rank");
    m_LblRank.setMinimumWidth(m_iMinLabelWidth);
    m_LblRank.setMaximumWidth(m_iMaxElementWidth);
    m_LblRank.setMaximumHeight(m_iMaxLabelHeight);
    m_LblRank.setAlignment(Qt::AlignLeft);
    //
    //m_comboRank = new QComboBox();
    m_comboRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankUnknown), QVariant(static_cast<int>(AGENT_RANK::RankUnknown)));
    m_comboRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryBad), QVariant(static_cast<int>(AGENT_RANK::RankVeryBad)));
    m_comboRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankBad), QVariant(static_cast<int>(AGENT_RANK::RankBad)));
    m_comboRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankNeutral), QVariant(static_cast<int>(AGENT_RANK::RankNeutral)));
    m_comboRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankGood), QVariant(static_cast<int>(AGENT_RANK::RankGood)));
    m_comboRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryGood), QVariant(static_cast<int>(AGENT_RANK::RankVeryGood)));
    m_comboRank.setCurrentIndex(0);
    //
    connect(&m_comboRank, SIGNAL(currentIndexChanged(int)), this, SLOT(onRankChanged(int)));
    //
    //m_ButtonCheckEmail = new QPushButton();
    m_ButtonCheckEmail.setText("Check e-mail");
    m_ButtonCheckEmail.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonCheckEmail.setMinimumHeight(m_iMinButtonHeight);
    m_ButtonCheckEmail.setEnabled(false);
    connect(&m_ButtonCheckEmail, &QPushButton::released, this, &DlgNewAgent::onClickBtnCheckEmail);
    //
    //m_ButtonUpdateSaveOffer = new QPushButton();
    m_ButtonUpdateSaveOffer.setText("Save new agent");
    m_ButtonUpdateSaveOffer.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonUpdateSaveOffer.setEnabled(false);
    m_ButtonUpdateSaveOffer.setMinimumHeight(m_iMinButtonHeight);
    connect(&m_ButtonUpdateSaveOffer, &QPushButton::released, this, &DlgNewAgent::onClickBtnUpdateSaveOffer);
    //
    //m_ButtonClose = new QPushButton();
    m_ButtonClose.setText("Close");
    m_ButtonClose.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonClose.setEnabled(true);
    m_ButtonClose.setMinimumHeight(m_iMinButtonHeight);
    connect(&m_ButtonClose, &QPushButton::released, this, &DlgNewAgent::close);
    //
    //m_EditStatusBar = new QLineEdit();
    m_EditStatusBar.setEnabled(false);
}

void DlgNewAgent::fillInitialData(){
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByID(m_iAgentId);
    if(nullptr == ptr_agent){
        return;
    };
    //
    m_EditDescription.setPlainText(ptr_agent->getDescription());
    m_EditName.setText(ptr_agent->getName());
    m_EditEmail.setText(ptr_agent->getEMail());
    m_EditPhone1.setText(ptr_agent->getPhone1());
    m_EditPhone2.setText(ptr_agent->getPhone2());
    m_EditWebProfile.setText(ptr_agent->getWebProfile());
    m_EditAgency.setEnabled(false);
    const QString str_agency_name = AgencyProcessor::getInstance().getAgencyNameByID(ptr_agent->getAgencyId());
    m_EditAgency.setText(str_agency_name);
    //
    for (int i = 0; i < m_comboRank.count(); ++i){
        QVariant current_rank = m_comboRank.itemData(i,Qt::UserRole);
        if (current_rank.toInt() == ptr_agent->getRank()){
            m_comboRank.setCurrentIndex(i);
            break;
        };
    };
    //
    m_ButtonUpdateSaveOffer.setText("Update agent data");
}

void DlgNewAgent::setDlgSizes(){
    const int i_height = 350;
    //
    this->setMinimumHeight(i_height);
    this->setMaximumHeight(i_height);
    this->setMinimumWidth(800);
    this->setMaximumWidth(800);
    //
    m_iMinLabelWidth    = 60;
    m_iMaxElementWidth  = 320;
    m_iMaxLabelHeight   = 25;
    m_iMinEditWidth     = 80;
    //
    m_iMinButtonWidth = m_iMinLabelWidth + m_iMinEditWidth;
    m_iMinButtonHeight = 25;
}

void DlgNewAgent::setDlgLayout(){
    //m_MainLayout = new  QGridLayout();
    this->setLayout(&m_MainLayout);
}

void DlgNewAgent::addWidgetsToLayout(){
    int i_row = 0;
    //.addWidget(ptr_widget,                row,column,rowSpan,columnSpan,                         aligment);
    m_MainLayout.addWidget(&m_LblDescription,i_row,0,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_EditDescription,i_row,0,10,1);
    //
    m_MainLayout.addWidget(&m_LblName,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditName,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblEmail,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditEmail,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblPhone1,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditPhone1,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblPhone2,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditPhone2,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblWebProfile,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditWebProfile,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgency,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgency,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblRank,i_row,1,1,1);
    m_MainLayout.addWidget(&m_comboRank,i_row,2,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonCheckEmail,i_row,1,1,2);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonUpdateSaveOffer,i_row,1,1,2);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonClose,i_row,1,1,2);
    //
    i_row++;
    m_MainLayout.addWidget(&m_EditStatusBar,i_row,0,1,3);
}

void DlgNewAgent::onChangeDescription(){
    if(true == m_bFillModeOn){
        return;
    };
    whenSomethingChanged();
    m_bDescriptionChanged = true;
}

void DlgNewAgent::onChangeName(){
    if(true == m_bFillModeOn){
        return;
    };
    whenSomethingChanged();
    m_bNameChanged = true;
}

void DlgNewAgent::onChangeEmail(){
    if(true == m_bFillModeOn){
        return;
    };
    if(m_EditEmail.text().length() > 0){
        m_ButtonCheckEmail.setEnabled(true);
    }else{
        m_ButtonCheckEmail.setEnabled(false);
    };
    //
    whenSomethingChanged();
    m_bEmailChanged = true;
}

void DlgNewAgent::onChangePhone1(){
    if(true == m_bFillModeOn){
        return;
    };
    whenSomethingChanged();
    m_bPhone1Changed = true;
}

void DlgNewAgent::onChangePhone2(){
    if(true == m_bFillModeOn){
        return;
    };
    whenSomethingChanged();
    m_bPhone2Changed = true;
}

void DlgNewAgent::onChangeWebProfile(){
    if(true == m_bFillModeOn){
        return;
    };
    whenSomethingChanged();
    m_bWebProfileChanged = true;
}

void DlgNewAgent::whenSomethingChanged(){
    m_bDataChanged = true;
    m_ButtonUpdateSaveOffer.setEnabled(true);
}

void DlgNewAgent::onClickBtnUpdateSaveOffer(){
    QString str_msg;
    const bool b_is_possible = isPossibleToSaveOrUpdate(str_msg);
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Ok );
    //
    if(false == b_is_possible){
        box.setText(str_msg);
        box.exec();
        return;
    };
    //
    if(VALUE_UNDEFINED == m_iAgentId){
        saveAgent();
        this->close();
    }else{
        updateAgent();
        m_EditStatusBar.setText("Agent info updated");
    };
}

void DlgNewAgent::saveAgent(){
    const int i_agency_id = saveAgency(m_EditAgency.text().trimmed());
    if (VALUE_UNDEFINED == i_agency_id){
        return;
    };
    //
    AgentBaseDTO agent_dto;
    agent_dto.setAgencyId(i_agency_id);
    agent_dto.setName(m_EditName.text().trimmed());
    agent_dto.setDescription(m_EditDescription.toPlainText().trimmed());
    agent_dto.setEMail(m_EditEmail.text().trimmed());
    agent_dto.setPhone1(m_EditPhone1.text().trimmed());
    agent_dto.setPhone2(m_EditPhone2.text().trimmed());
    agent_dto.setWebProfile(m_EditWebProfile.text().trimmed());
    const int i_rank = m_comboRank.currentData().toInt();
    agent_dto.setRank(i_rank);
    //
    m_iAgentId = AgentProcessor::getInstance().add(&agent_dto);
    //
    m_bDataChanged = false;
}

int DlgNewAgent::saveAgency(const QString& str_agency_name){
    const int i_agency_id = AgencyProcessor::getInstance().add(str_agency_name);
    return i_agency_id;
}

void DlgNewAgent::updateAgent(){
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByID(m_iAgentId);
    if (nullptr == ptr_agent){
        return;
    };
    //
    if(true == m_bDescriptionChanged){
        const QString str_new_description = m_EditDescription.toPlainText().trimmed();
        if (ptr_agent->getDescription().compare(str_new_description, Qt::CaseInsensitive) != 0){
            AgentProcessor::getInstance().updateDecription(m_iAgentId, str_new_description);
        }else{
            m_bDescriptionChanged = false;
        };
    };
    //
    if(true == m_bNameChanged){
        const QString str_new_name = m_EditName.text().trimmed();
        if (ptr_agent->getName().compare(str_new_name, Qt::CaseInsensitive) != 0){ //name was really changed
            if(str_new_name.isEmpty() == false){
                AgentProcessor::getInstance().updateName(m_iAgentId, str_new_name);
            }else{
                m_bNameChanged = false;
            };
        };
    };
    //
    if(true == m_bEmailChanged){
        const QString str_new_email = m_EditEmail.text().trimmed();
        if(str_new_email.isEmpty() == false){
            AgentProcessor::getInstance().updateEmail(m_iAgentId, str_new_email);
        };
    };
    //
    if(true == m_bPhone1Changed){
        AgentProcessor::getInstance().updatePhone(m_iAgentId, m_EditPhone1.text().trimmed(), AgentProcessor::PHONE_NUM::PHONE_NUM_1);
    };
    //
    if(true == m_bPhone2Changed){
        AgentProcessor::getInstance().updatePhone(m_iAgentId, m_EditPhone2.text().trimmed(), AgentProcessor::PHONE_NUM::PHONE_NUM_2);
    };
    //
    if(true == m_bWebProfileChanged){
        AgentProcessor::getInstance().updateWebProfile(m_iAgentId, m_EditWebProfile.text().trimmed());
    };
    //
    if(true == m_bRankChanged){
        const int i_new_rank = m_comboRank.currentData().toInt();
        if(ptr_agent->getRank() != i_new_rank){
            AgentProcessor::getInstance().updateRank(m_iAgentId,i_new_rank);
        };
    };
    //
    m_bDataChanged = false; //already saved
}

bool DlgNewAgent::isPossibleToSaveOrUpdate(QString& str_message) const{

    if(m_EditName.text().isEmpty() == true){
        str_message = "Agent name can not be empty\n";
    };
    //
    if(m_EditEmail.text().isEmpty() == true){
        str_message += "Agent e-mail can not be empty\n";
    };
    //
    if((m_EditPhone1.text().trimmed().isEmpty() == true) && (m_EditPhone2.text().trimmed().isEmpty() == true)){
        str_message += "Agent phone can not be empty\n";
    };
    //
    if(m_EditAgency.text().isEmpty() == true){
        str_message += "Agency name can not be empty\n";
    };
    //
    if (str_message.isEmpty() == false){
        return false;
    };
    return true;
}

void DlgNewAgent::onRankChanged(int){
    if(m_bFillModeOn){
        return;
    };
    whenSomethingChanged();
    m_bRankChanged = true;
}

void DlgNewAgent::onClickBtnCheckEmail(){
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByEmail(m_EditEmail.text().trimmed());
    QString str_msg;
    if (nullptr == ptr_agent){
        str_msg = "Agent with this e-mail not found";
    }else{
        str_msg = "Agent with this e-mail already exists";
    };
    //
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Ok );
    box.setText(str_msg);
    box.exec();
}

int  DlgNewAgent::getAgentId() const{
    return m_iAgentId;
}

bool DlgNewAgent::isNameOrDescriptionChanged() const{
    if((true == m_bNameChanged) || (true == m_bDescriptionChanged)){
        return true;
    };
    //
    return false;
}

void DlgNewAgent::closeEvent(QCloseEvent *event){
    if(true == m_bDataChanged){
        QString str_msg = "Agen info not saved. Do you want to close window?";
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

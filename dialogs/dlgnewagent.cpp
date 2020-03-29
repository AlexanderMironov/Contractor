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
    //detachElements();
    delete m_ptrMainLayout;
}


/*
not in use right now, just experiment
*/
void DlgNewAgent::detachElements(){
    m_ptrMainLayout->removeWidget(m_ptrLblDescription);
    m_ptrMainLayout->removeWidget(m_ptrEditDescription);
    m_ptrMainLayout->removeWidget(m_ptrLblName);
    m_ptrMainLayout->removeWidget(m_ptrEditName);
    m_ptrMainLayout->removeWidget(m_ptrLblEmail);
    m_ptrMainLayout->removeWidget(m_ptrEditEmail);
    m_ptrMainLayout->removeWidget(m_ptrLblPhone1);
    m_ptrMainLayout->removeWidget(m_ptrEditPhone1);
    m_ptrMainLayout->removeWidget(m_ptrLblPhone2);
    m_ptrMainLayout->removeWidget(m_ptrEditPhone2);
    m_ptrMainLayout->removeWidget(m_ptrLblWebProfile);
    m_ptrMainLayout->removeWidget(m_ptrEditWebProfile);
    m_ptrMainLayout->removeWidget(m_ptrLblAgency);
    m_ptrMainLayout->removeWidget(m_ptrEditAgency);
    m_ptrMainLayout->removeWidget(m_ptrLblRank);
    m_ptrMainLayout->removeWidget(m_ptrcomboRank);
    m_ptrMainLayout->removeWidget(m_ptrButtonCheckEmail);
    m_ptrMainLayout->removeWidget(m_ptrButtonUpdateSaveOffer);
    m_ptrMainLayout->removeWidget(m_ptrButtonClose);
    //
    delete m_ptrLblDescription;
    delete m_ptrEditDescription;
    delete m_ptrLblName;
    delete m_ptrEditName;
    delete m_ptrLblEmail;
    delete m_ptrEditEmail;
    delete m_ptrLblPhone1;
    delete m_ptrEditPhone1;
    delete m_ptrLblPhone2;
    delete m_ptrEditPhone2;
    delete m_ptrLblWebProfile;
    delete m_ptrEditWebProfile;
    delete m_ptrLblAgency;
    delete m_ptrEditAgency;
    delete m_ptrLblRank;
    delete m_ptrcomboRank;
    delete m_ptrButtonCheckEmail;
    delete m_ptrButtonUpdateSaveOffer;
    delete m_ptrButtonClose;
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
    m_ptrLblDescription = new QLabel();
    m_ptrLblDescription->setText("Agent description:");
    m_ptrLblDescription->setMinimumWidth(i_left_side_max_width);
    m_ptrEditDescription = new QPlainTextEdit();
    m_ptrEditDescription->setMinimumWidth(i_left_side_max_width);
    m_ptrEditDescription->setMaximumWidth(i_left_side_max_width*2);
    connect(m_ptrEditDescription, SIGNAL(textChanged()), this, SLOT(onChangeDescription()));
    //
    m_ptrLblName = new QLabel();
    m_ptrLblName->setText("Name");
    m_ptrLblName->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblName->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblName->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblName->setAlignment(Qt::AlignLeft);
    //
    m_ptrEditName = new QLineEdit();
    m_ptrEditName->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditName->setMaximumWidth(m_iMaxElementWidth);
    connect(m_ptrEditName, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeName()));
    //
    m_ptrLblEmail = new QLabel();
    m_ptrLblEmail->setText("E-mail");
    m_ptrLblEmail->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblEmail->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblEmail->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblEmail->setAlignment(Qt::AlignLeft);
    //
    m_ptrEditEmail = new QLineEdit();
    m_ptrEditEmail->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditEmail->setMaximumWidth(m_iMaxElementWidth);
    connect(m_ptrEditEmail, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeEmail()));
    //
    m_ptrLblPhone1= new QLabel();
    m_ptrLblPhone1->setText("Phone 1");
    m_ptrLblPhone1->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblPhone1->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblPhone1->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblPhone1->setAlignment(Qt::AlignLeft);
    //
    m_ptrEditPhone1 = new QLineEdit();
    m_ptrEditPhone1->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditPhone1->setMaximumWidth(m_iMaxElementWidth);
    connect(m_ptrEditPhone1, SIGNAL(textChanged(const QString &)), this, SLOT(onChangePhone1()));
    //
    m_ptrLblPhone2 = new QLabel();
    m_ptrLblPhone2->setText("Phone 2");
    m_ptrLblPhone2->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblPhone2->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblPhone2->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblPhone2->setAlignment(Qt::AlignLeft);
    //
    m_ptrEditPhone2 = new QLineEdit();
    m_ptrEditPhone2->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditPhone2->setMaximumWidth(m_iMaxElementWidth);
    connect(m_ptrEditPhone2, SIGNAL(textChanged(const QString &)), this, SLOT(onChangePhone2()));
    //
    m_ptrLblWebProfile = new QLabel();
    m_ptrLblWebProfile->setText("Web profile");
    m_ptrLblWebProfile->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblWebProfile->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblWebProfile->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblWebProfile->setAlignment(Qt::AlignLeft);
    //
    m_ptrEditWebProfile = new QLineEdit();
    m_ptrEditWebProfile->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditWebProfile->setMaximumWidth(m_iMaxElementWidth);
    connect(m_ptrEditWebProfile, SIGNAL(textChanged(const QString &)), this, SLOT(onChangeWebProfile()));
    //
    m_ptrLblAgency = new QLabel();
    m_ptrLblAgency->setText("Agency");
    m_ptrLblAgency->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblAgency->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblAgency->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblAgency->setAlignment(Qt::AlignLeft);
    //
    m_ptrEditAgency = new QLineEdit();
    m_ptrEditAgency->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditAgency->setMaximumWidth(m_iMaxElementWidth);
    //
    m_ptrLblRank = new QLabel();
    m_ptrLblRank->setText("Rank");
    m_ptrLblRank->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblRank->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblRank->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblRank->setAlignment(Qt::AlignLeft);
    //
    m_ptrcomboRank = new QComboBox();
    m_ptrcomboRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankUnknown), QVariant(static_cast<int>(AGENT_RANK::RankUnknown)));
    m_ptrcomboRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryBad), QVariant(static_cast<int>(AGENT_RANK::RankVeryBad)));
    m_ptrcomboRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankBad), QVariant(static_cast<int>(AGENT_RANK::RankBad)));
    m_ptrcomboRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankNeutral), QVariant(static_cast<int>(AGENT_RANK::RankNeutral)));
    m_ptrcomboRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankGood), QVariant(static_cast<int>(AGENT_RANK::RankGood)));
    m_ptrcomboRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryGood), QVariant(static_cast<int>(AGENT_RANK::RankVeryGood)));
    m_ptrcomboRank->setCurrentIndex(0);
    //
    connect(m_ptrcomboRank, SIGNAL(currentIndexChanged(int)), this, SLOT(onRankChanged(int)));
    //
    m_ptrButtonCheckEmail = new QPushButton();
    m_ptrButtonCheckEmail->setText("Check e-mail");
    m_ptrButtonCheckEmail->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonCheckEmail->setEnabled(false);
    connect(m_ptrButtonCheckEmail, &QPushButton::released, this, &DlgNewAgent::onClickBtnCheckEmail);
    //
    m_ptrButtonUpdateSaveOffer = new QPushButton();
    m_ptrButtonUpdateSaveOffer->setText("Save new agent");
    m_ptrButtonUpdateSaveOffer->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonUpdateSaveOffer->setEnabled(false);
    connect(m_ptrButtonUpdateSaveOffer, &QPushButton::released, this, &DlgNewAgent::onClickBtnUpdateSaveOffer);
    //
    m_ptrButtonClose = new QPushButton();
    m_ptrButtonClose->setText("Close");
    m_ptrButtonClose->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonClose->setEnabled(true);
    connect(m_ptrButtonClose, &QPushButton::released, this, &DlgNewAgent::close);
    //
    m_ptrEditStatusBar = new QLineEdit();
    m_ptrEditStatusBar->setEnabled(false);
}

void DlgNewAgent::fillInitialData(){
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByID(m_iAgentId);
    if(nullptr == ptr_agent){
        return;
    };
    //
    m_ptrEditDescription->setPlainText(ptr_agent->getDescription());
    m_ptrEditName->setText(ptr_agent->getName());
    m_ptrEditEmail->setText(ptr_agent->getEMail());
    m_ptrEditPhone1->setText(ptr_agent->getPhone1());
    m_ptrEditPhone2->setText(ptr_agent->getPhone2());
    m_ptrEditWebProfile->setText(ptr_agent->getWebProfile());
    m_ptrEditAgency->setEnabled(false);
    const QString str_agency_name = AgencyProcessor::getInstance().getAgencyNameByID(ptr_agent->getAgencyId());
    m_ptrEditAgency->setText(str_agency_name);
    //
    for (int i = 0; i < m_ptrcomboRank->count(); ++i){
        QVariant current_rank = m_ptrcomboRank->itemData(i,Qt::UserRole);
        if (current_rank.toInt() == ptr_agent->getRank()){
            m_ptrcomboRank->setCurrentIndex(i);
            break;
        };
    };
    //
    m_ptrButtonUpdateSaveOffer->setText("Update agent data");
}

void DlgNewAgent::setDlgSizes(){
    const int i_height = 300;
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
}

void DlgNewAgent::setDlgLayout(){
    m_ptrMainLayout = new  QGridLayout();
    this->setLayout(m_ptrMainLayout);
}

void DlgNewAgent::addWidgetsToLayout(){
    int i_row = 0;
    //->addWidget(ptr_widget,                row,column,rowSpan,columnSpan,                         aligment);
    m_ptrMainLayout->addWidget(m_ptrLblDescription,i_row,0,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrEditDescription,i_row,0,10,1);
    //
    m_ptrMainLayout->addWidget(m_ptrLblName,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditName,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblEmail,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditEmail,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblPhone1,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditPhone1,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblPhone2,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditPhone2,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblWebProfile,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditWebProfile,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAgency,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditAgency,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblRank,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrcomboRank,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrButtonCheckEmail,i_row,1,1,2);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrButtonUpdateSaveOffer,i_row,1,1,2);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrButtonClose,i_row,1,1,2);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrEditStatusBar,i_row,0,1,3);
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
    if(m_ptrEditEmail->text().length() > 0){
        m_ptrButtonCheckEmail->setEnabled(true);
    }else{
        m_ptrButtonCheckEmail->setEnabled(false);
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
    m_ptrButtonUpdateSaveOffer->setEnabled(true);
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
        m_ptrEditStatusBar->setText("Agent info updated");
    };
}

void DlgNewAgent::saveAgent(){
    const int i_agency_id = saveAgency(m_ptrEditAgency->text().trimmed());
    if (VALUE_UNDEFINED == i_agency_id){
        return;
    };
    //
    AgentBaseDTO agent_dto;
    agent_dto.setAgencyId(i_agency_id);
    agent_dto.setName(m_ptrEditName->text().trimmed());
    agent_dto.setDescription(m_ptrEditDescription->toPlainText().trimmed());
    agent_dto.setEMail(m_ptrEditEmail->text().trimmed());
    agent_dto.setPhone1(m_ptrEditPhone1->text().trimmed());
    agent_dto.setPhone2(m_ptrEditPhone2->text().trimmed());
    agent_dto.setWebProfile(m_ptrEditWebProfile->text().trimmed());
    agent_dto.setRank(m_ptrcomboRank->currentData().toInt());
    //
    m_iAgentId = AgentProcessor::getInstance().add(&agent_dto);
    //
    m_bDataChanged = true;
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
        const QString str_new_description = m_ptrEditDescription->toPlainText().trimmed();
        if (ptr_agent->getDescription().compare(str_new_description, Qt::CaseInsensitive) != 0){
            AgentProcessor::getInstance().updateDecription(m_iAgentId, str_new_description);
        }else{
            m_bDescriptionChanged = false;
        };
    };
    //
    if(true == m_bNameChanged){
        const QString str_new_name = m_ptrEditName->text().trimmed();
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
        const QString str_new_email = m_ptrEditEmail->text().trimmed();
        if(str_new_email.isEmpty() == false){
            AgentProcessor::getInstance().updateEmail(m_iAgentId, str_new_email);
        };
    };
    //
    if(true == m_bPhone1Changed){
        AgentProcessor::getInstance().updatePhone(m_iAgentId, m_ptrEditPhone1->text().trimmed(), AgentProcessor::PHONE_NUM::PHONE_NUM_1);
    };
    //
    if(true == m_bPhone2Changed){
        AgentProcessor::getInstance().updatePhone(m_iAgentId, m_ptrEditPhone2->text().trimmed(), AgentProcessor::PHONE_NUM::PHONE_NUM_2);
    };
    //
    if(true == m_bWebProfileChanged){
        AgentProcessor::getInstance().updateWebProfile(m_iAgentId, m_ptrEditWebProfile->text().trimmed());
    };
    //
    if(true == m_bRankChanged){
        const int i_new_rank = m_ptrcomboRank->currentData().toInt();
        if(ptr_agent->getRank() != i_new_rank){
            AgentProcessor::getInstance().updateRank(m_iAgentId,i_new_rank);
        };
    };
    //
    m_bDataChanged = false; //already saved
}

bool DlgNewAgent::isPossibleToSaveOrUpdate(QString& str_message) const{

    if(m_ptrEditName->text().isEmpty() == true){
        str_message = "Agent name can not be empty\n";
    };
    //
    if(m_ptrEditEmail->text().isEmpty() == true){
        str_message += "Agent e-mail can not be empty\n";
    };
    //
    if((m_ptrEditPhone1->text().trimmed().isEmpty() == true) && (m_ptrEditPhone2->text().trimmed().isEmpty() == true)){
        str_message += "Agent phone can not be empty\n";
    };
    //
    if(m_ptrEditAgency->text().isEmpty() == true){
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
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByEmail(m_ptrEditEmail->text().trimmed());
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

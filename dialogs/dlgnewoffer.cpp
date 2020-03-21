#include <QMessageBox>
#include <QDate>
#include <QMenu>
#include <QAction>
//
#include "dlgnewoffer.h"
#include "commondef.h"
//
#include "processor/agencyprocessor.h"
#include "processor/agentprocessor.h"
#include "processor/countryprocessor.h"
#include "processor/townprocessor.h"
#include "processor/skillprocessor.h"
#include "processor/offerskillprocesor.h"
#include "processor/offerprocessor.h"
#include "processor/statusprocessor.h"
//
#include "operations/offerscaner.h"
//
#include "dto/statusdto.h"
#include "dto/attractivity.h"
//
#include "config/configuration.h"

DlgNewOffer::DlgNewOffer(QWidget *parent) :
    QDialog(parent)
{

}

DlgNewOffer::~DlgNewOffer(){

}

void DlgNewOffer::init(){
    setDlgSizes();
    setElementSizes();
    setDlgLayout();
    setMenuAction();
    //
    createWidgets();
    addWidgetsToLayout();
}

void DlgNewOffer::setMenuAction(){
    m_actionAcceptOfferCore.setText("Set position title");
    connect(&m_actionAcceptOfferCore,   SIGNAL(triggered()), this, SLOT(onClickBtnAcceptPositionDescription()));
    m_actionAcceptCountry.setText("Set country");
    connect(&m_actionAcceptCountry,    SIGNAL(triggered()), this, SLOT(onClickBtnAcceptCountry()));
    m_actionAcceptTown.setText("Set town");
    connect(&m_actionAcceptTown,     SIGNAL(triggered()), this, SLOT(onClickBtnAcceptTown()));
    m_actionAcceptSkills.setText("Add skill");
    connect(&m_actionAcceptSkills, SIGNAL(triggered()), this, SLOT(onClickBtnAcceptSkills()));
    //
    m_actionAcceptAgentName.setText("Set agent name");
    connect(&m_actionAcceptAgentName, SIGNAL(triggered()), this, SLOT(onClickBtnAcceptAgentName()));
    m_actionAcceptAgentEmail.setText("Set agent e-mail");
    connect(&m_actionAcceptAgentEmail, SIGNAL(triggered()), this, SLOT(onClickBtnAcceptAgentEmail()));
    m_actionAcceptAgentPhone1.setText("Set agent phone N 1");
    connect(&m_actionAcceptAgentPhone1, SIGNAL(triggered()), this, SLOT(onClickBtnAcceptAgentPhone1()));
    m_actionAcceptAgentPhone2.setText("Set agent phone N 2");
    connect(&m_actionAcceptAgentPhone2, SIGNAL(triggered()), this, SLOT(onClickBtnAcceptAgentPhone2()));
    m_actionAcceptAgencyName.setText("Set agency name");
    connect(&m_actionAcceptAgencyName, SIGNAL(triggered()), this, SLOT(onClickBtnAcceptAgencyName()));
    //
    m_actionScan.setText("Scan offer");
    connect(&m_actionScan, SIGNAL(triggered()), this, SLOT(onClickBtnScan()));
    //
    m_actionPaste.setText("Paste");
    connect(&m_actionPaste, SIGNAL(triggered()), &m_OfferEdit, SLOT(paste()));
}

void DlgNewOffer::setDlgLayout(){
    this->setLayout(&m_MainLayout);
}

void DlgNewOffer::setDlgSizes(){
    const int i_height = 600;
    //
    this->setMinimumHeight(i_height);
    this->setMaximumHeight(i_height);

    this->setMinimumWidth(1200);

}

void DlgNewOffer::setElementSizes(){
    m_iMinButtonWidth   = 60;
    m_iMinLabelWidth    = 80;
    m_iMinEditWidth     = 80;
    m_iMaxLabelHeight   = 25;
    m_iMaxElementWidth = 350;
}

void DlgNewOffer::createWidgets(){
    //
    createOfferWidgets();
    createAgentWidgets();
    createControlButtons();
}

void  DlgNewOffer::createOfferWidgets(){
    //m_OfferEdit = new QOfferEdit();
    //m_OfferEdit = new QPlainTextEdit();
    m_OfferEdit.setMinimumWidth(700);
    m_OfferEdit.setContextMenuPolicy(Qt::CustomContextMenu);
    connect(&m_OfferEdit, &QPlainTextEdit::copyAvailable, this, &DlgNewOffer::onSelectText);
    connect(&m_OfferEdit, &QWidget::customContextMenuRequested, this, &DlgNewOffer::onRequestUserMenu);
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
    m_EditOfferCore.setToolTip("Position name 'C++ Developer' for example");
    //
    m_ButtonAcceptOfferCore.setText("Accept selection");
    m_ButtonAcceptOfferCore.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptOfferCore.setEnabled(false);
    connect(&m_ButtonAcceptOfferCore, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptPositionDescription);
    //create offer country  line
    m_LblCountry.setText("Country");
    m_LblCountry.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditCountry.setToolTip("Target country name");
    m_EditCountry.setMinimumWidth(m_iMinEditWidth);
    m_EditCountry.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptCountry.setText("Accept selection");
    m_ButtonAcceptCountry.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptCountry.setEnabled(false);
    connect(&m_ButtonAcceptCountry, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptCountry);
    //create town country line
    m_LblTown.setText("Town");
    m_LblTown.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditTown.setToolTip("Town country name");
    m_EditTown.setMinimumWidth(m_iMinEditWidth);
    m_EditTown.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptTown.setText("Accept selection");
    m_ButtonAcceptTown.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonAcceptTown, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptTown);
    m_ButtonAcceptTown.setEnabled(false);
    //
    m_LblSkills.setText("Skills");
    m_LblSkills.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditSkills.setToolTip("Example:Java, C++, Qt...");
    m_EditSkills.setMinimumWidth(m_iMinEditWidth);
    m_EditSkills.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptSkills.setText("Add selection ");
    m_ButtonAcceptSkills.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonAcceptSkills, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptSkills);
    m_ButtonAcceptSkills.setEnabled(false);
    //
    m_LblRate.setText("Rate");
    m_LblRate.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditRate.setToolTip("add estimated rate for this position");
    m_EditRate.setMinimumWidth(30);
    m_EditRate.setMaximumWidth(40);
    m_EditRate.setAlignment(Qt::AlignRight);
    //
    m_LblStatus.setText("Status");
    m_LblStatus.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ComboStatus.setMinimumWidth(m_iMinEditWidth);
    m_ComboStatus.setMaximumWidth(m_iMaxElementWidth);
    //
    const StatusStorage& status_list = StatusProcessor::getInstance().getStorage();
    for (const auto& i : status_list){
        const int i_key = i->getId();
        const QString& str_status = i->getName();
        m_ComboStatus.addItem(str_status, QVariant(i_key));
    };
    //
    m_LblAttractivity.setText("Attractivity");
    m_LblAttractivity.setMinimumWidth(m_iMinLabelWidth);
    //
    m_ComboAttractivity.setMinimumWidth(m_iMinEditWidth);
    m_ComboAttractivity.setMaximumWidth(m_iMaxElementWidth);
    //
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_UNKNOWN), QVariant(static_cast<int>(ATTRACTIVITY_UNKNOWN)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_LOW), QVariant(static_cast<int>(ATTRACTIVITY_LOW)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_STANDARD), QVariant(static_cast<int>(ATTRACTIVITY_STANDARD)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_HIGH), QVariant(static_cast<int>(ATTRACTIVITY_HIGH)));
    m_ComboAttractivity.addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_VERY_HIGH), QVariant(static_cast<int>(ATTRACTIVITY_VERY_HIGH)));
    m_ComboAttractivity.setCurrentIndex(2); //standard
}

void  DlgNewOffer::createAgentWidgets(){
    m_LblAgentInfo.setText("Agent info");
    m_LblAgentInfo.setMinimumWidth(300);
    m_LblAgentInfo.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgentInfo.setMaximumHeight(m_iMaxLabelHeight);
    m_LblAgentInfo.setAlignment(Qt::AlignLeft);
    //
    m_LblAgentName.setText("Name");
    m_LblAgentName.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditAgentName.setToolTip("Add name of the contact agent");
    m_EditAgentName.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentName.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptAgentName.setText("Add selection");
    m_ButtonAcceptAgentName.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentName.setEnabled(false);
    connect(&m_ButtonAcceptAgentName, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentName);
    //
    m_LblAgentEmail.setText("E-mail");
    m_LblAgentEmail.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditAgentEmail.setToolTip("Add agent e-mail here");
    m_EditAgentEmail.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentEmail.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptAgentEmail.setText("Add selection ");
    m_ButtonAcceptAgentEmail.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentEmail.setEnabled(false);
    connect(&m_ButtonAcceptAgentEmail, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentEmail);
    //
    m_LblAgentPhone1.setText("Phone 1");
    m_LblAgentPhone1.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditAgentPhone1.setToolTip("Add agent phone number here");
    m_EditAgentPhone1.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentPhone1.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptAgentPhone1.setText("Add selection ");
    m_ButtonAcceptAgentPhone1.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentPhone1.setEnabled(false);
    connect(&m_ButtonAcceptAgentPhone1, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentPhone1);
    //
    m_LblAgentPhone2.setText("Phone 2");
    m_LblAgentPhone2.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditAgentPhone2.setToolTip("Add agent phone number here");
    m_EditAgentPhone2.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentPhone2.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ButtonAcceptAgentPhone2.setText("Add selection ");
    m_ButtonAcceptAgentPhone2.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentPhone2.setEnabled(false);
    connect(&m_ButtonAcceptAgentPhone2, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentPhone2);
    //
    m_LblAgencyName.setText("Agency");
    m_LblAgencyName.setMinimumWidth(m_iMinLabelWidth);
    //..
    m_EditAgencyName.setMinimumWidth(m_iMinEditWidth);
    m_EditAgencyName.setMaximumWidth(m_iMaxElementWidth);
    m_EditAgencyName.setToolTip("Select agency name");
    //..
    m_ButtonAcceptAgencyName.setText("Add selection ");
    m_ButtonAcceptAgencyName.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgencyName.setEnabled(false);
    connect(&m_ButtonAcceptAgencyName, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgencyName);
    //
    m_LblAgentRank.setText("Rank");
    m_LblAgentRank.setMinimumWidth(m_iMinLabelWidth);
    m_LblAgentRank.setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ComboAgentRank.setMinimumWidth(m_iMinButtonWidth);
    m_ComboAgentRank.addItem("Unknown");
    m_ComboAgentRank.setMaximumWidth(m_iMaxElementWidth);
    //
}

void  DlgNewOffer::createControlButtons(){
    m_ButtonSaveOffer.setText("Save offer ");
    m_ButtonSaveOffer.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonSaveOffer, &QPushButton::released, this, &DlgNewOffer::onClickBtnSaveOffer);
    //
    m_ButtonShowAgentInfo.setText("Show agent info");
    m_ButtonShowAgentInfo.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonShowAgentInfo.setEnabled(false);
    //
    m_ButtonShareOffer.setText("Share offer with colleagues");
    m_ButtonShareOffer.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonShareOffer.setEnabled(false);
    //
    m_ButtonScan.setText("Scan offer");
    m_ButtonScan.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonScan, &QPushButton::released, this, &DlgNewOffer::onClickBtnScan);
}

/*
                  0                                  1           2            3
+----------------------------------------------------------------------------------------+
!
! +---------------------------------------------+           offer info
! !                                             ! country    [       ]  accept selected
! !                                             ! town       [       ]  accept selected
! !                                             ! skills     [       ]  add selected
! !                                             ! rate:      [       ]  accept selected
! !                                             ! status:    < new, no CV >
! !                                             !            agent info:
! !                                             ! name       [       ]  accept selected
! !                                             ! e-mail     [       ]  accept selected
! !                                             ! phone1     [       ]  accept selected
! !                                             ! phone2     [       ]  accept selected
! !                                             ! agency     [       ]  accept selected
! !                                             ! country    [       ]  accept selected
! !                                             ! rank       <       >
! !                                             ! [             save offer            ]
! !                                             ! [          show agent info          ]
! !                                             ! [            share offer            ]
! !                                             !
! +---------------------------------------------+                                           !
+-------------------------------------------------------------------------------------------+


*/
void DlgNewOffer::addWidgetsToLayout(){
    //offer text
    //const int i_total_column_number = 4;
    const int i_total_row_number = 20;
    //
    int i_row = 0;
    //->addWidget(ptr_widget, row,column,rowSpan,columnSpan, aligment);
    m_MainLayout.addWidget(&m_OfferEdit,i_row,0,i_total_row_number,1);
    m_MainLayout.addWidget(&m_LblOfferInfo,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblOfferCore,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditOfferCore,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptOfferCore,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblCountry,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditCountry,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptCountry,i_row,3,1,1);
    //
    i_row++;
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
    m_MainLayout.addWidget(&m_LblAgentInfo,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentName,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgentName,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgentName,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentName,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgentName,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgentName,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentEmail,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgentEmail,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgentEmail,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentPhone1,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgentPhone1,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgentPhone1,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentPhone2,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgentPhone2,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgentPhone2,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgencyName,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgencyName,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgencyName,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentRank,i_row,1,1,1);
    m_MainLayout.addWidget(&m_ComboAgentRank,i_row,2,1,1);
    //------------------------------------------------------------------------------
    i_row++;
    m_MainLayout.addWidget(&m_ButtonSaveOffer,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonShowAgentInfo,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonShareOffer,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonScan,i_row,1,1,3);
}

void  DlgNewOffer::onSelectText(bool b_selected){
    m_ButtonAcceptOfferCore.setEnabled(b_selected);
    m_ButtonAcceptCountry.setEnabled(b_selected);
    m_ButtonAcceptTown.setEnabled(b_selected);
    m_ButtonAcceptSkills.setEnabled(b_selected);
    //
    m_ButtonAcceptAgencyName.setEnabled(b_selected);
    m_ButtonAcceptAgentName.setEnabled(b_selected);
    m_ButtonAcceptAgentEmail.setEnabled(b_selected);
    m_ButtonAcceptAgentPhone1.setEnabled(b_selected);
    m_ButtonAcceptAgentPhone2.setEnabled(b_selected);
    m_ButtonAcceptAgencyName.setEnabled(b_selected);
}

void  DlgNewOffer::onRequestUserMenu(){
    QMenu popup_menu(this);
    bool b_can_paste = m_OfferEdit.canPaste();
    m_actionPaste.setEnabled(b_can_paste);
    //
    const QString str_selected = m_OfferEdit.textCursor().selectedText();
    //
    popup_menu.addAction(&m_actionPaste);
    popup_menu.addSeparator();
    //
    if (str_selected.length() == 0){
        popup_menu.addAction(&m_actionScan);
    }else{
        popup_menu.addAction(&m_actionAcceptOfferCore);
        popup_menu.addAction(&m_actionAcceptCountry);
        popup_menu.addAction(&m_actionAcceptTown);
        popup_menu.addAction(&m_actionAcceptSkills);
        popup_menu.addSeparator();
        popup_menu.addAction(&m_actionAcceptAgentName);
        popup_menu.addAction(&m_actionAcceptAgentEmail);
        popup_menu.addAction(&m_actionAcceptAgentPhone1);
        popup_menu.addAction(&m_actionAcceptAgentPhone2);
        popup_menu.addAction(&m_actionAcceptAgencyName);
        popup_menu.addSeparator();
        popup_menu.addAction(&m_actionScan);
    };
    //
    popup_menu.exec(QCursor::pos());
}

QString DlgNewOffer::getSelectedPartOfOffer() const{
    QString str_selected = m_OfferEdit.textCursor().selectedText();
    str_selected = str_selected.normalized(QString::NormalizationForm_D);
    str_selected = str_selected.trimmed();
    return str_selected;
}

void DlgNewOffer::onClickBtnAcceptPositionDescription(){
    m_EditOfferCore.setText(this->getSelectedPartOfOffer());
}

void DlgNewOffer::onClickBtnAcceptCountry(){
    m_EditCountry.setText(this->getSelectedPartOfOffer());
}

void DlgNewOffer::onClickBtnAcceptTown(){
    m_EditTown.setText(this->getSelectedPartOfOffer());
}

void  DlgNewOffer::onClickBtnAcceptSkills(){
    const QString str_property = this->getSelectedPartOfOffer();
    const QString str_existing_skills = m_EditSkills.text();
    QString str_full_skills_list;
    //
    if (str_existing_skills.length() > 0){
        str_full_skills_list = str_existing_skills + SKILLS_SEPARATOR;
    };
    //
    str_full_skills_list +=str_property;
    m_EditSkills.setText(str_full_skills_list);
}

void DlgNewOffer::onClickBtnAcceptAgentName(){
    const QString str_name = this->getSelectedPartOfOffer();
    //todo: make right register here
    m_EditAgentName.setText(str_name);
}

void DlgNewOffer::onClickBtnAcceptAgentEmail(){
    const QString str_email = this->getSelectedPartOfOffer();
    //todo: check e-mail
    m_EditAgentEmail.setText(str_email);
}

void DlgNewOffer::onClickBtnAcceptAgentPhone1(){
    //todo: check if it is a phone
    m_EditAgentPhone1.setText(this->getSelectedPartOfOffer());
}

void DlgNewOffer::onClickBtnAcceptAgentPhone2(){
    //todo: check if it is a phone
    m_EditAgentPhone2.setText(this->getSelectedPartOfOffer());
}

void DlgNewOffer::onClickBtnAcceptAgencyName(){
    m_EditAgencyName.setText(this->getSelectedPartOfOffer());
}

void  DlgNewOffer::onClickBtnScan(){
    //todo: implement it
    OfferScaner scaner;
    scaner.parse(m_OfferEdit.toPlainText());
    //
    m_OfferEdit.setPlainText(scaner.getModifiedText());
    m_EditSkills.setText(scaner.getSkills());
    //
    if (scaner.getAgentEmail().length() > 0){
        //for prevent double saving operations
        m_dtoAgent.setId(scaner.getAgentId());
        m_dtoAgent.setAgencyId(scaner.getAgentId());
        //for visualisation
        m_EditAgentEmail.setText(scaner.getAgentEmail());
        m_EditAgentName.setText(scaner.getAgentName());
        m_EditAgentPhone1.setText(scaner.getAgentPhone1());
        m_EditAgentPhone2.setText(scaner.getAgentPhone2());
    };
    m_EditAgencyName.setText(scaner.getAgencyName());
    m_EditTown.setText(scaner.getTownName());
}

void  DlgNewOffer::onClickBtnSaveOffer(){
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Ok);
    QString str_message_text;
    //
    if (m_EditOfferCore.text().isEmpty() == true){
        str_message_text = "Position title can not be empty\n";
    };
    //
    if(m_EditCountry.text().isEmpty() == true){
        str_message_text = str_message_text + "Country can not be empty\n";
    };
    //
    if(m_EditSkills.text().isEmpty() == true){
        str_message_text = str_message_text + "Skills list can not be empty\n";
    };
    //check agent info
    if(m_EditAgencyName.text().isEmpty() == true){
        str_message_text = str_message_text + "Agent name can not be empty\n";
    };
    if(m_EditAgentEmail.text().isEmpty() == true){
        str_message_text = str_message_text + "Agent e-mail can not be empty\n";
    };
    if((m_EditAgentPhone1.text().isEmpty() == true) && (m_EditAgentPhone2.text().isEmpty() == true)){
        str_message_text = str_message_text + "Agent phone can not be empty\n";
    };
    if(m_EditAgencyName.text().isEmpty() == true){
        str_message_text = str_message_text + "Agency name can not be empty\n";
    };
    //
    if (str_message_text.isEmpty() == false){
        box.setText(str_message_text);
        box.exec();
        return;
    };
    //
    saveAgentInfo();
    saveOffer();
    //
    emit addedNewOffer();
    return;
}

void DlgNewOffer::saveOffer(){
    const int           i_country_id    = CountryProcessor::getInstance().add(m_EditCountry.text().trimmed());
    const int           i_town_id       = TownProcessor::getInstance().add(m_EditTown.text().trimmed());
    const QStringList   str_l_skills    =  m_EditSkills.text().split(",", QString::SkipEmptyParts);
    const SkillsList    skill_list_ids  = SkillProcessor::getInstance().add(str_l_skills);
    //
    m_dtoOffer.setAgentId(m_dtoAgent.getId());
    m_dtoOffer.setCreationDate(QDate::currentDate());
    m_dtoOffer.setPositionTitle(m_EditOfferCore.text());
    m_dtoOffer.setCountryId(i_country_id);
    m_dtoOffer.setTownId(i_town_id);
    //m_dtoOffer.setSkillsListIDs(skill_list_ids);
    //
    const QString str_rate = m_EditRate.text();
    m_dtoOffer.setRate(str_rate.toInt());
    const int i_attractivity = m_ComboAttractivity.currentData().toInt();
    m_dtoOffer.setAttractivity(i_attractivity);
    const int i_status = m_ComboStatus.currentData().toInt();
    m_dtoOffer.setStatusId(i_status);
    const int i_offer_id = OfferProcessor::getInstance().add(&m_dtoOffer);
    m_dtoOffer.setId(i_offer_id);
    OfferSkillProcesor::getInstance().add(i_offer_id,skill_list_ids);
    //
    this->close();
}

void DlgNewOffer::saveAgentInfo(){
    if (m_dtoAgent.getId() != VALUE_UNDEFINED){
        return; //agent and agency already found by scaner
    };
    //
    int i_agency_id = AgencyProcessor::getInstance().add(m_EditAgencyName.text().trimmed());
    //
    m_dtoAgent.setName(m_EditAgentName.text());
    m_dtoAgent.setEMail( m_EditAgentEmail.text());
    m_dtoAgent.setPhone1(m_EditAgentPhone1.text());
    m_dtoAgent.setPhone2(m_EditAgentPhone2.text());
    m_dtoAgent.setAgencyId(i_agency_id);
    //
    int id = AgentProcessor::getInstance().add(&m_dtoAgent);
    m_dtoAgent.setId(id);
}

void DlgNewOffer::closeEvent(QCloseEvent *event){
    clearFields();
    QDialog::closeEvent(event);
}

void DlgNewOffer::clearFields(){
    const QString str_empty_txt = "";
    m_OfferEdit.setPlainText(str_empty_txt);
    m_EditOfferCore.setText(str_empty_txt);
    m_EditCountry.setText(str_empty_txt);
    m_EditTown.setText(str_empty_txt);
    m_EditSkills.setText(str_empty_txt);
    m_EditRate.setText(str_empty_txt);
    m_EditAgentName.setText(str_empty_txt);
    m_EditAgentEmail.setText(str_empty_txt);
    m_EditAgentPhone1.setText(str_empty_txt);
    m_EditAgentPhone2.setText(str_empty_txt);
    m_EditAgencyName.setText(str_empty_txt);
}

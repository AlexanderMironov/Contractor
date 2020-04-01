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
//
#include "dto/countrydto.h"
#include "processor/countryprocessor.h"
//
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
#include "dto/agentrank.h"
//
#include "config/configuration.h"

DlgNewOffer::DlgNewOffer(QWidget *parent) :
    QDialog(parent),
    m_Spacer(100,325)
{
    m_bOfferSaved = false;
    m_bAgentAdded = false;
    this->setWindowTitle("Create new job offer");
    //m_MainLayout = nullptr;
}

DlgNewOffer::~DlgNewOffer(){
    detachElements();
}

void DlgNewOffer::detachElements()
{
    m_MainLayout.removeWidget(&m_LblnsertOffer);
    m_MainLayout.removeWidget(&m_OfferEdit);
    m_MainLayout.removeWidget(&m_LblOfferInfo);
    //
    m_MainLayout.removeWidget(&m_LblPositonTitle);
    m_MainLayout.removeWidget(&m_EditPositonTitle);
    m_MainLayout.removeWidget(&m_ButtonAcceptPositonTitle);
    //
    m_MainLayout.removeWidget(&m_LblCountry);
    m_MainLayout.removeWidget(&m_ComboCountry);
    //
    m_MainLayout.removeWidget(&m_LblTown);
    m_MainLayout.removeWidget(&m_EditTown);
    m_MainLayout.removeWidget(&m_ButtonAcceptTown);
    //
    m_MainLayout.removeWidget(&m_LblSkills);
    m_MainLayout.removeWidget(&m_EditSkills);
    m_MainLayout.removeWidget(&m_ButtonAcceptSkills);
    m_MainLayout.removeWidget(&m_LblRate);
    m_MainLayout.removeWidget(&m_EditRate);
    //
    m_MainLayout.removeWidget(&m_LblStatus);
    m_MainLayout.removeWidget(&m_ComboStatus);
    //
    m_MainLayout.removeWidget(&m_LblAttractivity);
    m_MainLayout.removeWidget(&m_ComboAttractivity);
    m_MainLayout.removeItem(&m_Spacer);
    m_MainLayout.removeWidget(&m_LblnsertComment);
    m_MainLayout.removeWidget(&m_CommentEdit);
    m_MainLayout.removeWidget(&m_LblAgentInfo);
    //
    m_MainLayout.removeWidget(&m_LblAgentName);
    m_MainLayout.removeWidget(&m_EditAgentName);
    m_MainLayout.removeWidget(&m_ButtonAcceptAgentName);
    //
    m_MainLayout.removeWidget(&m_LblAgentEmail);
    m_MainLayout.removeWidget(&m_EditAgentEmail);
    m_MainLayout.removeWidget(&m_ButtonAcceptAgentEmail);
    //
    m_MainLayout.removeWidget(&m_LblAgentPhone1);
    m_MainLayout.removeWidget(&m_EditAgentPhone1);
    m_MainLayout.removeWidget(&m_ButtonAcceptAgentPhone1);
    //
    m_MainLayout.removeWidget(&m_LblAgentPhone2);
    m_MainLayout.removeWidget(&m_EditAgentPhone2);
    m_MainLayout.removeWidget(&m_ButtonAcceptAgentPhone2);
    //
    m_MainLayout.removeWidget(&m_LblAgencyName);
    m_MainLayout.removeWidget(&m_EditAgencyName);
    m_MainLayout.removeWidget(&m_ButtonAcceptAgencyName);
    //
    m_MainLayout.removeWidget(&m_LblAgentRank);
    m_MainLayout.removeWidget(&m_ComboAgentRank);
    //
    m_MainLayout.removeWidget(&m_ButtonScan);
    //
    m_MainLayout.removeWidget(&m_ButtonSaveOffer);
    //
    m_MainLayout.removeWidget(&m_ButtonClose);
}

void DlgNewOffer::init(){
/*
    if(nullptr != m_MainLayout){
        return; //already done
    };
*/
    //
    setDlgSizes();
    setElementSizes();
    setDlgLayout();
    createWidgets();
    setMenuAction();
    //
    addWidgetsToLayout();
}

void DlgNewOffer::setMenuAction(){
    m_actionAcceptOfferCore.setText("Set position title");
    connect(&m_actionAcceptOfferCore,   SIGNAL(triggered()), this, SLOT(onClickBtnAcceptPositionTitle()));
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
    //m_MainLayout = new QGridLayout();
    this->setLayout(&m_MainLayout);
}

void DlgNewOffer::setDlgSizes(){
    const int i_height = 600;
    //
    this->setMinimumHeight(i_height);
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
    //
    //m_EditStatusBar = new QLineEdit();
    m_EditStatusBar.setEnabled(false);
}

void DlgNewOffer::onAddNewCountry(){

    m_ComboCountry.clear();
    //
    const CountryStorage&  country_storage = CountryProcessor::getInstance().getStorage();
    CountryStorage::const_iterator i = country_storage.constBegin();
    while(i != country_storage.constEnd()){
        CountryDTO* ptr_country = i.value();
        m_ComboCountry.addItem(ptr_country->getName(), QVariant(ptr_country->getId()));
        i++;
    };
}


void  DlgNewOffer::createOfferWidgets(){
    const int i_left_side_max_width = 700;
    //m_LblnsertOffer = new QLabel();
    m_LblnsertOffer.setText("Insert job offer:");
    m_LblnsertOffer.setMinimumWidth(i_left_side_max_width);
    //m_OfferEdit = new QPlainTextEdit();
    m_OfferEdit.setMinimumWidth(i_left_side_max_width);
    m_OfferEdit.setContextMenuPolicy(Qt::CustomContextMenu);
    connect(&m_OfferEdit, &QPlainTextEdit::copyAvailable, this, &DlgNewOffer::onSelectText);
    connect(&m_OfferEdit, &QWidget::customContextMenuRequested, this, &DlgNewOffer::onRequestUserMenu);
    //
    //m_LblnsertComment = new QLabel();
    m_LblnsertComment.setText("Insert comments:");
    m_LblnsertComment.setMinimumWidth(i_left_side_max_width);
   // m_CommentEdit = new QPlainTextEdit();
    m_CommentEdit.setMinimumWidth(i_left_side_max_width);
    //
    //m_LblOfferInfo = new QLabel();
    m_LblOfferInfo.setText("Offer info");
    m_LblOfferInfo.setMinimumWidth(300);
    m_LblOfferInfo.setMaximumWidth(m_iMaxElementWidth);
    m_LblOfferInfo.setMaximumHeight(m_iMaxLabelHeight);
    m_LblOfferInfo.setAlignment(Qt::AlignLeft);
    //create offer core
    //m_LblPositonTitle = new QLabel();
    m_LblPositonTitle.setText("Position title");
    m_LblPositonTitle.setMinimumWidth(m_iMinLabelWidth);
    //..
   // m_EditPositonTitle = new QLineEdit();
    m_EditPositonTitle.setMinimumWidth(m_iMinEditWidth);
    m_EditPositonTitle.setMaximumWidth(m_iMaxElementWidth);
    m_EditPositonTitle.setToolTip("Position name 'C++ Developer' for example");
    //
    //m_ButtonAcceptPositonTitle = new QPushButton();
    m_ButtonAcceptPositonTitle.setText("Accept selection");
    m_ButtonAcceptPositonTitle.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptPositonTitle.setEnabled(false);
    connect(&m_ButtonAcceptPositonTitle, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptPositionTitle);
    //create offer country  line
    //m_LblCountry = new QLabel();
    m_LblCountry.setText("Country");
    m_LblCountry.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_ComboCountry = new QComboBox();
    m_ComboCountry.setToolTip("Coose country of job offer");
    m_ComboCountry.setMinimumWidth(m_iMinEditWidth);
    m_ComboCountry.setMaximumWidth(m_iMaxElementWidth);
    onAddNewCountry();
    //..
    //create town country line
    //m_LblTown = new QLabel();
    m_LblTown.setText("Town");
    m_LblTown.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditTown  = new QLineEdit();
    m_EditTown.setToolTip("Town country name");
    m_EditTown.setMinimumWidth(m_iMinEditWidth);
    m_EditTown.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ButtonAcceptTown = new QPushButton();
    m_ButtonAcceptTown.setText("Accept selection");
    m_ButtonAcceptTown.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonAcceptTown, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptTown);
    m_ButtonAcceptTown.setEnabled(false);
    //
    //m_LblSkills  = new QLabel();
    m_LblSkills.setText("Skills");
    m_LblSkills.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditSkills = new QLineEdit();
    m_EditSkills.setToolTip("Example:Java, C++, Qt...");
    m_EditSkills.setMinimumWidth(m_iMinEditWidth);
    m_EditSkills.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ButtonAcceptSkills = new QPushButton();
    m_ButtonAcceptSkills.setText("Add selection ");
    m_ButtonAcceptSkills.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonAcceptSkills, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptSkills);
    m_ButtonAcceptSkills.setEnabled(false);
    //
    //m_LblRate = new QLabel();
    m_LblRate.setText("Rate");
    m_LblRate.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditRate = new QLineEdit();
    m_EditRate.setToolTip("add estimated rate for this position");
    m_EditRate.setMinimumWidth(30);
    m_EditRate.setMaximumWidth(40);
    m_EditRate.setAlignment(Qt::AlignRight);
    m_EditRate.setText("0"); //usially rate on start is unknown
    //
    //m_LblStatus = new QLabel();
    m_LblStatus.setText("Status");
    m_LblStatus.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_ComboStatus = new QComboBox();
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
    //m_LblAttractivity = new QLabel();
    m_LblAttractivity.setText("Attractivity");
    m_LblAttractivity.setMinimumWidth(m_iMinLabelWidth);
    //
   // m_ComboAttractivity = new QComboBox();
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
    //m_Spacer = new QSpacerItem(100,325);
    //
    //m_LblAgentInfo = new QLabel();
    m_LblAgentInfo.setText("Agent info");
    m_LblAgentInfo.setMinimumWidth(300);
    m_LblAgentInfo.setMaximumWidth(m_iMaxElementWidth);
    m_LblAgentInfo.setMaximumHeight(m_iMaxLabelHeight);
    m_LblAgentInfo.setAlignment(Qt::AlignLeft);
    //
    //m_LblAgentName = new QLabel();
    m_LblAgentName.setText("Name");
    m_LblAgentName.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditAgentName = new QLineEdit();
    m_EditAgentName.setToolTip("Add name of the contact agent");
    m_EditAgentName.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentName.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ButtonAcceptAgentName = new QPushButton();
    m_ButtonAcceptAgentName.setText("Add selection");
    m_ButtonAcceptAgentName.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentName.setEnabled(false);
    connect(&m_ButtonAcceptAgentName, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentName);
    //
    //m_LblAgentEmail = new QLabel();
    m_LblAgentEmail.setText("E-mail");
    m_LblAgentEmail.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditAgentEmail = new QLineEdit();
    m_EditAgentEmail.setToolTip("Add agent e-mail here");
    m_EditAgentEmail.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentEmail.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ButtonAcceptAgentEmail = new QPushButton();
    m_ButtonAcceptAgentEmail.setText("Add selection ");
    m_ButtonAcceptAgentEmail.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentEmail.setEnabled(false);
    connect(&m_ButtonAcceptAgentEmail, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentEmail);
    //
    //m_LblAgentPhone1 = new QLabel();
    m_LblAgentPhone1.setText("Phone 1");
    m_LblAgentPhone1.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditAgentPhone1 = new QLineEdit();
    m_EditAgentPhone1.setToolTip("Add agent phone number here");
    m_EditAgentPhone1.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentPhone1.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ButtonAcceptAgentPhone1 = new QPushButton();
    m_ButtonAcceptAgentPhone1.setText("Add selection ");
    m_ButtonAcceptAgentPhone1.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentPhone1.setEnabled(false);
    connect(&m_ButtonAcceptAgentPhone1, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentPhone1);
    //
    //m_LblAgentPhone2 = new QLabel();
    m_LblAgentPhone2.setText("Phone 2");
    m_LblAgentPhone2.setMinimumWidth(m_iMinLabelWidth);
    //..
   // m_EditAgentPhone2 = new QLineEdit();
    m_EditAgentPhone2.setToolTip("Add agent phone number here");
    m_EditAgentPhone2.setMinimumWidth(m_iMinEditWidth);
    m_EditAgentPhone2.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ButtonAcceptAgentPhone2 = new QPushButton();
    m_ButtonAcceptAgentPhone2.setText("Add selection ");
    m_ButtonAcceptAgentPhone2.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgentPhone2.setEnabled(false);
    connect(&m_ButtonAcceptAgentPhone2, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentPhone2);
    //
    //m_LblAgencyName = new QLabel();
    m_LblAgencyName.setText("Agency");
    m_LblAgencyName.setMinimumWidth(m_iMinLabelWidth);
    //..
    //m_EditAgencyName = new QLineEdit();
    m_EditAgencyName.setMinimumWidth(m_iMinEditWidth);
    m_EditAgencyName.setMaximumWidth(m_iMaxElementWidth);
    m_EditAgencyName.setToolTip("Select agency name");
    //..
    //m_ButtonAcceptAgencyName = new QPushButton();
    m_ButtonAcceptAgencyName.setText("Add selection ");
    m_ButtonAcceptAgencyName.setMinimumWidth(m_iMinButtonWidth);
    m_ButtonAcceptAgencyName.setEnabled(false);
    connect(&m_ButtonAcceptAgencyName, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgencyName);
    //
    //m_LblAgentRank = new QLabel();
    m_LblAgentRank.setText("Rank");
    m_LblAgentRank.setMinimumWidth(m_iMinLabelWidth);
    m_LblAgentRank.setMaximumWidth(m_iMaxElementWidth);
    //..
    //m_ComboAgentRank = new QComboBox();
    m_ComboAgentRank.setMinimumWidth(m_iMinButtonWidth);
    m_ComboAgentRank.setMaximumWidth(m_iMaxElementWidth);
    m_ComboAgentRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankUnknown), QVariant(static_cast<int>(AGENT_RANK::RankUnknown)));
    m_ComboAgentRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryBad), QVariant(static_cast<int>(AGENT_RANK::RankVeryBad)));
    m_ComboAgentRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankBad), QVariant(static_cast<int>(AGENT_RANK::RankBad)));
    m_ComboAgentRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankNeutral), QVariant(static_cast<int>(AGENT_RANK::RankNeutral)));
    m_ComboAgentRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankGood), QVariant(static_cast<int>(AGENT_RANK::RankGood)));
    m_ComboAgentRank.addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryGood), QVariant(static_cast<int>(AGENT_RANK::RankVeryGood)));
    m_ComboAgentRank.setCurrentIndex(0);
}

void  DlgNewOffer::createControlButtons(){
    //m_ButtonScan = new QPushButton();
    m_ButtonScan.setText("Scan offer");
    m_ButtonScan.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonScan, &QPushButton::released, this, &DlgNewOffer::onClickBtnScan);
    //
    //m_ButtonSaveOffer = new QPushButton();
    m_ButtonSaveOffer.setText("Save offer ");
    m_ButtonSaveOffer.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonSaveOffer, &QPushButton::released, this, &DlgNewOffer::onClickBtnSaveOffer);
    //
    //m_ButtonClose = new QPushButton();
    m_ButtonClose.setText("Close window");
    m_ButtonClose.setMinimumWidth(m_iMinButtonWidth);
    connect(&m_ButtonClose, &QPushButton::released, this, &DlgNewOffer::close);
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
    //const int i_total_row_number = 21;
    //
    int i_row = 0;
    //->addWidget(ptr_widget, row,column,rowSpan,columnSpan, aligment);
    m_MainLayout.addWidget(&m_LblnsertOffer,i_row,0,1,1);
    m_MainLayout.addWidget(&m_LblOfferInfo,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_OfferEdit,i_row,0,11,1);
    //
    m_MainLayout.addWidget(&m_LblPositonTitle,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditPositonTitle,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptPositonTitle,i_row,3,1,1);
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
    m_MainLayout.addItem(&m_Spacer,i_row,1,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_LblAgentInfo,i_row,1,1,3);
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
    m_MainLayout.addWidget(&m_LblnsertComment,i_row,0,1,1);
    //
    m_MainLayout.addWidget(&m_LblAgentPhone1,i_row,1,1,1);
    m_MainLayout.addWidget(&m_EditAgentPhone1,i_row,2,1,1);
    m_MainLayout.addWidget(&m_ButtonAcceptAgentPhone1,i_row,3,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_CommentEdit,i_row,0,6,1);
    //
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
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonScan,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonSaveOffer,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonClose,i_row,1,1,3);
    //
    i_row++;
    m_MainLayout.addWidget(&m_EditStatusBar,i_row,0,1,4);
}

void  DlgNewOffer::onSelectText(bool b_selected){
    m_ButtonAcceptPositonTitle.setEnabled(b_selected);
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

void DlgNewOffer::onClickBtnAcceptPositionTitle(){
    m_EditPositonTitle.setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}
/*
void DlgNewOffer::onClickBtnAcceptCountry(){

}
*/
void DlgNewOffer::onClickBtnAcceptTown(){
    m_EditTown.setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
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
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentName(){
    const QString str_name = this->getSelectedPartOfOffer();
    m_EditAgentName.setText(str_name);
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentEmail(){
    const QString str_email = this->getSelectedPartOfOffer();
    //todo: check e-mail
    m_EditAgentEmail.setText(str_email);
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentPhone1(){
    //todo: check if it is a phone
    m_EditAgentPhone1.setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentPhone2(){
    //todo: check if it is a phone
    m_EditAgentPhone2.setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgencyName(){
    m_EditAgencyName.setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void  DlgNewOffer::onClickBtnScan(){
    OfferScaner scaner;
    scaner.parse(m_OfferEdit.toPlainText());
    //
    m_OfferEdit.setPlainText(scaner.getModifiedText());
    m_EditSkills.setText(scaner.getSkills());
    //
    if (scaner.getAgencyName().length() > 0){
        m_EditAgencyName.setText(scaner.getAgencyName());
        m_dtoAgent.setAgencyId(scaner.getAgentId());
    };
    //
    if (scaner.getAgentEmail().length() > 0){
        //for prevent double saving operations
        m_dtoAgent.setId(scaner.getAgentId());
        m_bAgentAdded = false;
        //for visualisation
        m_EditAgentEmail.setText(scaner.getAgentEmail());
        m_EditAgentName.setText(scaner.getAgentName());
        m_EditAgentPhone1.setText(scaner.getAgentPhone1());
        m_EditAgentPhone2.setText(scaner.getAgentPhone2());
        //
        for (int i = 0; i < m_ComboAgentRank.count(); ++i){
            QVariant current_rank = m_ComboAgentRank.itemData(i,Qt::UserRole);
            if (current_rank.toInt() == scaner.getAgentRank()){
                m_ComboAgentRank.setCurrentIndex(i);
                break;
            };
        };
    };
    //
    m_EditTown.setText(scaner.getTownName());
    //
    m_EditStatusBar.setText("Offer scanned");
}

void  DlgNewOffer::onClickBtnSaveOffer(){
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Ok);
    QString str_message_text;
    //
    if (m_EditPositonTitle.text().isEmpty() == true){
        str_message_text = "Position title can not be empty\n";
    };
    //
    if(m_ComboCountry.currentIndex() == -1){
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
    const bool b_agent_info_saved = saveAgentInfo();
    if (true == b_agent_info_saved){
        if (saveOffer() == true){
            this->close();
        };
    };
    //
    return;
}

bool DlgNewOffer::saveOffer(){
    const int           i_country_id    = m_ComboCountry.currentData(Qt::UserRole).toInt();
    const int           i_town_id       = TownProcessor::getInstance().add(m_EditTown.text().trimmed());
    const QStringList   str_l_skills    =  m_EditSkills.text().split(",", QString::SkipEmptyParts);
    const SkillsList    skill_list_ids  = SkillProcessor::getInstance().add(str_l_skills);
    //
    m_dtoOffer.setAgentId(m_dtoAgent.getId());
    m_dtoOffer.setCreationDate(QDate::currentDate());
    m_dtoOffer.setPositionTitle(m_EditPositonTitle.text());
    QString str_offer_text = m_OfferEdit.toPlainText();
    if (str_offer_text.length() > 2000){
        str_offer_text = str_offer_text.mid(MAX_TEXT_LENGTH);
    };
    m_dtoOffer.setDescription(str_offer_text);
    //
    QString str_comment_text = m_CommentEdit.toPlainText();
    if (str_comment_text.length() > 2000){
        str_comment_text = str_comment_text.mid(MAX_TEXT_LENGTH);
    };
    m_dtoOffer.setComments(str_comment_text);
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

    if(VALUE_UNDEFINED != i_offer_id){
        m_dtoOffer.setId(i_offer_id);
        OfferSkillProcesor::getInstance().add(i_offer_id,skill_list_ids);
        m_bOfferSaved = true;
        return true;
    };
    return false;
}

bool DlgNewOffer::saveAgentInfo(){
    if (m_dtoAgent.getId() != VALUE_UNDEFINED){
        return true; //agent and agency already found by scaner
    };
    //
    //agent was not founded by scaner (user did not make scan) but exists in the database, no reason to add it twice
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByEmail(m_EditAgentEmail.text());
    if (nullptr != ptr_agent){
        m_bAgentAdded = false;
        m_dtoAgent.setId(ptr_agent->getId());
        return true;
    };
    //
    int i_agency_id = AgencyProcessor::getInstance().add(m_EditAgencyName.text().trimmed());
    if(VALUE_UNDEFINED == i_agency_id){
        return false; //can not add new agency to database
    }
    //
    m_dtoAgent.setName(m_EditAgentName.text());
    m_dtoAgent.setEMail( m_EditAgentEmail.text());
    m_dtoAgent.setPhone1(m_EditAgentPhone1.text());
    m_dtoAgent.setPhone2(m_EditAgentPhone2.text());
    m_dtoAgent.setAgencyId(i_agency_id);
    const QVariant agent_rank = m_ComboAgentRank.currentData();
    m_dtoAgent.setRank(agent_rank.toInt());
    //
    int id = AgentProcessor::getInstance().add(&m_dtoAgent);
    if(VALUE_UNDEFINED != id){
        m_dtoAgent.setId(id);
        m_bAgentAdded = true;
        return true;
    };
    //new agent was not added to the database, we can not save offer
    return false;
}

void DlgNewOffer::closeEvent(QCloseEvent *event){
    if((false == m_bOfferSaved) && (m_EditPositonTitle.text().length() > 0)){
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
    clearFields();
    event->accept();
}

bool DlgNewOffer::isbOfferSaved() const{
    return m_bOfferSaved;
}

bool DlgNewOffer::isNewAgentAdded(){
    return m_bAgentAdded;
}

void DlgNewOffer::clearFields(){
    const QString str_empty_txt = "";
    m_OfferEdit.setPlainText(str_empty_txt);
    m_EditPositonTitle.setText(str_empty_txt);
    m_ComboCountry.setCurrentIndex(-1);
    m_EditTown.setText(str_empty_txt);
    m_EditSkills.setText(str_empty_txt);
    m_EditRate.setText("0");
    m_EditAgentName.setText(str_empty_txt);
    m_EditAgentEmail.setText(str_empty_txt);
    m_EditAgentPhone1.setText(str_empty_txt);
    m_EditAgentPhone2.setText(str_empty_txt);
    m_EditAgencyName.setText(str_empty_txt);
    m_dtoOffer.reset();
    m_dtoAgent.reset();
}

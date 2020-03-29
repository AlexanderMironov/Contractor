#include <QMessageBox>
#include <QDate>
#include <QMenu>
#include <QAction>
//
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
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
    QDialog(parent)
{
    m_bOfferSaved = false;
    m_bAgentAdded = false;
    this->setWindowTitle("Create new job offer");
    m_ptrMainLayout = nullptr;
}

DlgNewOffer::~DlgNewOffer(){

}

void DlgNewOffer::init(){
    if(nullptr != m_ptrMainLayout){
        return; //already done
    };
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
    connect(&m_actionPaste, SIGNAL(triggered()), m_ptrOfferEdit, SLOT(paste()));
}

void DlgNewOffer::setDlgLayout(){
    m_ptrMainLayout = new QGridLayout();
    this->setLayout(m_ptrMainLayout);
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
}

void DlgNewOffer::onAddNewCountry(){

    m_ptrComboCountry->clear();
    //
    const CountryStorage&  country_storage = CountryProcessor::getInstance().getStorage();
    CountryStorage::const_iterator i = country_storage.constBegin();
    while(i != country_storage.constEnd()){
        CountryDTO* ptr_country = i.value();
        m_ptrComboCountry->addItem(ptr_country->getName(), QVariant(ptr_country->getId()));
        i++;
    };
}

void  DlgNewOffer::createOfferWidgets(){
    const int i_left_side_max_width = 700;
    m_ptrLblnsertOffer = new QLabel();
    m_ptrLblnsertOffer->setText("Insert job offer:");
    m_ptrLblnsertOffer->setMinimumWidth(i_left_side_max_width);
    m_ptrOfferEdit = new QPlainTextEdit();
    m_ptrOfferEdit->setMinimumWidth(i_left_side_max_width);
    m_ptrOfferEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_ptrOfferEdit, &QPlainTextEdit::copyAvailable, this, &DlgNewOffer::onSelectText);
    connect(m_ptrOfferEdit, &QWidget::customContextMenuRequested, this, &DlgNewOffer::onRequestUserMenu);
    //
    m_ptrLblnsertComment = new QLabel();
    m_ptrLblnsertComment->setText("Insert comments:");
    m_ptrLblnsertComment->setMinimumWidth(i_left_side_max_width);
    m_ptrCommentEdit = new QPlainTextEdit();
    m_ptrCommentEdit->setMinimumWidth(i_left_side_max_width);
    //
    m_ptrLblOfferInfo = new QLabel();
    m_ptrLblOfferInfo->setText("Offer info");
    m_ptrLblOfferInfo->setMinimumWidth(300);
    m_ptrLblOfferInfo->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblOfferInfo->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblOfferInfo->setAlignment(Qt::AlignLeft);
    //create offer core
    m_ptrLblPositonTitle = new QLabel();
    m_ptrLblPositonTitle->setText("Position title");
    m_ptrLblPositonTitle->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditPositonTitle = new QLineEdit();
    m_ptrEditPositonTitle->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditPositonTitle->setMaximumWidth(m_iMaxElementWidth);
    m_ptrEditPositonTitle->setToolTip("Position name 'C++ Developer' for example");
    //
    m_ptrButtonAcceptPositonTitle = new QPushButton();
    m_ptrButtonAcceptPositonTitle->setText("Accept selection");
    m_ptrButtonAcceptPositonTitle->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonAcceptPositonTitle->setEnabled(false);
    connect(m_ptrButtonAcceptPositonTitle, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptPositionTitle);
    //create offer country  line
    m_ptrLblCountry = new QLabel();
    m_ptrLblCountry->setText("Country");
    m_ptrLblCountry->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrComboCountry = new QComboBox();
    m_ptrComboCountry->setToolTip("Coose country of job offer");
    m_ptrComboCountry->setMinimumWidth(m_iMinEditWidth);
    m_ptrComboCountry->setMaximumWidth(m_iMaxElementWidth);
    onAddNewCountry();
    //..
    //create town country line
    m_ptrLblTown = new QLabel();
    m_ptrLblTown->setText("Town");
    m_ptrLblTown->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditTown  = new QLineEdit();
    m_ptrEditTown->setToolTip("Town country name");
    m_ptrEditTown->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditTown->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrButtonAcceptTown = new QPushButton();
    m_ptrButtonAcceptTown->setText("Accept selection");
    m_ptrButtonAcceptTown->setMinimumWidth(m_iMinButtonWidth);
    connect(m_ptrButtonAcceptTown, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptTown);
    m_ptrButtonAcceptTown->setEnabled(false);
    //
    m_ptrLblSkills  = new QLabel();
    m_ptrLblSkills->setText("Skills");
    m_ptrLblSkills->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditSkills = new QLineEdit();
    m_ptrEditSkills->setToolTip("Example:Java, C++, Qt...");
    m_ptrEditSkills->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditSkills->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrButtonAcceptSkills = new QPushButton();
    m_ptrButtonAcceptSkills->setText("Add selection ");
    m_ptrButtonAcceptSkills->setMinimumWidth(m_iMinButtonWidth);
    connect(m_ptrButtonAcceptSkills, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptSkills);
    m_ptrButtonAcceptSkills->setEnabled(false);
    //
    m_ptrLblRate = new QLabel();
    m_ptrLblRate->setText("Rate");
    m_ptrLblRate->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditRate = new QLineEdit();
    m_ptrEditRate->setToolTip("add estimated rate for this position");
    m_ptrEditRate->setMinimumWidth(30);
    m_ptrEditRate->setMaximumWidth(40);
    m_ptrEditRate->setAlignment(Qt::AlignRight);
    m_ptrEditRate->setText("0"); //usially rate on start is unknown
    //
    m_ptrLblStatus = new QLabel();
    m_ptrLblStatus->setText("Status");
    m_ptrLblStatus->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrComboStatus = new QComboBox();
    m_ptrComboStatus->setMinimumWidth(m_iMinEditWidth);
    m_ptrComboStatus->setMaximumWidth(m_iMaxElementWidth);
    //
    const StatusStorage& status_list = StatusProcessor::getInstance().getStorage();
    for (const auto& i : status_list){
        const int i_key = i->getId();
        const QString& str_status = i->getName();
        m_ptrComboStatus->addItem(str_status, QVariant(i_key));
    };
    //
    m_ptrLblAttractivity = new QLabel();
    m_ptrLblAttractivity->setText("Attractivity");
    m_ptrLblAttractivity->setMinimumWidth(m_iMinLabelWidth);
    //
    m_ptrComboAttractivity = new QComboBox();
    m_ptrComboAttractivity->setMinimumWidth(m_iMinEditWidth);
    m_ptrComboAttractivity->setMaximumWidth(m_iMaxElementWidth);
    //
    m_ptrComboAttractivity->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_UNKNOWN), QVariant(static_cast<int>(ATTRACTIVITY_UNKNOWN)));
    m_ptrComboAttractivity->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_LOW), QVariant(static_cast<int>(ATTRACTIVITY_LOW)));
    m_ptrComboAttractivity->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_STANDARD), QVariant(static_cast<int>(ATTRACTIVITY_STANDARD)));
    m_ptrComboAttractivity->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_HIGH), QVariant(static_cast<int>(ATTRACTIVITY_HIGH)));
    m_ptrComboAttractivity->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_VERY_HIGH), QVariant(static_cast<int>(ATTRACTIVITY_VERY_HIGH)));
    m_ptrComboAttractivity->setCurrentIndex(2); //standard
}

void  DlgNewOffer::createAgentWidgets(){
    m_ptrSpacer = new QSpacerItem(100,325);
    //
    m_ptrLblAgentInfo = new QLabel();
    m_ptrLblAgentInfo->setText("Agent info");
    m_ptrLblAgentInfo->setMinimumWidth(300);
    m_ptrLblAgentInfo->setMaximumWidth(m_iMaxElementWidth);
    m_ptrLblAgentInfo->setMaximumHeight(m_iMaxLabelHeight);
    m_ptrLblAgentInfo->setAlignment(Qt::AlignLeft);
    //
    m_ptrLblAgentName = new QLabel();
    m_ptrLblAgentName->setText("Name");
    m_ptrLblAgentName->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditAgentName = new QLineEdit();
    m_ptrEditAgentName->setToolTip("Add name of the contact agent");
    m_ptrEditAgentName->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditAgentName->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrButtonAcceptAgentName = new QPushButton();
    m_ptrButtonAcceptAgentName->setText("Add selection");
    m_ptrButtonAcceptAgentName->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonAcceptAgentName->setEnabled(false);
    connect(m_ptrButtonAcceptAgentName, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentName);
    //
    m_ptrLblAgentEmail = new QLabel();
    m_ptrLblAgentEmail->setText("E-mail");
    m_ptrLblAgentEmail->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditAgentEmail = new QLineEdit();
    m_ptrEditAgentEmail->setToolTip("Add agent e-mail here");
    m_ptrEditAgentEmail->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditAgentEmail->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrButtonAcceptAgentEmail = new QPushButton();
    m_ptrButtonAcceptAgentEmail->setText("Add selection ");
    m_ptrButtonAcceptAgentEmail->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonAcceptAgentEmail->setEnabled(false);
    connect(m_ptrButtonAcceptAgentEmail, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentEmail);
    //
    m_ptrLblAgentPhone1 = new QLabel();
    m_ptrLblAgentPhone1->setText("Phone 1");
    m_ptrLblAgentPhone1->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditAgentPhone1 = new QLineEdit();
    m_ptrEditAgentPhone1->setToolTip("Add agent phone number here");
    m_ptrEditAgentPhone1->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditAgentPhone1->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrButtonAcceptAgentPhone1 = new QPushButton();
    m_ptrButtonAcceptAgentPhone1->setText("Add selection ");
    m_ptrButtonAcceptAgentPhone1->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonAcceptAgentPhone1->setEnabled(false);
    connect(m_ptrButtonAcceptAgentPhone1, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentPhone1);
    //
    m_ptrLblAgentPhone2 = new QLabel();
    m_ptrLblAgentPhone2->setText("Phone 2");
    m_ptrLblAgentPhone2->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditAgentPhone2 = new QLineEdit();
    m_ptrEditAgentPhone2->setToolTip("Add agent phone number here");
    m_ptrEditAgentPhone2->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditAgentPhone2->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrButtonAcceptAgentPhone2 = new QPushButton();
    m_ptrButtonAcceptAgentPhone2->setText("Add selection ");
    m_ptrButtonAcceptAgentPhone2->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonAcceptAgentPhone2->setEnabled(false);
    connect(m_ptrButtonAcceptAgentPhone2, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgentPhone2);
    //
    m_ptrLblAgencyName = new QLabel();
    m_ptrLblAgencyName->setText("Agency");
    m_ptrLblAgencyName->setMinimumWidth(m_iMinLabelWidth);
    //..
    m_ptrEditAgencyName = new QLineEdit();
    m_ptrEditAgencyName->setMinimumWidth(m_iMinEditWidth);
    m_ptrEditAgencyName->setMaximumWidth(m_iMaxElementWidth);
    m_ptrEditAgencyName->setToolTip("Select agency name");
    //..
    m_ptrButtonAcceptAgencyName = new QPushButton();
    m_ptrButtonAcceptAgencyName->setText("Add selection ");
    m_ptrButtonAcceptAgencyName->setMinimumWidth(m_iMinButtonWidth);
    m_ptrButtonAcceptAgencyName->setEnabled(false);
    connect(m_ptrButtonAcceptAgencyName, &QPushButton::released, this, &DlgNewOffer::onClickBtnAcceptAgencyName);
    //
    m_ptrLblAgentRank = new QLabel();
    m_ptrLblAgentRank->setText("Rank");
    m_ptrLblAgentRank->setMinimumWidth(m_iMinLabelWidth);
    m_ptrLblAgentRank->setMaximumWidth(m_iMaxElementWidth);
    //..
    m_ptrComboAgentRank = new QComboBox();
    m_ptrComboAgentRank->setMinimumWidth(m_iMinButtonWidth);
    m_ptrComboAgentRank->setMaximumWidth(m_iMaxElementWidth);
    m_ptrComboAgentRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankUnknown), QVariant(static_cast<int>(AGENT_RANK::RankUnknown)));
    m_ptrComboAgentRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryBad), QVariant(static_cast<int>(AGENT_RANK::RankVeryBad)));
    m_ptrComboAgentRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankBad), QVariant(static_cast<int>(AGENT_RANK::RankBad)));
    m_ptrComboAgentRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankNeutral), QVariant(static_cast<int>(AGENT_RANK::RankNeutral)));
    m_ptrComboAgentRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankGood), QVariant(static_cast<int>(AGENT_RANK::RankGood)));
    m_ptrComboAgentRank->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryGood), QVariant(static_cast<int>(AGENT_RANK::RankVeryGood)));
    m_ptrComboAgentRank->setCurrentIndex(0);
}

void  DlgNewOffer::createControlButtons(){
    m_ptrButtonScan = new QPushButton();
    m_ptrButtonScan->setText("Scan offer");
    m_ptrButtonScan->setMinimumWidth(m_iMinButtonWidth);
    connect(m_ptrButtonScan, &QPushButton::released, this, &DlgNewOffer::onClickBtnScan);
    //
    m_ptrButtonSaveOffer = new QPushButton();
    m_ptrButtonSaveOffer->setText("Save offer ");
    m_ptrButtonSaveOffer->setMinimumWidth(m_iMinButtonWidth);
    connect(m_ptrButtonSaveOffer, &QPushButton::released, this, &DlgNewOffer::onClickBtnSaveOffer);
    //
    m_ptrButtonClose = new QPushButton();
    m_ptrButtonClose->setText("Close window");
    m_ptrButtonClose->setMinimumWidth(m_iMinButtonWidth);
    connect(m_ptrButtonClose, &QPushButton::released, this, &DlgNewOffer::close);
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
    m_ptrMainLayout->addWidget(m_ptrLblnsertOffer,i_row,0,1,1);
    m_ptrMainLayout->addWidget(m_ptrLblOfferInfo,i_row,1,1,3);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrOfferEdit,i_row,0,11,1);
    //
    m_ptrMainLayout->addWidget(m_ptrLblPositonTitle,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditPositonTitle,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptPositonTitle,i_row,3,1,1);
    //
    i_row++;
    //
    m_ptrMainLayout->addWidget(m_ptrLblCountry,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrComboCountry,i_row,2,1,1);
    //
    i_row++;
    //
    m_ptrMainLayout->addWidget(m_ptrLblTown,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditTown,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptTown,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblSkills,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditSkills,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptSkills,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblRate,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditRate,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblStatus,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrComboStatus,i_row,2,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAttractivity,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrComboAttractivity,i_row,2,1,1);
    //--------------------------------------------------------------------------
    i_row++;
    m_ptrMainLayout->addItem(m_ptrSpacer,i_row,1,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAgentInfo,i_row,1,1,3);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAgentName,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditAgentName,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptAgentName,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAgentEmail,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditAgentEmail,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptAgentEmail,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblnsertComment,i_row,0,1,1);
    //
    m_ptrMainLayout->addWidget(m_ptrLblAgentPhone1,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditAgentPhone1,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptAgentPhone1,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrCommentEdit,i_row,0,6,1);
    //
    m_ptrMainLayout->addWidget(m_ptrLblAgentPhone2,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditAgentPhone2,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptAgentPhone2,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAgencyName,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrEditAgencyName,i_row,2,1,1);
    m_ptrMainLayout->addWidget(m_ptrButtonAcceptAgencyName,i_row,3,1,1);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrLblAgentRank,i_row,1,1,1);
    m_ptrMainLayout->addWidget(m_ptrComboAgentRank,i_row,2,1,1);
    //------------------------------------------------------------------------------
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrButtonScan,i_row,1,1,3);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrButtonSaveOffer,i_row,1,1,3);
    //
    i_row++;
    m_ptrMainLayout->addWidget(m_ptrButtonClose,i_row,1,1,3);
}

void  DlgNewOffer::onSelectText(bool b_selected){
    m_ptrButtonAcceptPositonTitle->setEnabled(b_selected);
    m_ptrButtonAcceptTown->setEnabled(b_selected);
    m_ptrButtonAcceptSkills->setEnabled(b_selected);
    //
    m_ptrButtonAcceptAgencyName->setEnabled(b_selected);
    m_ptrButtonAcceptAgentName->setEnabled(b_selected);
    m_ptrButtonAcceptAgentEmail->setEnabled(b_selected);
    m_ptrButtonAcceptAgentPhone1->setEnabled(b_selected);
    m_ptrButtonAcceptAgentPhone2->setEnabled(b_selected);
    m_ptrButtonAcceptAgencyName->setEnabled(b_selected);
}

void  DlgNewOffer::onRequestUserMenu(){
    QMenu popup_menu(this);
    bool b_can_paste = m_ptrOfferEdit->canPaste();
    m_actionPaste.setEnabled(b_can_paste);
    //
    const QString str_selected = m_ptrOfferEdit->textCursor().selectedText();
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
    QString str_selected = m_ptrOfferEdit->textCursor().selectedText();
    str_selected = str_selected.normalized(QString::NormalizationForm_D);
    str_selected = str_selected.trimmed();
    return str_selected;
}

void DlgNewOffer::onClickBtnAcceptPositionTitle(){
    m_ptrEditPositonTitle->setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptTown(){
    m_ptrEditTown->setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void  DlgNewOffer::onClickBtnAcceptSkills(){
    const QString str_property = this->getSelectedPartOfOffer();
    const QString str_existing_skills = m_ptrEditSkills->text();
    QString str_full_skills_list;
    //
    if (str_existing_skills.length() > 0){
        str_full_skills_list = str_existing_skills + SKILLS_SEPARATOR;
    };
    //
    str_full_skills_list +=str_property;
    m_ptrEditSkills->setText(str_full_skills_list);
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentName(){
    const QString str_name = this->getSelectedPartOfOffer();
    m_ptrEditAgentName->setText(str_name);
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentEmail(){
    const QString str_email = this->getSelectedPartOfOffer();
    //todo: check e-mail
    m_ptrEditAgentEmail->setText(str_email);
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentPhone1(){
    //todo: check if it is a phone
    m_ptrEditAgentPhone1->setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgentPhone2(){
    //todo: check if it is a phone
    m_ptrEditAgentPhone2->setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void DlgNewOffer::onClickBtnAcceptAgencyName(){
    m_ptrEditAgencyName->setText(this->getSelectedPartOfOffer());
    m_bOfferSaved = false;
}

void  DlgNewOffer::onClickBtnScan(){
    OfferScaner scaner;
    scaner.parse(m_ptrOfferEdit->toPlainText());
    //
    m_ptrOfferEdit->setPlainText(scaner.getModifiedText());
    m_ptrEditSkills->setText(scaner.getSkills());
    //
    if (scaner.getAgencyName().length() > 0){
        m_ptrEditAgencyName->setText(scaner.getAgencyName());
        m_dtoAgent.setAgencyId(scaner.getAgentId());
    };
    //
    if (scaner.getAgentEmail().length() > 0){
        //for prevent double saving operations
        m_dtoAgent.setId(scaner.getAgentId());
        m_bAgentAdded = false;
        //for visualisation
        m_ptrEditAgentEmail->setText(scaner.getAgentEmail());
        m_ptrEditAgentName->setText(scaner.getAgentName());
        m_ptrEditAgentPhone1->setText(scaner.getAgentPhone1());
        m_ptrEditAgentPhone2->setText(scaner.getAgentPhone2());
        //
        for (int i = 0; i < m_ptrComboAgentRank->count(); ++i){
            QVariant current_rank = m_ptrComboAgentRank->itemData(i,Qt::UserRole);
            if (current_rank.toInt() == scaner.getAgentRank()){
                m_ptrComboAgentRank->setCurrentIndex(i);
                break;
            };
        };
    };
    //
    m_ptrEditTown->setText(scaner.getTownName());
}

void  DlgNewOffer::onClickBtnSaveOffer(){
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Ok);
    QString str_message_text;
    //
    if (m_ptrEditPositonTitle->text().isEmpty() == true){
        str_message_text = "Position title can not be empty\n";
    };
    //
    if(m_ptrComboCountry->currentIndex() == -1){
        str_message_text = str_message_text + "Country can not be empty\n";
    };
    //
    if(m_ptrEditSkills->text().isEmpty() == true){
        str_message_text = str_message_text + "Skills list can not be empty\n";
    };
    //check agent info
    if(m_ptrEditAgencyName->text().isEmpty() == true){
        str_message_text = str_message_text + "Agent name can not be empty\n";
    };
    if(m_ptrEditAgentEmail->text().isEmpty() == true){
        str_message_text = str_message_text + "Agent e-mail can not be empty\n";
    };
    if((m_ptrEditAgentPhone1->text().isEmpty() == true) && (m_ptrEditAgentPhone2->text().isEmpty() == true)){
        str_message_text = str_message_text + "Agent phone can not be empty\n";
    };
    if(m_ptrEditAgencyName->text().isEmpty() == true){
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
    const int           i_country_id    = m_ptrComboCountry->currentData(Qt::UserRole).toInt();
    const int           i_town_id       = TownProcessor::getInstance().add(m_ptrEditTown->text().trimmed());
    const QStringList   str_l_skills    =  m_ptrEditSkills->text().split(",", QString::SkipEmptyParts);
    const SkillsList    skill_list_ids  = SkillProcessor::getInstance().add(str_l_skills);
    //
    m_dtoOffer.setAgentId(m_dtoAgent.getId());
    m_dtoOffer.setCreationDate(QDate::currentDate());
    m_dtoOffer.setPositionTitle(m_ptrEditPositonTitle->text());
    QString str_offer_text = m_ptrOfferEdit->toPlainText();
    if (str_offer_text.length() > 2000){
        str_offer_text = str_offer_text.mid(MAX_TEXT_LENGTH);
    };
    m_dtoOffer.setDescription(str_offer_text);
    //
    QString str_comment_text = m_ptrCommentEdit->toPlainText();
    if (str_comment_text.length() > 2000){
        str_comment_text = str_comment_text.mid(MAX_TEXT_LENGTH);
    };
    m_dtoOffer.setComments(str_comment_text);
    m_dtoOffer.setCountryId(i_country_id);
    m_dtoOffer.setTownId(i_town_id);
    //m_dtoOffer.setSkillsListIDs(skill_list_ids);
    //
    const QString str_rate = m_ptrEditRate->text();
    m_dtoOffer.setRate(str_rate.toInt());
    const int i_attractivity = m_ptrComboAttractivity->currentData().toInt();
    m_dtoOffer.setAttractivity(i_attractivity);
    const int i_status = m_ptrComboStatus->currentData().toInt();
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
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByEmail(m_ptrEditAgentEmail->text());
    if (nullptr != ptr_agent){
        m_bAgentAdded = false;
        m_dtoAgent.setId(ptr_agent->getId());
        return true;
    };
    //
    int i_agency_id = AgencyProcessor::getInstance().add(m_ptrEditAgencyName->text().trimmed());
    if(VALUE_UNDEFINED == i_agency_id){
        return false; //can not add new agency to database
    }
    //
    m_dtoAgent.setName(m_ptrEditAgentName->text());
    m_dtoAgent.setEMail( m_ptrEditAgentEmail->text());
    m_dtoAgent.setPhone1(m_ptrEditAgentPhone1->text());
    m_dtoAgent.setPhone2(m_ptrEditAgentPhone2->text());
    m_dtoAgent.setAgencyId(i_agency_id);
    const QVariant agent_rank = m_ptrComboAgentRank->currentData();
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
    if((false == m_bOfferSaved) && (m_ptrEditPositonTitle->text().length() > 0)){
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
    m_ptrOfferEdit->setPlainText(str_empty_txt);
    m_ptrEditPositonTitle->setText(str_empty_txt);
    m_ptrComboCountry->setCurrentIndex(-1);
    m_ptrEditTown->setText(str_empty_txt);
    m_ptrEditSkills->setText(str_empty_txt);
    m_ptrEditRate->setText("0");
    m_ptrEditAgentName->setText(str_empty_txt);
    m_ptrEditAgentEmail->setText(str_empty_txt);
    m_ptrEditAgentPhone1->setText(str_empty_txt);
    m_ptrEditAgentPhone2->setText(str_empty_txt);
    m_ptrEditAgencyName->setText(str_empty_txt);
    m_dtoOffer.reset();
    m_dtoAgent.reset();
}

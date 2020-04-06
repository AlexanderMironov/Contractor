#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QMenu>
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
//
#include "graficcontainers/graficcontainerlistoffers.h"
#include "graficcontainers/graficcontainerlistagent.h"
#include "graficcontainers/offerstable.h"
#include "graficcontainers/agentstable.h"
//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    createLayout();
    createTabPages();
    setWindowSize();
    //
    this->setWindowTitle("Contractor");
    //
    m_mnuContainer.init(this);
    m_dlgManageCountries.init();
    //
    OffersTable* ptr_offers_tab =  GraficContainerListOffers::getInstance().getOffersTab();
    AgentsTable* ptr_agents_tab = GraficContainerListAgent::getInstance().getAgentsTab();
    //
    connect(&m_dlgManageCountries, SIGNAL( modifyCountry(int)), ptr_offers_tab, SLOT(onChangeCountryName(int)));
    //for parallel moving on agent table
    connect(ptr_offers_tab, SIGNAL(currentAgentChanged(int)), ptr_agents_tab, SLOT(onCurrentAgentChanged(int)));
    //for update agent name in the offer table
    connect(ptr_agents_tab, SIGNAL(changeAgentDescriptionName(int)), ptr_offers_tab, SLOT(onChangeAgentName(int)));
    //for update agent table when new agen created during creating of noe offer
    connect(ptr_offers_tab, SIGNAL(agentAdded()), ptr_agents_tab, SLOT(showTable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createLayout(){
    m_ptrLayoutMain = new QVBoxLayout(this->centralWidget());
    this->setLayout(m_ptrLayoutMain);
    //
    m_ptrMainTab = new QTabWidget();
    m_ptrLayoutMain->addWidget(m_ptrMainTab);
}

void MainWindow::createTabPages(){
    //create TabPages 1 by 1
    //offers
    GraficContainerListOffers::getInstance().init(m_ptrMainTab);
    GraficContainerListAgent::getInstance().init(m_ptrMainTab);
}

void MainWindow::setWindowSize(){
    QDesktopWidget dw;
    this->setMinimumHeight(dw.height()*0.5);
    this->setMinimumWidth(dw.width()*0.9);

    //
    //this->setMaximumHeight(dw.height()*0.9);
    //this->setMaximumWidth(dw.width());
    //
}

DlgManageCountries* MainWindow::getDlgManageCountries(){
    return &m_dlgManageCountries;
}

void MainWindow::onShowManageCountriesDlg(){
    m_dlgManageCountries.exec();
}

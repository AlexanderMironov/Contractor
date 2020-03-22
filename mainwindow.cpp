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
    DlgNewOffer* ptr_dlg_new_offer = GraficContainerListOffers::getInstance().getDlgNewOffer();
    //
    connect(&m_dlgManageCountries, SIGNAL(createNewCountry()), ptr_dlg_new_offer, SLOT(onAddNewCountry()));
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
    this->setMaximumHeight(dw.height()*0.9);
    //
    this->setMinimumWidth(dw.width()*0.8);
    this->setMaximumWidth(dw.width()*0.9);
}

DlgManageCountries* MainWindow::getDlgManageCountries(){
    return &m_dlgManageCountries;
}

void MainWindow::onShowManageCountriesDlg(){
    m_dlgManageCountries.exec();
}

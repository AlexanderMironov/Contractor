#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QFrame>
#include <QVBoxLayout>
#include <QDesktopWidget>
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
//
#include "graficcontainers/graficcontainerlistoffers.h"
//
#include "dialogs/dlgnewoffer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
    m_ptrLayoutMain = new QVBoxLayout(this->centralWidget());
    this->setLayout(m_ptrLayoutMain);
    //
    m_ptrMainTab = new QTabWidget();
    m_ptrLayoutMain->addWidget(m_ptrMainTab);
    //create TabPages 1 by 1
    //offers
    GraficContainerListOffers::getInstance().init(m_ptrMainTab);
    //agents
    //todo add it
    QDesktopWidget dw;
    this->setMinimumHeight(dw.height()*0.8);
    //
    this->setMinimumWidth(dw.width()*0.7);
    this->setMaximumWidth(dw.width()*0.95);
    //
    this->setWindowTitle("Contractor");
    //debug code
    //DlgNewOffer dlg;
    //dlg.exec();
    //debug code
    return;
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

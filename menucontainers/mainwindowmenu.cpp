#include <QMenuBar>
#include <QObject>
//
#include "mainwindowmenu.h"
#include "mainwindow.h"
#include "graficcontainers/graficcontainerlistoffers.h"
#include "graficcontainers/graficcontainerlistagent.h"

MainWindowMenu::MainWindowMenu()
{
    m_ptrMainWindow = nullptr;
}

void MainWindowMenu::init(MainWindow* pt_main_window){
    if (nullptr != m_ptrMainWindow){
        return;
    };
    //
    m_ptrMainWindow = pt_main_window;
    //
    m_ptrFileMenu = m_ptrMainWindow->menuBar()->addMenu("File");
    //
    createActionNewOffer();
    //
    m_mnuAdd.setTitle("Create new");
    m_mnuAdd.addAction(&actionCreateNewOffer);
    m_mnuAdd.addSeparator();
    m_mnuAdd.addAction(&actionCreateNewAgent);
    //
    m_ptrFileMenu->addMenu(&m_mnuAdd);
    m_ptrFileMenu->addSeparator();
    m_ptrFileMenu->addAction(&actionCountriesOperation);
}

void MainWindowMenu::createActionNewOffer(){
    actionCreateNewOffer.setText("Job offer");
    actionCreateNewOffer.setEnabled(true);
    GraficContainerListOffers& offer_container = GraficContainerListOffers::getInstance();
    QObject::connect(&actionCreateNewOffer, &QAction::triggered, &offer_container, &GraficContainerListOffers::onShowNewOfferDlg);
    //
    actionCreateNewAgent.setText("Agent");
    actionCreateNewAgent.setEnabled(true);
    GraficContainerListAgent& agent_container = GraficContainerListAgent::getInstance();
    QObject::connect(&actionCreateNewAgent, &QAction::triggered, &agent_container, &GraficContainerListAgent::onShowNewAgentDlg);
    //
    actionCountriesOperation.setText("Manage countries");
    actionCountriesOperation.setEnabled(true);
    QObject::connect(&actionCountriesOperation, &QAction::triggered, m_ptrMainWindow, &MainWindow::onShowManageCountriesDlg);

}

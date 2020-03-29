#include <QMenuBar>
#include <QObject>
//
#include "mainwindowmenu.h"
#include "mainwindow.h"
#include "graficcontainers/graficcontainerlistoffers.h"
#include "graficcontainers/graficcontainerlistagent.h"
#include "graficcontainers/offerstable.h"
#include "graficcontainers/agentstable.h"

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
    //
    OffersTable* ptr_offer_table = GraficContainerListOffers::getInstance().getOffersTab();
    QObject::connect(&actionCreateNewOffer, &QAction::triggered, ptr_offer_table, &OffersTable::onCreateOffer);
    //
    actionCreateNewAgent.setText("Agent");
    actionCreateNewAgent.setEnabled(true);
    AgentsTable* ptr_agent_table = GraficContainerListAgent::getInstance().getAgentsTab();
    QObject::connect(&actionCreateNewAgent, &QAction::triggered, ptr_agent_table, &AgentsTable::onCreateAgent);
    //
    actionCountriesOperation.setText("Manage countries");
    actionCountriesOperation.setEnabled(true);
    QObject::connect(&actionCountriesOperation, &QAction::triggered, m_ptrMainWindow, &MainWindow::onShowManageCountriesDlg);

}

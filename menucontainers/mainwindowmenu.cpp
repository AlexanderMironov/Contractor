#include <QMenuBar>
#include <QObject>
//
#include "mainwindowmenu.h"
#include "mainwindow.h"
#include "graficcontainers/graficcontainerlistoffers.h"

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
    m_ptrFileMenu->addAction(&actionCreateNewOffer);
    m_ptrFileMenu->addSeparator();

}

void MainWindowMenu::createActionNewOffer(){
    actionCreateNewOffer.setText("Create new job offer");
    actionCreateNewOffer.setEnabled(true);
    GraficContainerListOffers& container = GraficContainerListOffers::getInstance();

    QObject::connect(&actionCreateNewOffer, &QAction::triggered, &container, &GraficContainerListOffers::onShowNewOfferDlg);

}

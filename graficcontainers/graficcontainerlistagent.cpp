#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
//
#include "graficcontainers/graficcontainerlistagent.h"
#include "graficcontainers/graficcontainerlistoffers.h"
#include "dialogs/dlgnewoffer.h"
//
#include "graficcontainers/agentstable.h"

GraficContainerListAgent::GraficContainerListAgent(QObject *parent) : QObject(parent)
{
    m_ptrMainTab = nullptr;
}

GraficContainerListAgent::~GraficContainerListAgent(){
//GraficContainerListOffers
}

GraficContainerListAgent& GraficContainerListAgent::getInstance(){
    static GraficContainerListAgent instance;
    return instance;
}

void GraficContainerListAgent::init(QTabWidget* ptr_tab){
    if (nullptr != m_ptrMainTab){
        return; //already initialized
    };
    //
    m_ptrMainTab = ptr_tab;
    //create all for 2-nd page
    QWidget* ptr_firt_main_widget = new QWidget ();
    QVBoxLayout* ptr_firt_main_layout = new QVBoxLayout();
    ptr_firt_main_widget->setLayout(ptr_firt_main_layout);
    //
    m_ptrTblAgentsTable = new AgentsTable();
    ptr_firt_main_layout->addWidget(m_ptrTblAgentsTable);
    //
//    m_dlgNewOffer.init();
    //
    bindSignalsAndSlots();
    //
    m_ptrMainTab->addTab(ptr_firt_main_widget,"Agents");
}

void GraficContainerListAgent::bindSignalsAndSlots(){
//    QObject::connect(m_ptrTblOffersTable, SIGNAL(needNewOfferDlg()), this, SLOT(onShowNewOfferDlg()));

    DlgNewOffer* ptr_dlg = GraficContainerListOffers::getInstance().getDlgNewOffer();
    if(nullptr != ptr_dlg){
      QObject::connect(ptr_dlg, SIGNAL(addedNewOffer()), m_ptrTblAgentsTable, SLOT(showTable()));
    };

//
    //todo: also update agents table here
}
/*
DlgNewOffer* GraficContainerListAgent::getDlgNewOffer(){
    return &m_dlgNewOffer;
}
*/
/*
void GraficContainerListAgent::onShowNewOfferDlg(){
    m_dlgNewOffer.exec();
}
*/

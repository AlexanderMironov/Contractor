#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
//
#include "graficcontainerlistoffers.h"
#include "graficcontainers/offerstable.h"

GraficContainerListOffers::GraficContainerListOffers(QObject *parent) : QObject(parent)
{
    m_ptrMainTab = nullptr;
}

GraficContainerListOffers::~GraficContainerListOffers(){

}

GraficContainerListOffers& GraficContainerListOffers::getInstance(){
    static GraficContainerListOffers instance;
    return instance;
}

void GraficContainerListOffers::init(QTabWidget* ptr_tab){
    if (nullptr != m_ptrMainTab){
        return; //already initialized
    };
    //
    m_ptrMainTab = ptr_tab;
    //create all for 1-st page
    QWidget* ptr_firt_main_widget = new QWidget ();
    QVBoxLayout* ptr_firt_main_layout = new QVBoxLayout();
    ptr_firt_main_widget->setLayout(ptr_firt_main_layout);
    //
    m_ptrTblOffersTable = new OffersTable();
    ptr_firt_main_layout->addWidget(m_ptrTblOffersTable);
    //
    m_dlgNewOffer.init();
    //
    bindSignalsAndSlots();
    //
    m_ptrMainTab->addTab(ptr_firt_main_widget,"Offers");
}

void GraficContainerListOffers::bindSignalsAndSlots(){
    QObject::connect(m_ptrTblOffersTable, SIGNAL(needNewOfferDlg()), this, SLOT(onShowNewOfferDlg()));
    QObject::connect(&m_dlgNewOffer, SIGNAL(addedNewOffer()), m_ptrTblOffersTable, SLOT(showTable()));
    //todo: also update agents table here
}

DlgNewOffer* GraficContainerListOffers::getDlgNewOffer(){
    return &m_dlgNewOffer;
}

void GraficContainerListOffers::onShowNewOfferDlg(){
    m_dlgNewOffer.exec();
}

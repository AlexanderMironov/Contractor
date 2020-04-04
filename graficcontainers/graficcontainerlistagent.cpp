#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
//
#include "graficcontainers/graficcontainerlistagent.h"
#include "graficcontainers/graficcontainerlistoffers.h"
#include "dialogs/dlgnewoffer.h"
//
#include "graficcontainers/agentstable.h"

GraficContainerListAgent::GraficContainerListAgent(QObject *parent) : QObject(parent)
{
    m_ptrMainTab        = nullptr;
    m_ptrFirtMainWidget = nullptr;
    m_ptrFirtMainLayout = nullptr;
    m_ptrClearButton    = nullptr;
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
    //
    m_ptrFirtMainWidget = new QWidget ();
    //
    createGraficElements();
    createLayouts();
    addElementsToLayouts();
    //
    bindSignalsAndSlots();
    //
    m_ptrMainTab->addTab(m_ptrFirtMainWidget,"Agents");
}

void GraficContainerListAgent::addElementsToLayouts(){
    m_ptrSearchLayout->addWidget(m_ptrSearchLabel);
    m_ptrSearchLayout->addWidget(m_ptrSearchEditField,Qt::AlignLeft);
    m_ptrSearchLayout->addWidget(m_ptrClearButton);
    //
    m_ptrFirtMainLayout->addLayout(m_ptrSearchLayout);
    m_ptrFirtMainLayout->addWidget(m_ptrTblAgentsTable);
}

void GraficContainerListAgent::createGraficElements(){
    m_ptrSearchLabel = new QLabel("Search agent by name or e-mail");
    //
    m_ptrSearchEditField = new QLineEdit();
    //
    m_ptrClearButton = new QPushButton("Clear search");
    m_ptrClearButton->setMinimumWidth(100);
    m_ptrClearButton->setMaximumWidth(150);
    //
    m_ptrTblAgentsTable = new AgentsTable();
}

void GraficContainerListAgent::createLayouts(){
    m_ptrFirtMainLayout = new QVBoxLayout();
    m_ptrFirtMainWidget->setLayout(m_ptrFirtMainLayout);
    //
    m_ptrSearchLayout = new QHBoxLayout();
}

void GraficContainerListAgent::bindSignalsAndSlots(){
    //
    //todo: also update agents table her
    connect(m_ptrSearchEditField, SIGNAL(textChanged(const QString &)),m_ptrTblAgentsTable, SLOT(onChangeSearchNameOrEmail(const QString &)));
}

AgentsTable* GraficContainerListAgent::getAgentsTab(){
    return m_ptrTblAgentsTable;
}

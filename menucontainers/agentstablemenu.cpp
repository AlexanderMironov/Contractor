#include <QMenu>
#include "agentstablemenu.h"
#include "graficcontainers/agentstable.h"

AgentsTableMenu::AgentsTableMenu()
{
    m_ptrParentWindow = nullptr;
}

void AgentsTableMenu::init(AgentsTable* pt_main_window){
    if (nullptr != m_ptrParentWindow){
        return;
    };
    //
    m_ptrParentWindow = pt_main_window;
    //
    m_actionShowEditAgent.setText("Show/Edit current agent");
    m_actionShowEditAgent.setEnabled(true);
    QObject::connect(&m_actionShowEditAgent, SIGNAL(triggered()), m_ptrParentWindow, SLOT(onShowEditAgent()));
    //
    m_actionCreateAgent.setText("Create new agent");
    m_actionCreateAgent.setEnabled(true);
    QObject::connect(&m_actionCreateAgent, SIGNAL(triggered()), m_ptrParentWindow, SLOT(onCreateAgent()));
}

void AgentsTableMenu::fillPopupMenu(QMenu* ptr_mnu, bool enable_edit){
    if(nullptr == ptr_mnu){
        return;
    };
    //
    m_actionShowEditAgent.setEnabled(enable_edit);
    ptr_mnu->addAction(&m_actionShowEditAgent);
    //
    ptr_mnu->addAction(&m_actionCreateAgent);
}

QAction* AgentsTableMenu::getActionShowEditAgent(){
    return &m_actionShowEditAgent;
}

QAction* AgentsTableMenu::getActionCreateAgent(){
    return &m_actionCreateAgent;
}

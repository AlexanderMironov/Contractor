#ifndef AGENTSTABLEMENU_H
#define AGENTSTABLEMENU_H

#include <QAction>
//
class AgentsTable;

class AgentsTableMenu
{
public:
    AgentsTableMenu();
    void init(AgentsTable* pt_main_window);
    void                fillPopupMenu(QMenu* ptr_mnu, bool enable_edit);
    QAction*            getActionShowEditAgent();
    QAction*            getActionCreateAgent();

private:
    AgentsTable*        m_ptrParentWindow;
    //
    QAction             m_actionShowEditAgent;
    QAction             m_actionCreateAgent;
};

#endif // AGENTSTABLEMENU_H

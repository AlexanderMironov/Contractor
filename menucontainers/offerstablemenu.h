#ifndef OFFERSTABLEMENU_H
#define OFFERSTABLEMENU_H

#include <QAction>
//
class OffersTable;
class QMenu;
//

class OffersTableMenu
{
public:
    OffersTableMenu();
    void init(OffersTable* pt_main_window);
    QAction*            getActionShowNewOfferDlg();
    QAction*            getActionDeleteCurrentOffer();
    void                fillPopupMenu(QMenu* ptr_mnu, bool enable_delete);
    //void                enableDeleteCurrentOffer(bool b_enable);

private:
    OffersTable*        m_ptrParentWindow;
    //
    QAction             m_actionShowNewOfferDlg;
    QAction             m_actionDeleteCurrentOffer;
    QAction             m_actionEditCurrentOffer;

};

#endif // OFFERSTABLEMENU_H

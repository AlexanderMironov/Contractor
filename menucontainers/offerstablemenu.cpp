#include <QObject>
#include <QMenu>
//
#include "offerstablemenu.h"
#include "graficcontainers/offerstable.h"

OffersTableMenu::OffersTableMenu()
{
    m_ptrParentWindow = nullptr;
}

void OffersTableMenu::init(OffersTable* pt_main_window){
    if (nullptr != m_ptrParentWindow){
        return;
    };
    //
    m_ptrParentWindow = pt_main_window;
    //
    m_actionShowNewOfferDlg.setText("Add new offer");
    m_actionShowNewOfferDlg.setEnabled(true);
    QObject::connect(&m_actionShowNewOfferDlg, SIGNAL(triggered()), m_ptrParentWindow, SLOT(onCreateOffer()));
    //
    m_actionDeleteCurrentOffer.setText("Delete current offer");
    m_actionDeleteCurrentOffer.setEnabled(true);
    QObject::connect(&m_actionDeleteCurrentOffer, SIGNAL(triggered()), m_ptrParentWindow, SLOT(onDeleteCurrentOffer()));
    //
    m_actionEditCurrentOffer.setText("Edit/View Current offer");
    m_actionEditCurrentOffer.setEnabled(true);
    //
    QObject::connect(&m_actionEditCurrentOffer, SIGNAL(triggered()), m_ptrParentWindow, SLOT(onEditCurrentOffer()));
}

void OffersTableMenu::fillPopupMenu(QMenu* ptr_mnu, bool enable_delete){
    if(nullptr == ptr_mnu){
        return;
    };
    //
    ptr_mnu->addAction(&m_actionShowNewOfferDlg);
    //
    m_actionDeleteCurrentOffer.setEnabled(enable_delete);
    m_actionEditCurrentOffer.setEnabled(enable_delete);
    //
    ptr_mnu->addAction(&m_actionEditCurrentOffer);
    //
    ptr_mnu->addAction(&m_actionDeleteCurrentOffer);


}

/*
void OffersTableMenu::enableDeleteCurrentOffer(bool b_enable){
    m_actionDeleteCurrentOffer.setEnabled(b_enable);
}
*/
QAction* OffersTableMenu::getActionDeleteCurrentOffer(){
    return &m_actionDeleteCurrentOffer;
}

QAction* OffersTableMenu::getActionShowNewOfferDlg(){
    return &m_actionShowNewOfferDlg;
}

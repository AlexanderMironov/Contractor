#ifndef MAINWINDOWMENU_H
#define MAINWINDOWMENU_H

#include <QAction>
#include <QMenu>
//
class MainWindow;

class MainWindowMenu
{
public:
    MainWindowMenu();
    void init(MainWindow *pt_main_window);

private:
    void createActionNewOffer();
private:
    MainWindow* m_ptrMainWindow;
    QMenu*      m_ptrFileMenu;
    QMenu       m_mnuAdd;
    //
    QAction     actionCreateNewOffer;
    QAction     actionCreateNewAgent;
    QAction     actionCountriesOperation;

};

#endif // MAINWINDOWMENU_H

#ifndef MAINWINDOWMENU_H
#define MAINWINDOWMENU_H

#include <QAction>
//
class MainWindow;
class QMenu;

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
    //
    QAction     actionCreateNewOffer;
    QAction     actionCountriesOperation;

};

#endif // MAINWINDOWMENU_H

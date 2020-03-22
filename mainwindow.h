#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
//
#include "menucontainers/mainwindowmenu.h"
#include "dialogs/dlgmanagecountries.h"

class QTabWidget;
class QVBoxLayout;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DlgManageCountries* getDlgManageCountries();

public slots:
    void onShowManageCountriesDlg();

private:
    void    setWindowSize();
    void    createTabPages();
    void    createLayout();

private:
    Ui::MainWindow* ui;
    QTabWidget*         m_ptrMainTab;
    QVBoxLayout*        m_ptrLayoutMain;
    //
    MainWindowMenu      m_mnuContainer;
    //
    DlgManageCountries  m_dlgManageCountries;
};

#endif // MAINWINDOW_H

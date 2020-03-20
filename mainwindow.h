#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
//
#include "menucontainers/mainwindowmenu.h"

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

private:
    Ui::MainWindow* ui;
    QTabWidget*     m_ptrMainTab;
    QVBoxLayout*    m_ptrLayoutMain;
    //
    MainWindowMenu  m_mnuContainer;
    //
};

#endif // MAINWINDOW_H

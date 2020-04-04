#ifndef GraficContainerListAgent_H
#define GraficContainerListAgent_H

#include <QObject>
//
class QVBoxLayout;
class QHBoxLayout;
class QTabWidget;
class AgentsTable;
class QPushButton;
class QLineEdit;
class QLabel;
//
class GraficContainerListAgent : public QObject
{
    Q_OBJECT
public:
    ~GraficContainerListAgent();
    static GraficContainerListAgent& getInstance();
    //
    void                init(QTabWidget* ptr_tab);
    AgentsTable*        getAgentsTab();
    //DlgNewOffer*        getDlgNewOffer();

private:
    explicit            GraficContainerListAgent(QObject *parent = nullptr);
    void                createGraficElements();
    void                createLayouts();
    void                addElementsToLayouts();
    void                bindSignalsAndSlots();

signals:

public slots:


private:
    QWidget*        m_ptrFirtMainWidget;
    QVBoxLayout*    m_ptrFirtMainLayout;
    QHBoxLayout*    m_ptrSearchLayout;
    QTabWidget*     m_ptrMainTab;
    //
    QLabel*         m_ptrSearchLabel;
    QPushButton*    m_ptrClearButton;
    QLineEdit*      m_ptrSearchEditField;
    //
    AgentsTable*    m_ptrTblAgentsTable;
    //
    //DlgNewOffer m_dlgNewOffer;

};

#endif // GraficContainerListAgent_H

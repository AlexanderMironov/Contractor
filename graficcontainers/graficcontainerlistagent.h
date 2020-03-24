#ifndef GraficContainerListAgent_H
#define GraficContainerListAgent_H

#include <QObject>
//
class QTabWidget;
class AgentsTable;

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
    void                bindSignalsAndSlots();

signals:

public slots:
    //void onShowNewOfferDlg();

private:
    QTabWidget* m_ptrMainTab;
    //
    AgentsTable* m_ptrTblAgentsTable;
    //
    //DlgNewOffer m_dlgNewOffer;

};

#endif // GraficContainerListAgent_H

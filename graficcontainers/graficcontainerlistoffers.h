#ifndef GRAFICCONTAINERLISTOFFERS_H
#define GRAFICCONTAINERLISTOFFERS_H

#include <QObject>
//
#include "dialogs/dlgnewoffer.h"
//
class QTabWidget;
class OffersTable;

class GraficContainerListOffers : public QObject
{
    Q_OBJECT
public:
    ~GraficContainerListOffers();
    static GraficContainerListOffers& getInstance();
    //
    void                init(QTabWidget* ptr_tab);
    OffersTable*        getOffersTab();

private:
    explicit            GraficContainerListOffers(QObject *parent = nullptr);
    void                bindSignalsAndSlots();

signals:

public slots:

private:
    QTabWidget* m_ptrMainTab;
    //
    OffersTable* m_ptrTblOffersTable;
};

#endif // GRAFICCONTAINERLISTOFFERS_H

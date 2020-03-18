#ifndef GRAFICCONTAINERLISTOFFERS_H
#define GRAFICCONTAINERLISTOFFERS_H

#include <QObject>
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
    void        init(QTabWidget* ptr_tab);
private:
    explicit GraficContainerListOffers(QObject *parent = nullptr);

signals:

public slots:

private:
    QTabWidget* m_ptrMainTab;
    //
    OffersTable* m_ptrTblOffersTable;

};

#endif // GRAFICCONTAINERLISTOFFERS_H

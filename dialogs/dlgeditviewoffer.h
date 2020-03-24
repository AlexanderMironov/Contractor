#ifndef DLGEDITVIEWOFFER_H
#define DLGEDITVIEWOFFER_H

#include <QDialog>
#include <QObject>


class DlgEditViewOffer : public QDialog
{
    Q_OBJECT

public:
    DlgEditViewOffer(QWidget *parent = nullptr);
    ~DlgEditViewOffer();
    void init();
};

#endif // DLGEDITVIEWOFFER_H

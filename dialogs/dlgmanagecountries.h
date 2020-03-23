#ifndef DLGMANAGECOUNTRIES_H
#define DLGMANAGECOUNTRIES_H

#include <QObject>
#include <QDialog>
#include <QGridLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
//
class QListWidgetItem;
//
class DlgManageCountries : public QDialog
{
        Q_OBJECT

public:
            DlgManageCountries(QWidget *parent = nullptr);
            ~DlgManageCountries();
    void    init();

signals:
    void createNewCountry();
    void modifyCountry(int i_country_id);

private slots:
    void    onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void    onEditTextChanged(const QString& str_txt);
    void    onClickButtonAddNew();
    void    onClickButtonModifyCurrent();

private:
    void    setDlgLayout();
    void    addWidgetsToLayout();
    void    createWidgets();
    void    createCountriesList();
    void    createEditField();
    void    createButtons();

private:
    bool            m_bFillModeOn;
    QGridLayout     m_MainLayout;
    //
    int             m_iItemsWidth;
    int             m_iItemsHeight;
    //
    QListWidget     m_wListOfCountries;
    QLineEdit       m_EditCountry;
    QPushButton     m_ButtonAddNew;
    QPushButton     m_ButtonModifyCurrent;
};

#endif // DLGMANAGECOUNTRIES_H

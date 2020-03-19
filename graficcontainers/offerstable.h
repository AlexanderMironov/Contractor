#ifndef OFFERSTABLE_H
#define OFFERSTABLE_H

#include <QObject>
#include <QTableWidget>
#include <QAction>
//
class OfferBaseDTO;
//
class OffersTable : public QTableWidget
{
    Q_OBJECT

public:
    OffersTable  (QWidget *parent = nullptr);
    ~OffersTable();

signals:
    void needNewOfferDlg();

public slots:
    void    showTable();


private slots:
    void            statusChanged (int i_index);
    void            attractivityChanged(int i_index);
    void            onChangeItem (QTableWidgetItem * item);
    void            onShowNewOfferDlg();

protected:
    void            mouseReleaseEvent   (QMouseEvent *event);
private:
    //
    enum OffersTableColumns
    {
         COL_CREATION_DATE  = 0
        ,COL_TITLE          = 1
        ,COL_SKILLS         = 2
        ,COL_COUNTRY        = 3
        ,COL_TOWN           = 4
        ,COL_AGENT          = 5
        ,COL_AGENCY         = 6
        ,COL_STATUS         = 7
        ,COL_ATTRACTIVITY   = 8
        ,COL_RATE           = 9
    };
    //
private:
    void                setHeaderParams();
    void                bindSignalsAndSlots();
    void                fillDataRow (int ui_row_num, OfferBaseDTO* ptr_dto);
    void                updateStatus (unsigned int ui_row);
    void                updateAttractivity(unsigned int ui_row);
    void                setPopUpMnu();
    void                showPopupMenu();
    int                 getRecordIdByRowNum(int i_row_num);
    //
    QTableWidgetItem*   makeCellDate (OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellTitle(OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellSkills(int ui_row_num, OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellCountry(OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellTown(OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellAgent(OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellAgency(OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellStatus(int ui_row_num, OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellAttractity(int ui_row_num, OfferBaseDTO* ptr_dto);
    QTableWidgetItem*   makeCellRate(OfferBaseDTO* ptr_dto);
    //
    QAction             m_actionShowNewOfferDlg;
    QAction             m_actionDeleteCurrentOffer;
    //
    bool    m_bFillTableModeOn;

};

#endif // OFFERSTABLE_H

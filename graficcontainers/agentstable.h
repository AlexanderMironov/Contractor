#ifndef AGENTSSTABLE_H
#define AGENTSSTABLE_H

#include <QObject>
#include <QTableWidget>
#include <QAction>
//
#include "menucontainers/agentstablemenu.h"
//
class AgentBaseDTO;
class QMouseEvent;
//
class AgentsTable : public QTableWidget
{
    Q_OBJECT

public:
    AgentsTable  (QWidget *parent = nullptr);
    ~AgentsTable();

signals:
    void changeAgentDescriptionName(int i_agent_id);

public slots:
    void    showTable();
    void    onCurrentAgentChanged(int i_agent_id);
    void    onShowEditAgent();
    void    onCreateAgent();


private slots:
//    void            attractivityChanged(int i_index);
    void            onChangeItem (QTableWidgetItem * item);
    void            onRankChanged (int i_index);
    void            onDoubleClick(QTableWidgetItem* item);
    void            onClickHeader(int i_logical_index);


protected:
    void            mouseReleaseEvent   (QMouseEvent *event);

private:
    //
    enum AgentsTableColumns
    {
         COL_NAME           = 0
        ,COL_RANK           = 1
        ,COL_EMAIL          = 2
        ,COL_PHONE_1        = 3
        ,COL_PHONE_2        = 4
        ,COL_WEB_PROFILE    = 5
        ,COL_AGENCY         = 6
    };
    //
private:
    void                setHeaderParams();
    void                bindSignalsAndSlots();
    void                fillDataRow (int ui_row_num, AgentBaseDTO* ptr_agent);
    void                showPopupMenu();
    int                 getRecordIdByRowNum(int i_row_num);
    void                refreshRow(int i_row_id, int i_agent_id);
    void                setNewSortOrderName();
    void                setNewSortOrderAgency();
    //
    QTableWidgetItem*   makeCellName (AgentBaseDTO* ptr_agent);
    QTableWidgetItem*   makeCellRank(int i_row_num, AgentBaseDTO* ptr_agent);
    QTableWidgetItem*   makeCellEmail (AgentBaseDTO* ptr_agent);
    QTableWidgetItem*   makeCellPhone_1(AgentBaseDTO* ptr_agent);
    QTableWidgetItem*   makeCellPhone_2(AgentBaseDTO* ptr_agent);
    QTableWidgetItem*   makeCellWebProfile(AgentBaseDTO* ptr_agent);
    QTableWidgetItem*   makeCellAgency(AgentBaseDTO* ptr_agent);
    //
    AgentsTableMenu     m_mnuContainer;
    //
    int                 m_iLastSortOrderName;
    int                 m_iLastSortOrderAgency;

    //
    bool    m_bFillTableModeOn;

};

#endif // AGENTSSTABLE_H

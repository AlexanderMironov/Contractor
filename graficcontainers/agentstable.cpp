#include <QStringList>
#include <QHeaderView>
#include <QComboBox>
#include <QMessageBox>
#include <QMenu>
#include <QMouseEvent>
//
#include "commondef.h"
#include "graficcontainers/agentstable.h"
//
#include "config/configuration.h"
//
#include "dto/agentrank.h"
#include "dto/agentbasedto.h"
#include "processor/agentprocessor.h"
//
#include "dto/agencydto.h"
#include "processor/agencyprocessor.h"
//
#include "dto/statusdto.h"
#include "processor/statusprocessor.h"

AgentsTable::AgentsTable(QWidget *parent):QTableWidget(parent)
{
    m_bFillTableModeOn = false;
    setHeaderParams();
    //m_mnuContainer.init(this);
    bindSignalsAndSlots();
    showTable();
}

AgentsTable::~AgentsTable(){

}

void AgentsTable::setHeaderParams(){
    this->setColumnCount(7);
    //
    QStringList str_att_header;
    //                0         1             2           3           4             5       6
    str_att_header<<"Name"<<"Rank"<< "Email"<<"Phone 1"<< "Phone 2"<<"Web profile"<<"Agency";
    this->setHorizontalHeaderLabels(str_att_header);
    //
    QHeaderView *header = this->horizontalHeader();
    //
    this->setColumnWidth(COL_NAME, 65);
    this->setColumnWidth(COL_RANK, 105);
    this->setColumnWidth(COL_EMAIL, 230);
    this->setColumnWidth(COL_PHONE_1, 180);
    this->setColumnWidth(COL_PHONE_2, 180);
    this->setColumnWidth(COL_WEB_PROFILE, 150);
    this->setColumnWidth(COL_AGENCY, 135);
    //
    header->setSectionResizeMode(COL_NAME,          QHeaderView::Stretch);
    header->setSectionResizeMode(COL_RANK,          QHeaderView::Fixed);
    header->setSectionResizeMode(COL_EMAIL,         QHeaderView::Fixed);
    header->setSectionResizeMode(COL_PHONE_1,       QHeaderView::Fixed);
    header->setSectionResizeMode(COL_PHONE_2,       QHeaderView::Fixed);
    header->setSectionResizeMode(COL_WEB_PROFILE,   QHeaderView::Stretch);
    header->setSectionResizeMode(COL_AGENCY,        QHeaderView::Fixed);
}

void AgentsTable::showTable(){
    this->setRowCount(0); //reset the rable;
    //
    const AgentStorage& agents_storage = AgentProcessor::getInstance().getStorage();
    //
    this->setRowCount(agents_storage.size());
    //
    AgentStorage::const_iterator i = agents_storage.constBegin();
    int i_current_row = 0;
    //
    m_bFillTableModeOn = true;
    //
    while(i != agents_storage.constEnd()){
        AgentBaseDTO* ptrDTO = i.value();
        if (nullptr == ptrDTO){
            i++; //increment iterator
            continue;
        };
        //
        fillDataRow(i_current_row, ptrDTO);
        //
        i_current_row++; //increment row
        i++;
    };
    //
    m_bFillTableModeOn = false;
}

void AgentsTable::fillDataRow (int ui_row_num, AgentBaseDTO* ptr_dto){
    QTableWidgetItem* ptr_item_name         = makeCellName(ptr_dto);
    QTableWidgetItem* ptr_item_rate         = makeCellRank(ui_row_num, ptr_dto);
    QTableWidgetItem* ptr_item_email        = makeCellEmail(ptr_dto);
    QTableWidgetItem* ptr_item_phone_1      = makeCellPhone_1(ptr_dto);
    QTableWidgetItem* ptr_item_phone_2      = makeCellPhone_2(ptr_dto);
    QTableWidgetItem* ptr_item_web_profile  = makeCellWebProfile(ptr_dto);
    QTableWidgetItem* ptr_item_agency       = makeCellAgency(ptr_dto);
    //
    this->setItem(ui_row_num, COL_NAME,         ptr_item_name);
    this->setItem(ui_row_num, COL_RANK,         ptr_item_rate);
    this->setItem(ui_row_num, COL_EMAIL,        ptr_item_email);
    this->setItem(ui_row_num, COL_PHONE_1,      ptr_item_phone_1);
    this->setItem(ui_row_num, COL_PHONE_2,      ptr_item_phone_2);
    this->setItem(ui_row_num, COL_WEB_PROFILE,  ptr_item_web_profile);
    this->setItem(ui_row_num, COL_AGENCY,       ptr_item_agency);
}

QTableWidgetItem* AgentsTable::makeCellName(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getName());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    QVariant id_object( ptr_dto->getId() );
    ptr_item_title->setData(Qt::UserRole, id_object);
    return ptr_item_title;
}

QTableWidgetItem*  AgentsTable::makeCellRank(int i_row_num, AgentBaseDTO* ptr_agent){
    QComboBox* combo = new QComboBox();
    //
    combo->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankUnknown), QVariant(static_cast<int>(AGENT_RANK::RankUnknown)));
    combo->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryBad), QVariant(static_cast<int>(AGENT_RANK::RankVeryBad)));
    combo->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankBad), QVariant(static_cast<int>(AGENT_RANK::RankBad)));
    combo->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankNeutral), QVariant(static_cast<int>(AGENT_RANK::RankNeutral)));
    combo->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankGood), QVariant(static_cast<int>(AGENT_RANK::RankGood)));
    combo->addItem(Configuration::getInstance().getAgentRankAsString(AGENT_RANK::RankVeryGood), QVariant(static_cast<int>(AGENT_RANK::RankVeryGood)));
    //
    for (int i = 0; i < combo->count(); ++i){
        QVariant current_rank = combo->itemData(i,Qt::UserRole);
        if (current_rank.toInt() == ptr_agent->getRank()){
            combo->setCurrentIndex(i);
            break;
        };
    };
    //
    QTableWidget::setCellWidget(static_cast<int>(i_row_num), COL_RANK,combo);
    QTableWidgetItem* ptr_item_rank = new  QTableWidgetItem();
    //
    QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(onRankChanged(int)));
    //
    ptr_item_rank->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable );
    ptr_item_rank->setTextAlignment(Qt::AlignCenter);
    //
    return ptr_item_rank;
}

QTableWidgetItem* AgentsTable::makeCellEmail(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getEMail());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_title;
}

QTableWidgetItem* AgentsTable::makeCellPhone_1(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getPhone1());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable|Qt::ItemIsEditable);
    return ptr_item_title;
}

QTableWidgetItem* AgentsTable::makeCellPhone_2(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getPhone2());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable|Qt::ItemIsEditable);
    return ptr_item_title;
}

QTableWidgetItem* AgentsTable::makeCellWebProfile(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getWebProfile());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable |Qt::ItemIsEditable);
    return ptr_item_title;
}

QTableWidgetItem* AgentsTable::makeCellAgency(AgentBaseDTO* ptr_dto){
    QString str_name;
    str_name = AgencyProcessor::getInstance().getAgencyNameByID(ptr_dto->getAgencyId());
    //
    QTableWidgetItem*  ptr_item_agency = new  QTableWidgetItem(str_name);
    ptr_item_agency->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_agency;
}

void AgentsTable::bindSignalsAndSlots(){
     QObject::connect(this,  SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onChangeItem(QTableWidgetItem*)));
}

void AgentsTable::onChangeItem(QTableWidgetItem* item)
{
    if(nullptr == item)
        return;
    //
    if(true == m_bFillTableModeOn){
        return;  //do nothing, it is automatic process
    };
    //
    const int i_column = this->column(item);
    const int i_row = this->row(item);
    const int i_agent_id = getRecordIdByRowNum(i_row);
    //
    if(i_column == COL_WEB_PROFILE){
        const QString str_web_profile = item->text();
        AgentProcessor::getInstance().updateWebProfile(i_agent_id, str_web_profile);
    }else if(i_column == COL_PHONE_1){
        const QString str_phone_num_1 = item->text();
        if(str_phone_num_1.length() == 0){
            QMessageBox box;
            box.setStandardButtons( QMessageBox::Close);
            QString str_box_msg = "Phone number can not be empty";
            box.setText(str_box_msg);
            box.exec();
            return;
        };
        AgentProcessor::getInstance().updatePhone(i_agent_id, str_phone_num_1,AgentProcessor::PHONE_NUM::PHONE_NUM_1);
    }else if(i_column == COL_PHONE_2){
        const QString str_phone_num_2 = item->text();
        AgentProcessor::getInstance().updatePhone(i_agent_id, str_phone_num_2,AgentProcessor::PHONE_NUM::PHONE_NUM_2);
    };
    //

    return;
}

void AgentsTable::mouseReleaseEvent (QMouseEvent *event)
{
    QTableWidget::mouseReleaseEvent(event);
    //
    Qt::MouseButton btn = event->button();
    //
    if ( btn == Qt::RightButton )
    {
       // showPopupMenu ();
    };
}

int AgentsTable::getRecordIdByRowNum(int i_row_num){
    QTableWidgetItem* ptr_item_date   = this->item(static_cast<int>(i_row_num), COL_NAME);
    const QVariant var_record_id = ptr_item_date->data(Qt::UserRole);
    const int i_record_id = var_record_id.toInt();
    return i_record_id;
}

void AgentsTable::onRankChanged (int){
    if (true == m_bFillTableModeOn){
        return;
    };
    //
    int i_current_row = this->currentRow();
    if (i_current_row < 0 ){
        return;
    };
    //

    QTableWidgetItem* ptr_agent_name = this->item(i_current_row, COL_NAME);
    if(nullptr == ptr_agent_name){
        return;
    };
    const int i_agent_id = getRecordIdByRowNum(i_current_row);
    //
    QComboBox* combo =static_cast<QComboBox*> (QTableWidget::cellWidget(i_current_row, COL_RANK));
    const QString str_combo_text = combo->currentText();
    const QVariant variant_rank = combo->currentData(Qt::UserRole);
    if (str_combo_text.length() == 0){
        return;
    };
    //
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Yes|QMessageBox::No );
    QString str_box_msg = QString("Do you really want to change rank of agent [%1] to [%2] ?").arg(ptr_agent_name->text()).arg(str_combo_text);
    box.setText(str_box_msg);
    const int ret = box.exec();
    if (ret != QMessageBox::Yes){
        return;
    };
    //
    AgentProcessor::getInstance().updateRank(i_agent_id, variant_rank.toInt());
}

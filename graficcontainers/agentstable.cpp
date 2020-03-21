#include <QStringList>
#include <QHeaderView>
#include <QComboBox>
#include <QMessageBox>
#include <QMenu>
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
    this->setColumnWidth(COL_PHONE_1, 200);
    this->setColumnWidth(COL_PHONE_2, 200);
    this->setColumnWidth(COL_WEB_PROFILE, 150);
    this->setColumnWidth(COL_AGENCY, 135);
    //
    header->setSectionResizeMode(COL_NAME,          QHeaderView::Stretch);
    header->setSectionResizeMode(COL_RANK,          QHeaderView::Fixed);
    header->setSectionResizeMode(COL_EMAIL,         QHeaderView::Stretch);
    header->setSectionResizeMode(COL_PHONE_1,       QHeaderView::Stretch);
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
    //todo::
    //QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(statusChanged(int)));
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
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_title;
}

QTableWidgetItem* AgentsTable::makeCellPhone_2(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getPhone2());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_title;
}

QTableWidgetItem* AgentsTable::makeCellWebProfile(AgentBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getWebProfile());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
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

/*
QTableWidgetItem* AgentsTable::makeCellAttractity(int ui_row_num, OfferBaseDTO* ptr_dto){
    QComboBox* combo = new QComboBox();
    //
    combo->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_UNKNOWN),  QVariant(ATTRACTIVITY_UNKNOWN));
    combo->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_LOW),      QVariant(ATTRACTIVITY_LOW));
    combo->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_STANDARD), QVariant(ATTRACTIVITY_STANDARD));
    combo->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_HIGH),     QVariant(ATTRACTIVITY_HIGH));
    combo->addItem(Configuration::getInstance().getAttractivityAsString(ATTRACTIVITY_VERY_HIGH),QVariant(ATTRACTIVITY_VERY_HIGH));
    //
    int i_active_index = 0;
    switch(ptr_dto->getAttractivity()){
    case ATTRACTIVITY_UNKNOWN:
        i_active_index = 0;
        break;
    case ATTRACTIVITY_LOW:
        i_active_index = 1;
        break;
    case ATTRACTIVITY_STANDARD:
        i_active_index = 2;
        break;
    case ATTRACTIVITY_HIGH:
        i_active_index = 3;
        break;
    case ATTRACTIVITY_VERY_HIGH:
        i_active_index = 4;
        break;
    }
    //
    combo->setCurrentIndex(i_active_index);
    //
    QTableWidget::setCellWidget(static_cast<int>(ui_row_num), COL_ATTRACTIVITY,combo);
    QTableWidgetItem* ptr_item_attractivity = new QTableWidgetItem();
    //
    QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(attractivityChanged(int)));
    //
    combo->setProperty("row",QVariant(ui_row_num));
    //
    ptr_item_attractivity->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable );
    ptr_item_attractivity->setTextAlignment(Qt::AlignCenter);
    //
    return ptr_item_attractivity;

}
*/
/*
void AgentsTable::attractivityChanged(int i_index){
    //
    if(true == m_bFillTableModeOn){
        return;  //do nothing, it is automatic process
    };
    unsigned int row = static_cast<unsigned int>(sender()->property("row").toInt());
    //
    updateAttractivity(row);
    return;
}
*/
/*
void AgentsTable::statusChanged(int ){
    //
    if(true == m_bFillTableModeOn){
        return;  //do nothing, it is automatic process
    };
    //
    unsigned int row = static_cast<unsigned int>(sender()->property("row").toInt());
    //
    updateStatus(row);
    return;
}
*/

/*
void AgentsTable::onDeleteCurrentOffer(){
    QTableWidgetItem* ptr_current_item = this->currentItem();
    if (nullptr == ptr_current_item){
        return;
    };
    //
    const int i_row = this->row(ptr_current_item);
    //
    QTableWidgetItem* ptr_pos_name_item = this->item(i_row, COL_TITLE);
    const QString str_pos_name = ptr_pos_name_item->text();
    //
    const int i_record_id = getRecordIdByRowNum(i_row);
    if (OfferProcessor::getInstance().removeOffer(i_record_id) == true){
        OfferSkillProcesor::getInstance().removeOffer(i_record_id);
    };
    //
    this->removeRow(i_row);
}
*/

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
/*
    //
    const int i_row   = this->row(item);
    const int i_col   = this->column(item);
    //
    QString str_rate;
    //
    if (i_col == static_cast<int>(COL_RATE)){
        str_rate = item->text();
    };
    bool b_ok = true;
    const int i_rate = str_rate.toInt(&b_ok);
    //
    if (false == b_ok){
        const QString str_msg = QString("can not convert %1 to integer").arg(str_rate);
        QMessageBox::critical(nullptr, "Error", str_msg, QMessageBox::Ok);
        return;
    };
    //
    const int i_record_id = getRecordIdByRowNum(i_row);
    OfferProcessor::getInstance().updateRate(i_record_id, i_rate);
    return;
*/
}
/*
void AgentsTable::onShowNewOfferDlg(){
    emit needNewOfferDlg();
}
*/
/*
void AgentsTable::showPopupMenu(){
    QMenu popup_menu(this);
    //
    const int i_row = this->currentRow();
    const int i_column = this->currentColumn();
    //
    const bool b_disable_delete = (i_row < 0) || (i_column < 0);
    m_mnuContainer.fillPopupMenu(&popup_menu,!b_disable_delete);
    //
    popup_menu.exec(QCursor::pos());
}
*/

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

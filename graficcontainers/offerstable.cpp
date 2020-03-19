#include <QStringList>
#include <QHeaderView>
#include <QComboBox>
#include <QMessageBox>
#include <QMenu>
//
#include "commondef.h"
#include "offerstable.h"
#include "config/configuration.h"
//
#include "dto/offerbasedto.h"
#include "processor/offerprocessor.h"
//
#include "dto/skilldto.h"
#include "processor/skillprocessor.h"
//
#include "dto/countrydto.h"
#include "processor/countryprocessor.h"
//
#include "dto/towndto.h"
#include "processor/townprocessor.h"
//
#include "dto/agentbasedto.h"
#include "processor/agentprocessor.h"
//
#include "dto/agencydto.h"
#include "processor/agencyprocessor.h"
//
#include "dto/statusdto.h"
#include "processor/statusprocessor.h"
//
#include "processor/offerskillprocesor.h"

OffersTable::OffersTable(QWidget *parent):QTableWidget(parent)
{
    m_bFillTableModeOn = false;
    setHeaderParams();
    setPopUpMnu();
    bindSignalsAndSlots();
    showTable();
}

OffersTable::~OffersTable(){

}

void OffersTable::setHeaderParams(){
    this->setColumnCount(10);
    //
    QStringList str_att_header;
    //                0           1            2           3       4        5         6          7             8            9
    str_att_header<<"Date"<< "Pos. Title"<<"Skills"<< "Country"<<"Town"<<"Agent"<<"Agency"<< "Pos. Status"<<"Attractivity"<<"Rate";
    this->setHorizontalHeaderLabels(str_att_header);
    //
    QHeaderView *header = this->horizontalHeader();
    //
    this->setColumnWidth(COL_CREATION_DATE, 85);
    this->setColumnWidth(COL_TITLE, 180);
    this->setColumnWidth(COL_SKILLS, 55);
    this->setColumnWidth(COL_COUNTRY, 85);
    this->setColumnWidth(COL_TOWN, 85);
    this->setColumnWidth(COL_AGENT, 115);
    this->setColumnWidth(COL_AGENCY, 105);
    this->setColumnWidth(COL_STATUS, 160);
    this->setColumnWidth(COL_ATTRACTIVITY, 140);
    this->setColumnWidth(COL_RATE, 45);
    //
    header->setSectionResizeMode(COL_CREATION_DATE, QHeaderView::Fixed);
    header->setSectionResizeMode(COL_TITLE,         QHeaderView::Fixed);
    header->setSectionResizeMode(COL_SKILLS,        QHeaderView::Stretch);
    header->setSectionResizeMode(COL_COUNTRY,       QHeaderView::Fixed);
    header->setSectionResizeMode(COL_TOWN,          QHeaderView::Fixed);
    header->setSectionResizeMode(COL_AGENT,         QHeaderView::Fixed);
    header->setSectionResizeMode(COL_AGENCY,        QHeaderView::Fixed);
    header->setSectionResizeMode(COL_STATUS,        QHeaderView::Fixed);
    header->setSectionResizeMode(COL_ATTRACTIVITY,  QHeaderView::Fixed);
    header->setSectionResizeMode(COL_RATE,          QHeaderView::Fixed);
}

void OffersTable::setPopUpMnu(){
    m_actionShowNewOfferDlg.setText("Add new offer");
    m_actionShowNewOfferDlg.setEnabled(true);
    //
    m_actionDeleteCurrentOffer.setText("Delete current offer");
    m_actionDeleteCurrentOffer.setEnabled(true);
}

void OffersTable::showTable(){
    this->setRowCount(0); //reset the rable;
    //
    const OfferStorage& offers_storage =  OfferProcessor::getInstance().getStorage();
    //
    this->setRowCount(offers_storage.size());
    //
    OfferStorage::const_iterator i = offers_storage.constBegin();
    int i_current_row = 0;
    //
    m_bFillTableModeOn = true;
    //
    while(i != offers_storage.constEnd()){
        OfferBaseDTO* ptrDTO = i.value();
        if (nullptr == ptrDTO){
            i++; //increment iterator
            continue;
        };
        //
        fillDataRow(i_current_row, ptrDTO);
        //
        i_current_row++; //increment row
        i++; //increment iterator
    };
    //
    m_bFillTableModeOn = false;
}

void OffersTable::fillDataRow (int ui_row_num, OfferBaseDTO* ptr_dto){
    QTableWidgetItem* ptr_item_date     = makeCellDate(ptr_dto);
    QTableWidgetItem* ptr_item_title    = makeCellTitle(ptr_dto);
    QTableWidgetItem* ptr_item_skills   = makeCellSkills(ui_row_num, ptr_dto);
    QTableWidgetItem* ptr_item_country  = makeCellCountry(ptr_dto);
    QTableWidgetItem* ptr_item_town     = makeCellTown(ptr_dto);
    QTableWidgetItem* ptr_item_agent    = makeCellAgent(ptr_dto);
    QTableWidgetItem* ptr_item_agency   = makeCellAgency(ptr_dto);
    QTableWidgetItem* ptr_item_status   = makeCellStatus(ui_row_num, ptr_dto);
    QTableWidgetItem* ptr_item_attract  = makeCellAttractity(ui_row_num, ptr_dto);
    QTableWidgetItem* ptr_item_rate     = makeCellRate(ptr_dto);
    //
    this->setItem(ui_row_num, COL_CREATION_DATE,    ptr_item_date);
    this->setItem(ui_row_num, COL_TITLE,            ptr_item_title);
    this->setItem(ui_row_num, COL_SKILLS,           ptr_item_skills);
    this->setItem(ui_row_num, COL_COUNTRY,          ptr_item_country);
    this->setItem(ui_row_num, COL_TOWN,             ptr_item_town);
    this->setItem(ui_row_num, COL_AGENT,            ptr_item_agent);
    this->setItem(ui_row_num, COL_AGENCY,           ptr_item_agency);
    this->setItem(ui_row_num, COL_STATUS,           ptr_item_status);
    this->setItem(ui_row_num, COL_ATTRACTIVITY,     ptr_item_attract);
    this->setItem(ui_row_num, COL_RATE,             ptr_item_rate);
}

QTableWidgetItem* OffersTable::makeCellDate (OfferBaseDTO* ptr_dto)
{
    QTableWidgetItem*   ptr_item_date   = new  QTableWidgetItem( ptr_dto->getCreationDate().toString("dd-MM-yyyy"));
    //
    ptr_item_date->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    QVariant id_object( ptr_dto->getId() );
    ptr_item_date->setData(Qt::UserRole, id_object);
    ptr_item_date->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    return ptr_item_date;
}

QTableWidgetItem* OffersTable::makeCellTitle(OfferBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getPositionTitle());
    ptr_item_title->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_title;
}

QTableWidgetItem* OffersTable::makeCellRate(OfferBaseDTO* ptr_dto){
    const QString str_rate = QString("%1").arg(ptr_dto->getRate());
    QTableWidgetItem*   ptr_item_rate  = new  QTableWidgetItem(str_rate);
    ptr_item_rate->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable| Qt::ItemIsEditable);
    ptr_item_rate->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    return ptr_item_rate;
}

QTableWidgetItem* OffersTable::makeCellSkills(int ui_row_num, OfferBaseDTO* ptr_dto){
    QString str_res_skills;
    const SkillsList&  skill_list_ids = OfferSkillProcesor::getInstance().getSkillsList(ptr_dto->getId());
    //
    for (int i = 0; i < skill_list_ids.size(); ++i){
        QString str_skill = SkillProcessor::getInstance().getSkillNameById(skill_list_ids[i]);
        if (str_res_skills.length() > 0){
            str_res_skills += SKILLS_SEPARATOR;
            str_res_skills += " ";
        };
        str_res_skills += str_skill;
    };
    //
    QTableWidgetItem*   ptr_item_skills = new  QTableWidgetItem(str_res_skills);
    ptr_item_skills->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    ptr_item_skills->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    return ptr_item_skills;
}

QTableWidgetItem* OffersTable::makeCellCountry(OfferBaseDTO* ptr_dto){
    const QString str_country = CountryProcessor::getInstance().getCountryNameByID(ptr_dto->getCountryId());
    QTableWidgetItem*   ptr_item_country = new  QTableWidgetItem(str_country);
    ptr_item_country->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    ptr_item_country->setTextAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    return ptr_item_country;
}

QTableWidgetItem* OffersTable::makeCellTown(OfferBaseDTO* ptr_dto){
    const QString str_town = TownProcessor::getInstance().getTownNameByID(ptr_dto->getTownId());
    QTableWidgetItem*   ptr_item_country = new  QTableWidgetItem(str_town);
    ptr_item_country->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    ptr_item_country->setTextAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    return ptr_item_country;
}

QTableWidgetItem* OffersTable::makeCellAgent(OfferBaseDTO* ptr_dto){
    QString str_ret;
    //
    QTableWidgetItem*  ptr_item_agent = new  QTableWidgetItem();
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByID(ptr_dto->getAgentId());
    //
    if (nullptr != ptr_agent){
        str_ret = ptr_agent->getName();
    };
    ptr_item_agent->setText(str_ret);
    ptr_item_agent->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_agent;
}

QTableWidgetItem* OffersTable::makeCellAgency(OfferBaseDTO* ptr_dto){
    QString str_name;
    //
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByID(ptr_dto->getAgentId());
    if (nullptr != ptr_agent){
        str_name = AgencyProcessor::getInstance().getAgencyNameByID(ptr_agent->getAgencyId());
    };
    //
    QTableWidgetItem*  ptr_item_agency = new  QTableWidgetItem(str_name);
    ptr_item_agency->setFlags( Qt::ItemIsEnabled |Qt::ItemIsSelectable );
    return ptr_item_agency;
}

QTableWidgetItem* OffersTable::makeCellStatus(int ui_row_num, OfferBaseDTO* ptr_dto){
    QComboBox* combo = new QComboBox();
    //
    const StatusStorage& status_storage = StatusProcessor::getInstance().getStorage();
    StatusStorage::const_iterator i = status_storage.constBegin();
    //
    int i_active_index = 0;
    int i_current_index = 0;
    //
    while (i != status_storage.constEnd()) {
        StatusDTO* ptr_status = i.value();
        combo->addItem(ptr_status->getName(), QVariant(ptr_status->getId()));
        if (ptr_status->getId() == ptr_dto->getStatusId()){
            i_active_index = i_current_index;
        };
        //
        i_current_index++;
        i++;
    };
    //
    combo->setCurrentIndex(i_active_index);
    //
    QTableWidget::setCellWidget(static_cast<int>(ui_row_num), COL_STATUS,combo);
    QTableWidgetItem* ptr_item_status = new QTableWidgetItem();
    //
    QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(statusChanged(int)));
    //
    combo->setProperty("row",QVariant(ui_row_num));
    //
    ptr_item_status->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable );
    ptr_item_status->setTextAlignment(Qt::AlignCenter);
    //
    return ptr_item_status;
}

QTableWidgetItem* OffersTable::makeCellAttractity(int ui_row_num, OfferBaseDTO* ptr_dto){
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

void OffersTable::attractivityChanged(int i_index){
    //
    if(true == m_bFillTableModeOn){
        return;  //do nothing, it is automatic process
    };
    unsigned int row = static_cast<unsigned int>(sender()->property("row").toInt());
    //
    updateAttractivity(row);
    return;
}

void OffersTable::statusChanged(int /*index*/){
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

void  OffersTable::updateAttractivity(unsigned int ui_row){

    const int i_record_id = getRecordIdByRowNum(static_cast<int>(ui_row));
    QComboBox*  prt_item_attractivity = dynamic_cast<QComboBox*>(QTableWidget::cellWidget(static_cast<int>(ui_row), COL_ATTRACTIVITY)) ;
    const QVariant var_attractivity = prt_item_attractivity->currentData();
    //
    OfferProcessor::getInstance().updateAttractivity(i_record_id, var_attractivity.toInt());
    return;
}

void OffersTable::updateStatus (unsigned int ui_row){

    const int i_record_id = getRecordIdByRowNum(static_cast<int>(ui_row));
    //
    QComboBox*  prt_item_status = dynamic_cast<QComboBox*>(QTableWidget::cellWidget(static_cast<int>(ui_row), COL_STATUS)) ;
    const QVariant var_status = prt_item_status->currentData();
    //
    OfferProcessor::getInstance().updateOfferStatus(i_record_id, var_status.toInt());
    return;
}

void OffersTable::bindSignalsAndSlots(){
     QObject::connect(this,  SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onChangeItem(QTableWidgetItem*)));
     QObject::connect(&m_actionShowNewOfferDlg, SIGNAL(triggered()), this, SLOT(onShowNewOfferDlg()));
}

void OffersTable::onChangeItem(QTableWidgetItem* item)
{
    if(nullptr == item)
        return;
    //
    if(true == m_bFillTableModeOn){
        return;  //do nothing, it is automatic process
    };
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
}

void OffersTable::onShowNewOfferDlg(){
    emit needNewOfferDlg();
}

void OffersTable::showPopupMenu(){
    QMenu popup_menu(this);
    popup_menu.addAction(&m_actionShowNewOfferDlg);
    //
    const int i_row = this->currentRow();
    const int i_column = this->currentColumn();
    //
    if ((i_row < 0) || (i_column < 0)){
        m_actionDeleteCurrentOffer.setEnabled(false);
    }else{
        m_actionDeleteCurrentOffer.setEnabled(true);
    };
    //
    popup_menu.addAction(&m_actionDeleteCurrentOffer);


    popup_menu.exec(QCursor::pos());
}

void OffersTable::mouseReleaseEvent (QMouseEvent *event)
{
    QTableWidget::mouseReleaseEvent(event);
    //
    Qt::MouseButton btn = event->button();
    //
    if ( btn == Qt::RightButton )
    {
        showPopupMenu ();
    };
}

int OffersTable::getRecordIdByRowNum(int i_row_num){
    QTableWidgetItem* ptr_item_date   = this->item(static_cast<int>(i_row_num), COL_CREATION_DATE);
    const QVariant var_record_id = ptr_item_date->data(Qt::UserRole);
    const int i_record_id = var_record_id.toInt();
    return i_record_id;
}

#include <QStringList>
#include <QHeaderView>
#include <QComboBox>
#include <QMessageBox>
#include <QMenu>
#include <QMouseEvent>
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
//
#include "dialogs/dlgeditviewoffer.h"
#include "dialogs/dlgnewoffer.h"

OffersTable::OffersTable(QWidget *parent):QTableWidget(parent)
{
    m_bFillTableModeOn = false;
    m_i_CurrentAgentId = VALUE_UNDEFINED;
    setHeaderParams();
    m_mnuContainer.init(this);
    bindSignalsAndSlots();
    showTable();
    m_i_CurrentAgentId = VALUE_UNDEFINED;
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
    this->setColumnWidth(COL_AGENT, 135);
    this->setColumnWidth(COL_AGENCY, 135);
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
    ptr_item_date->setFlags( Qt::ItemIsEnabled /*|Qt::ItemIsSelectable */);
    QVariant id_object( ptr_dto->getId() );
    ptr_item_date->setData(Qt::UserRole, id_object);
    ptr_item_date->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    return ptr_item_date;
}

QTableWidgetItem* OffersTable::makeCellTitle(OfferBaseDTO* ptr_dto){
    QTableWidgetItem*   ptr_item_title  = new  QTableWidgetItem( ptr_dto->getPositionTitle());
    ptr_item_title->setFlags( Qt::ItemIsEnabled /*|Qt::ItemIsSelectable */);
    ptr_item_title->setToolTip(ptr_dto->getPositionTitle());
    return ptr_item_title;
}

QTableWidgetItem* OffersTable::makeCellRate(OfferBaseDTO* ptr_dto){
    const QString str_rate = QString("%1").arg(ptr_dto->getRate());
    QTableWidgetItem*   ptr_item_rate  = new  QTableWidgetItem(str_rate);
    ptr_item_rate->setFlags( Qt::ItemIsEnabled |/*Qt::ItemIsSelectable|*/ Qt::ItemIsEditable);
    ptr_item_rate->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    return ptr_item_rate;
}

QTableWidgetItem* OffersTable::makeCellSkills(int ui_row_num, OfferBaseDTO* ptr_dto){
    QString str_res_skills = getSkillsListAsString(ptr_dto);
    //
    QTableWidgetItem*  ptr_item_skills = new  QTableWidgetItem(str_res_skills);
    ptr_item_skills->setFlags( Qt::ItemIsEnabled/* |Qt::ItemIsSelectable */);
    ptr_item_skills->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    return ptr_item_skills;
}

QTableWidgetItem* OffersTable::makeCellCountry(OfferBaseDTO* ptr_dto){
    const QString str_country = CountryProcessor::getInstance().getCountryNameByID(ptr_dto->getCountryId());
    QTableWidgetItem*   ptr_item_country = new  QTableWidgetItem(str_country);
    ptr_item_country->setData(Qt::UserRole, ptr_dto->getCountryId());
    ptr_item_country->setFlags( Qt::ItemIsEnabled /*|Qt::ItemIsSelectable */);
    ptr_item_country->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    return ptr_item_country;
}

QTableWidgetItem* OffersTable::makeCellTown(OfferBaseDTO* ptr_dto){
    const QString str_town = TownProcessor::getInstance().getTownNameByID(ptr_dto->getTownId());
    QTableWidgetItem*   ptr_item_country = new  QTableWidgetItem(str_town);
    ptr_item_country->setFlags( Qt::ItemIsEnabled/* |Qt::ItemIsSelectable */);
    ptr_item_country->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
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
    //
    if (ptr_agent->getDescription().length() > 0){
        ptr_item_agent->setToolTip(ptr_agent->getDescription());
    }else{
        ptr_item_agent->setToolTip("Description not available");
    };
    //
    ptr_item_agent->setText(str_ret);
    ptr_item_agent->setData(Qt::UserRole, QVariant(ptr_dto->getAgentId()));
    ptr_item_agent->setFlags( Qt::ItemIsEnabled /*|Qt::ItemIsSelectable */);
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
    ptr_item_agency->setFlags( Qt::ItemIsEnabled /*|Qt::ItemIsSelectable */);
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
}

void OffersTable::onEditCurrentOffer(){
    QTableWidgetItem* ptr_current_item = this->currentItem();
    if (nullptr == ptr_current_item){
        return;
    };
    //
    const int i_row = this->row(ptr_current_item);
    const int job_offer_id = getRecordIdByRowNum(i_row);
    DlgEditViewOffer dlg;
    dlg.init(job_offer_id);
    dlg.exec();
    //todo:update line if it was changed
    if (dlg.isSomethingChanged() == true){
        updateRow(i_row);
    }
}

void OffersTable::updateRow(int i_row_num){

    const int i_offer_id = getRecordIdByRowNum(i_row_num);
    OfferBaseDTO* ptr_offer = OfferProcessor::getInstance().getOfferById(i_offer_id);
    if (nullptr == ptr_offer){
        return;
    };
    //
    QTableWidgetItem* ptr_title = this->item(i_row_num, COL_TITLE);
    if(ptr_title){
        if(ptr_offer->getPositionTitle().isEmpty() == false){
            ptr_title->setText(ptr_offer->getPositionTitle());
        }else{
            ptr_title->setText("");
        };

    };
    //
    QTableWidgetItem* ptr_skills = this->item(i_row_num, COL_SKILLS);
    if(ptr_skills){
        QString str_res_skills = getSkillsListAsString(ptr_offer);
        if(str_res_skills.isEmpty() == false){
            ptr_skills->setText(str_res_skills);
        }else{
            ptr_skills->setText("");
        };
    };
    //
    QTableWidgetItem* ptr_country = this->item(i_row_num, COL_COUNTRY);
    if(ptr_country){
        ptr_country->setText(CountryProcessor::getInstance().getCountryNameByID(ptr_offer->getCountryId()));
        ptr_country->setData(Qt::UserRole,QVariant(ptr_offer->getCountryId()));
    };
    //
    QTableWidgetItem* ptr_town = this->item(i_row_num, COL_TOWN);
    if(ptr_town){
        ptr_town->setText(TownProcessor::getInstance().getTownNameByID(ptr_offer->getTownId()));
        ptr_town->setData(Qt::UserRole,QVariant(ptr_offer->getTownId()));
    };
    //
    QTableWidgetItem* ptr_rate = this->item(i_row_num, COL_RATE);
    if(ptr_rate){
        ptr_rate->setText(QString("%1").arg(ptr_offer->getRate()));
    };
    //
    QComboBox*  ptr_item_status = dynamic_cast<QComboBox*>(QTableWidget::cellWidget(i_row_num, COL_STATUS));
    if(nullptr != ptr_item_status){
        for(int i = 0; i < ptr_item_status->count(); i++){
            const int i_current_status = ptr_item_status->itemData(i,Qt::UserRole).toInt();
            if(i_current_status == ptr_offer->getStatusId()){
                if(i == ptr_item_status->currentIndex()){
                    break; //nothing changed
                }else{
                    ptr_item_status->setCurrentIndex(i);
                    break; //done
                };
            };
        };
    };
    //
    QComboBox*  ptr_item_attractivity = dynamic_cast<QComboBox*>(QTableWidget::cellWidget(i_row_num, COL_ATTRACTIVITY));
    if(nullptr != ptr_item_attractivity){
        for(int i = 0; i < ptr_item_attractivity->count(); i++){
            const int i_current_attractivity = ptr_item_attractivity->itemData(i,Qt::UserRole).toInt();
            if(i_current_attractivity == ptr_offer->getAttractivity()){
                if(i == ptr_item_attractivity->currentIndex()){
                    break; //nothing changed
                }else{
                    ptr_item_attractivity->setCurrentIndex(i);
                    break; //done
                };
            };
        };
    };
}

void OffersTable::onDeleteCurrentOffer(){
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
        QMessageBox box;
        box.setStandardButtons( QMessageBox::Yes|QMessageBox::No );
        QString str_box_msg = QString("Do you really want to delete offer [%1]").arg(str_pos_name);
        box.setText(str_box_msg);
        const int ret = box.exec();
        if (ret != QMessageBox::Yes){
            return;
        };
    //
    const int i_record_id = getRecordIdByRowNum(i_row);
    if (OfferProcessor::getInstance().removeOffer(i_record_id) == true){
        OfferSkillProcesor::getInstance().removeOffer(i_record_id);
    };
    //
    this->removeRow(i_row);
}

void OffersTable::bindSignalsAndSlots(){
     QObject::connect(this,  SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onChangeItem(QTableWidgetItem*)));
     QObject::connect(this,  SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(onCurrentCellChanged(int, int, int, int)));
     QObject::connect(this,  SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(onDoubleClick(QTableWidgetItem*)));
}

void OffersTable::onChangeAgentName(int i_agent_id){
    m_bFillTableModeOn = true;
    //
    AgentBaseDTO* ptr_agent = AgentProcessor::getInstance().getAgentByID(i_agent_id);
    if(nullptr == ptr_agent){
        return;
    };

    for (int i_row = 0; i_row < this->rowCount(); i_row++){
        QTableWidgetItem* ptr_agent_name_item = this->item(i_row, COL_AGENT);
        if(nullptr == ptr_agent_name_item){
            continue;
        };
        //
        if(ptr_agent_name_item->data(Qt::UserRole).toInt() == ptr_agent->getId()){
            ptr_agent_name_item->setText(ptr_agent->getName());
            if (ptr_agent->getDescription().length() > 0){
                ptr_agent_name_item->setToolTip(ptr_agent->getDescription());
            }else{
                ptr_agent_name_item->setToolTip("Description not available");
            };
        };
    };
    //
    m_bFillTableModeOn = false;
}

void OffersTable::onChangeCountryName(int i_country_id){
    m_bFillTableModeOn = true;
    for (int i_row = 0; i_row < this->rowCount(); i_row++){
        QTableWidgetItem* ptr_country_item = this->item(i_row, COL_COUNTRY);
        if(nullptr == ptr_country_item){
            continue;
        };
        //
        const QVariant var_country_id = ptr_country_item->data(Qt::UserRole);
        //
        if (var_country_id.toInt() == i_country_id){
            const QString str_new_country_name = CountryProcessor::getInstance().getCountryNameByID(var_country_id.toInt());
            ptr_country_item->setText(str_new_country_name);
        };
    };
    m_bFillTableModeOn = false;
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
    };

    return;
}

void OffersTable::onCurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn){
    if (m_bFillTableModeOn == true){
        return;
    };
    //
    if (currentRow == previousRow){
        return; //do nothing, agent was not changed
    };
    QTableWidgetItem* ptr_country_agent = this->item(currentRow,COL_AGENT);
    if(nullptr == ptr_country_agent){
        return;
    };
    //
    QVariant var_agent_id = ptr_country_agent->data(Qt::UserRole);
    //
    if (m_i_CurrentAgentId != var_agent_id.toInt()){
        m_i_CurrentAgentId =var_agent_id.toInt();
        emit currentAgentChanged(var_agent_id.toInt());
    };
}

void OffersTable::onCreateOffer(){
    DlgNewOffer dlgNewOffer;
    dlgNewOffer.init();
    dlgNewOffer.exec();
    //
    if(dlgNewOffer.isbOfferSaved() == true){
        this->showTable();
        //
        if(dlgNewOffer.isNewAgentAdded()){
            emit agentAdded();
        };
    };
}

void OffersTable::showPopupMenu(){
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

void OffersTable::onDoubleClick(QTableWidgetItem* item){
    if(nullptr == item){
        return;
    };
    //
    if(COL_TITLE == item->column()){
        onEditCurrentOffer();
    };
}

int OffersTable::getRecordIdByRowNum(int i_row_num){
    QTableWidgetItem* ptr_item_date   = this->item(static_cast<int>(i_row_num), COL_CREATION_DATE);
    const QVariant var_record_id = ptr_item_date->data(Qt::UserRole);
    const int i_record_id = var_record_id.toInt();
    return i_record_id;
}

QString OffersTable::getSkillsListAsString(OfferBaseDTO* ptr_dto) const{
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
    return str_res_skills;
}

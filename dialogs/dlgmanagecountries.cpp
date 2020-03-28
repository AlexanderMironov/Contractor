#include <QListWidgetItem>
#include <QMessageBox>
//
#include "dlgmanagecountries.h"
//
#include "dto/countrydto.h"
#include "processor/countryprocessor.h"
//
#include "commondef.h"

DlgManageCountries::DlgManageCountries(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Manage countries");
    m_iItemsWidth = 170;
    m_iItemsHeight = 20;
    m_bFillModeOn = false;
}

DlgManageCountries::~DlgManageCountries(){

}

void DlgManageCountries::init(){
    m_bFillModeOn = true;
    setDlgLayout();
    createWidgets();
    addWidgetsToLayout();
    //
    this->setMinimumWidth(400);
    this->setMaximumWidth(400);
    //
    this->setMinimumHeight(200);
    this->setMaximumHeight(200);
    m_bFillModeOn = false;
}

void DlgManageCountries::setDlgLayout(){
    this->setLayout(&m_MainLayout);
}

void DlgManageCountries::createWidgets(){
    createCountriesList();
    createEditField();
    createButtons();

}

void DlgManageCountries::addWidgetsToLayout(){
    const int i_total_row_number = 3;
    //
    int i_row = 0;
    //->addWidget(ptr_widget, row,column,rowSpan,columnSpan, aligment);
    m_MainLayout.addWidget(&m_wListOfCountries,i_row,0,i_total_row_number,1);
    m_MainLayout.addWidget(&m_EditCountry,i_row,1,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonAddNew,i_row,1,1,1);
    //
    i_row++;
    m_MainLayout.addWidget(&m_ButtonModifyCurrent,i_row,1,1,1);
}

void DlgManageCountries::createButtons(){
    m_ButtonAddNew.setMinimumWidth(m_iItemsWidth);
    m_ButtonAddNew.setMaximumWidth(m_iItemsWidth);
    m_ButtonAddNew.setMinimumHeight(m_iItemsHeight);
    m_ButtonAddNew.setMaximumHeight(m_iItemsHeight);
    m_ButtonAddNew.setText("Add new country");
    m_ButtonAddNew.setEnabled(true);
    connect(&m_ButtonAddNew, &QPushButton::released, this, &DlgManageCountries::onClickButtonAddNew);
    //
    m_ButtonModifyCurrent.setMinimumWidth(m_iItemsWidth);
    m_ButtonModifyCurrent.setMaximumWidth(m_iItemsWidth);
    m_ButtonModifyCurrent.setMinimumHeight(m_iItemsHeight);
    m_ButtonModifyCurrent.setMaximumHeight(m_iItemsHeight);
    m_ButtonModifyCurrent.setText("Modify selected country");
    connect(&m_ButtonModifyCurrent, &QPushButton::released, this, &DlgManageCountries::onClickButtonModifyCurrent);
    m_ButtonModifyCurrent.setEnabled(false);
}

void DlgManageCountries::createEditField(){
    m_EditCountry.setMinimumWidth(m_iItemsWidth);
    m_EditCountry.setMaximumWidth(m_iItemsWidth);
    //
    m_EditCountry.setMinimumHeight(m_iItemsHeight);
    m_EditCountry.setMaximumHeight(m_iItemsHeight);
    //
    connect(&m_EditCountry, SIGNAL(textChanged(const QString&)), this, SLOT(onEditTextChanged(const QString&)));

}

void DlgManageCountries::createCountriesList(){
    const CountryStorage&  country_storage = CountryProcessor::getInstance().getStorage();
    CountryStorage::const_iterator i = country_storage.constBegin();
    while(i != country_storage.constEnd()){
        CountryDTO* ptr_country = i.value();
        QListWidgetItem* ptr_item = new QListWidgetItem(ptr_country->getName());
        ptr_item->setData(Qt::UserRole, QVariant(i.key()));
        m_wListOfCountries.addItem(ptr_item);
        i++;
    };
    //
    connect(&m_wListOfCountries, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(onCurrentItemChanged(QListWidgetItem*, QListWidgetItem*)));
}

void DlgManageCountries::onClickButtonModifyCurrent(){
    if (m_EditCountry.text().length() == 0){
        return;
    };
    //
    QListWidgetItem* ptr_item = m_wListOfCountries.currentItem();
    if(nullptr == ptr_item){

    };
    //
    QString str_msg = QString ("Do you want to replace name of the country from [%1] to [%2]?").arg(ptr_item->text()).arg(m_EditCountry.text());
    QMessageBox box;
    box.setStandardButtons( QMessageBox::Yes|QMessageBox::No );
    box.setText(str_msg);
    const int ret = box.exec();
    if (ret != QMessageBox::Yes){
        return;
    };
    //
    const QVariant var_country_id = ptr_item->data(Qt::UserRole);
    ptr_item->setText(m_EditCountry.text());
    //
    CountryProcessor::getInstance().updateCountryName(var_country_id.toInt(), m_EditCountry.text());
    emit modifyCountry(var_country_id.toInt());
}

void DlgManageCountries::onClickButtonAddNew(){
    if (m_EditCountry.text().length() == 0){
        return;
    };
    //
    if (CountryProcessor::getInstance().isCountryAlreadyExists(m_EditCountry.text()) != VALUE_UNDEFINED){
        QMessageBox box;
        box.setStandardButtons( QMessageBox::Ok);
        QString str_msg = QString("Country [%1] already exists").arg(m_EditCountry.text());
        box.setText(str_msg);
        box.exec();
        return;
    };
    //
    int i_country_id = CountryProcessor::getInstance().add(m_EditCountry.text());
    //
    if (VALUE_UNDEFINED == i_country_id){
        return;
    };
    //
    m_bFillModeOn = true;
    QListWidgetItem* ptr_item = new QListWidgetItem(m_EditCountry.text());
    ptr_item->setData(Qt::UserRole, QVariant(i_country_id));
    m_wListOfCountries.addItem(ptr_item);
    m_bFillModeOn = false;
    emit createNewCountry();
}




void DlgManageCountries::onEditTextChanged(const QString& str_txt){
    if(true == m_bFillModeOn){
        return;
    };
    //
    if (str_txt.length() == 0){
        m_ButtonModifyCurrent.setEnabled(false);
        m_ButtonAddNew.setEnabled(false);
    }else{
        m_ButtonModifyCurrent.setEnabled(true);
        m_ButtonAddNew.setEnabled(true);
    };
}

void DlgManageCountries::onCurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous){
    if (nullptr == current){
        return;
    };
    //
    if(true == m_bFillModeOn){
        return;
    };
    //
    m_EditCountry.setText(current->text());
}

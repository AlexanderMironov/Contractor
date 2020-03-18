#include <QSettings>
#include <QList>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>
//
#include "configuration.h"
#include "config/configbasefunctionality.h"
#include "config/configdef.h"
//
//
QString Configuration::CONFIG_FILE_NAME ="contractor.cfg";
//
Configuration::Configuration()
{
    m_ptrSettings = nullptr;
}

Configuration::~Configuration(){
    if (nullptr != m_ptrSettings)
    {
        delete m_ptrSettings;
    };
}

Configuration& Configuration::getInstance(){
    static Configuration config;
    return config;
}

bool Configuration::init(){
    if (nullptr != m_ptrSettings)
    {
        return true; //already done;
    };
    //
    const QString config_file_name = Configuration::getConfigFullPath();
    //
    if (ConfigBaseFunctionality::isConfigFileExists(config_file_name) == false){
        return false;
    };
    //
    m_ptrSettings = new QSettings(config_file_name, QSettings::IniFormat);
    //
    bool b_res = getDBSettings(m_ptrSettings);
    if (false == b_res){
        return false;
    };
    //
    b_res = getAttractivity(m_ptrSettings);
    if (false == b_res){
        return false;
    };
    //
    return b_res;
}

const QString& Configuration::getAttractivityAsString(ATTRACTIVITY en_attractivity){
    switch(en_attractivity){
    case ATTRACTIVITY_UNKNOWN:
        return m_str_AttractivityUnknown;
    case ATTRACTIVITY_LOW:
        return m_str_AttractivityLow;
    case ATTRACTIVITY_STANDARD:
        return m_str_AttractivityStandard;
    case ATTRACTIVITY_HIGH:
        return m_str_AttractivityHigh;
    case ATTRACTIVITY_VERY_HIGH:
        return m_str_AttractivityVeryHigh;
    };
}

bool Configuration::getAttractivity(QSettings *ptr_settings){
    bool b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_str_AttractivityUnknown,ATTRACTIVITY_SECTION_NAME, AT_ATTRACTIVITY_UNKNOWN, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_str_AttractivityLow,ATTRACTIVITY_SECTION_NAME, AT_ATTRACTIVITY_LOW, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_str_AttractivityStandard,ATTRACTIVITY_SECTION_NAME, AT_ATTRACTIVITY_STANDARD, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_str_AttractivityHigh,ATTRACTIVITY_SECTION_NAME, AT_ATTRACTIVITY_HIGH, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_str_AttractivityVeryHigh,ATTRACTIVITY_SECTION_NAME, AT_ATTRACTIVITY_VERY_HIGH, false);
    if (false == b_res){
        return false;
    };
}

QString Configuration::getConfigFullPath(){
    const QString path = QCoreApplication::applicationDirPath();
    const QString fullPath = path+ "/" + Configuration::CONFIG_FILE_NAME;
    return fullPath;
}

bool Configuration::getDBSettings(QSettings* ptr_settings){
    bool b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_strDBHost,DB_SECTION_NAME, DB_HOST, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_iDBPort,DB_SECTION_NAME, DB_PORT, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_strDBName,DB_SECTION_NAME, DB_NAME, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_strDBUser,DB_SECTION_NAME, DB_USER, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_strDBPassword,DB_SECTION_NAME, DB_PASSWORD, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_strDBConnectionName,DB_SECTION_NAME, DB_CONNECTIONAME, false);
    if (false == b_res){
        return false;
    };
    //
    b_res = ConfigBaseFunctionality::assignValue(ptr_settings, m_strDBDatabaseType,DB_SECTION_NAME, DB_DATABASETYPE, false);
    if (false == b_res){
        return false;
    };
    //
    return true;
}

const QString& Configuration::getDBHostName() const{return m_strDBHost;}
int Configuration::getDBPort() const{return m_iDBPort;}
const QString& Configuration::getDBName() const{return m_strDBName;}
const QString& Configuration::getDBUserName() const{ return m_strDBUser;}
const QString& Configuration::getDBUserPassword() const{return m_strDBPassword;}
const QString& Configuration::getDBConnectionName() const{return m_strDBConnectionName;}
const QString& Configuration::getDBDatabaseType() const{return m_strDBDatabaseType;}

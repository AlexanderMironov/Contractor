#include <QSettings>
#include <QDebug>
#include <QFileInfo>
//
#include "configbasefunctionality.h"

ConfigBaseFunctionality::ConfigBaseFunctionality()
{

}

bool ConfigBaseFunctionality::isConfigFileExists(const QString& str_config_file_name){
    QFileInfo check_file(str_config_file_name);
    if (check_file.exists() == false){
        qDebug()<<"configuration file: "<<str_config_file_name<<" does not exist, create it first";
        return false;
    };
    return true;
}

bool ConfigBaseFunctionality::assignValue(QSettings *ptr_settings, int& var, const char* ptr_section_name, const char* ptr_keyName, bool b_allow_zero){
    var = ConfigBaseFunctionality::getValueAsInt(ptr_settings, ptr_section_name, ptr_keyName);
    if(var > 0){
        return true;
    };
    if (false == b_allow_zero){
        qDebug()<<"configuration parameter: "<<ptr_section_name<<"/"<<ptr_keyName<<" does not exist, create it first";
        return false;
    };
    //
    return true;
}

bool ConfigBaseFunctionality::assignValue(QSettings* ptr_settings, QString& var, const char* ptr_section_name, const char* ptr_keyName, bool b_allow_empty){
    var = ConfigBaseFunctionality::getValueAsString(ptr_settings, ptr_section_name, ptr_keyName);
    if (var.length() > 0){
        return true;
    };
    if (false == b_allow_empty){
        qDebug()<<"configuration parameter: "<<ptr_section_name<<"/"<<ptr_keyName<<" does not exist, create it first";
        return false;
    };
    //
    return true;
}

QString ConfigBaseFunctionality::getValueAsString(QSettings* ptr_settings, const char* ptr_section_name, const char* ptr_keyName){
    const QString delim = "/";
    const QString key = ptr_section_name + delim + ptr_keyName;
    QString value;
    if (nullptr != ptr_settings){
        value = ptr_settings->value(key).toString();
    };
    //
    return value;
}

int ConfigBaseFunctionality::getValueAsInt(QSettings *ptr_settings, const char* ptr_section_name, const char* ptr_keyName){
    const QString str_res = ConfigBaseFunctionality::getValueAsString(ptr_settings, ptr_section_name, ptr_keyName);
    int i_res = str_res.toInt();
    return i_res;
}

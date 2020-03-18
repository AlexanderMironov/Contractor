#ifndef CONFIGBASESUPPORT_H
#define CONFIGBASESUPPORT_H
/**
 * @brief The ConfigBaseSupport class supports base config functionality: read configurations parameters and represent it as String or Integer
 */

#include <QString>

class QSettings;

class ConfigBaseFunctionality
{
public:
    static bool isConfigFileExists(const QString& str_config_file_name);
    static bool assignValue(QSettings *ptr_settings, QString& var, const char* ptr_section_name, const char* ptr_keyName, bool b_allow_empty);
    static bool assignValue(QSettings* ptr_settings, int& var, const char* ptr_section_name, const char* ptr_keyName, bool b_allow_zero);
    //
    static QString getValueAsString(QSettings *ptr_settings, const char* ptr_section_name, const char* ptr_keyName);
    static int     getValueAsInt(QSettings *ptr_settings, const char* ptr_section_name, const char* ptr_keyName);

private:
    ConfigBaseFunctionality();
};

#endif // CONFIGBASESUPPORT_H

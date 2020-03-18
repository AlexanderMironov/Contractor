#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <QList>
#include <QString>
//
#include "dto/attractivity.h"

class QSettings;

class Configuration
{
public:
    static QString CONFIG_FILE_NAME;
    static Configuration& getInstance();
    ~Configuration();
    //
    bool init();
    //
    const QString& getDBHostName() const;
    int            getDBPort() const;
    const QString& getDBName() const;
    const QString& getDBUserName() const;
    const QString& getDBUserPassword() const;
    const QString& getDBConnectionName() const;
    const QString& getDBDatabaseType() const;
    const QString& getAttractivityAsString(ATTRACTIVITY en_attractivity);

private:
    Configuration();
    bool getDBSettings(QSettings* ptr_settings);
    bool getAttractivity(QSettings* ptr_settings);
    static QString    getConfigFullPath();
    //
private:
    QSettings*  m_ptrSettings;
    //
    QString m_strDBHost;
    int     m_iDBPort;
    QString m_strDBName;
    QString m_strDBUser;
    QString m_strDBPassword;
    QString m_strDBConnectionName;
    QString m_strDBDatabaseType;
    //
    QString m_str_AttractivityUnknown;
    QString m_str_AttractivityLow;
    QString m_str_AttractivityStandard;
    QString m_str_AttractivityHigh;
    QString m_str_AttractivityVeryHigh;

};

#endif // CONFIGURATION_H

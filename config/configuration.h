#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include <QList>
#include <QString>
//
#include "dto/attractivity.h"
#include "dto/agentrank.h"

class QSettings;
class QTextStream;

class Configuration
{
public:
    static QString CONFIG_FILE_NAME;
    static Configuration& getInstance();
    ~Configuration();
    //
    bool init();
    //
    const QString&  getDBHostName() const;
    int             getDBPort() const;
    const QString&  getDBName() const;
    const QString&  getDBUserName() const;
    const QString&  getDBUserPassword() const;
    const QString&  getDBConnectionName() const;
    const QString&  getDBDatabaseType() const;
    const QString&  getAttractivityAsString(ATTRACTIVITY en_attractivity)const;
    const QString&  getAgentRankAsString(AGENT_RANK en_rank) const;
    const QString&  getDefaultExportPath() const;
    const QString&  getDefaultImportPath() const;
    const QString&  getLogFileName() const;
    int             getLogMode() const;

private:
                    Configuration();
    bool            getLogSettings(QSettings* ptr_settings);
    bool            getDBSettings(QSettings* ptr_settings);
    bool            getAgentRank(QSettings* ptr_settings);
    bool            getAttractivity(QSettings* ptr_settings);
    bool            getPaths(QSettings* ptr_settings);
    static QString  getConfigFullPath();
    //
private:
    QSettings*      m_ptrSettings;
    //
    QString         m_strDBHost;
    int             m_iDBPort;
    QString         m_strDBName;
    QString         m_strDBUser;
    QString         m_strDBPassword;
    QString         m_strDBConnectionName;
    QString         m_strDBDatabaseType;
    //
    QString         m_str_AttractivityUnknown;
    QString         m_str_AttractivityLow;
    QString         m_str_AttractivityStandard;
    QString         m_str_AttractivityHigh;
    QString         m_str_AttractivityVeryHigh;
    //
    QString         m_str_RankUnknown;
    QString         m_str_RankVeryBad;
    QString         m_str_RankBad;
    QString         m_str_RankNeutral;
    QString         m_str_RankGood;
    QString         m_str_RankVeryGood;
    //
    QString         m_str_DefaultExportPath;
    QString         m_str_DefaultImportPath;
    //
    QString         m_str_LogFileName;
    int             m_iLogMode;
    //
    QTextStream*    m_ptrOut;

};

#endif // CONFIGURATION_H

#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QMap>
//
class LogWriter;

typedef QMap<QString, LogWriter*> LoggerContainer;

class LoggerManager : public QObject
{
    Q_OBJECT
public:
    static LoggerManager& getInstance();
    ~LoggerManager();
    //
    bool            createLogger(const char* name, const QString& log_file);
    LogWriter*      getWriter(const QString& name);

signals:

public slots:

private:
    explicit        LoggerManager(QObject *parent = nullptr);


private:
    QMutex          m_Mutex;
    LoggerContainer m_loggerMap;
};

#endif // LOGGER_H

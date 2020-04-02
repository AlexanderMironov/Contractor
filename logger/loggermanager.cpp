#include <QMutexLocker>
//
#include "loggermanager.h"
#include "logger/logwriter.h"

LoggerManager::LoggerManager(QObject *parent) : QObject(parent)
{

}

LoggerManager::~LoggerManager(){
    //clear memory
    LoggerContainer::const_iterator itr = m_loggerMap.begin();
    for ( ; itr != m_loggerMap.end(); ++itr){
        delete itr.value();
    }
}

LoggerManager& LoggerManager::getInstance(){
    static LoggerManager instance;
    return instance;
}
bool LoggerManager::createLogger(const char* name, const QString& log_file){
    if (nullptr == name){
        return false;
    }
    //
    QMutexLocker locker(&m_Mutex);
    QString logger_name = name;
    //
    LoggerContainer::const_iterator itr = m_loggerMap.find(logger_name);
    //
    if (itr != m_loggerMap.end()){
        return true; //logger already exist
    }
    //
    LogWriter* writer = new LogWriter(name, log_file);
    //
    m_loggerMap.insert(logger_name, writer);
    //
    return true;
}

LogWriter* LoggerManager::getWriter(const QString& name){
    LoggerContainer::const_iterator itr = m_loggerMap.find(name);
    if (itr == m_loggerMap.end()){
        return nullptr;
    }
    //
    LogWriter* ptr = itr.value();
    return ptr;
}

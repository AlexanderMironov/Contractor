#include <QMutex>
#include <QMutexLocker>
#include <QTextCodec>
//
#include "logger/logwriter.h"

 LogWriter::LogWriter(const char* logger_name, const QString& file_name, QObject *parent) : QObject(parent)
{
    m_ptrFile = nullptr;
    m_ptrOutStream = nullptr;
    m_ptrConsoleStream = nullptr;
    m_ptrAccessLocker = nullptr;
    //
    this->logger_name = logger_name;
    m_strFileName = file_name;
    //
    if (m_strFileName.length() > 0){
        m_ptrFile = new QFile(m_strFileName);
        //overwrite previous file
        if ( m_ptrFile->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
        {
            m_ptrOutStream = new QTextStream(m_ptrFile);
            m_ptrAccessLocker = new QMutex(QMutex::Recursive);
        };
    };
    //
#ifdef QT_NO_DEBUG
    m_ptrConsoleStream = new QTextStream(stdout);
#else
    if (m_strFileName.length() == 0){ //if main output in release not defined - make output in console
    m_ptrConsoleStream = new QTextStream(stdout);
    }
#endif
}

 LogWriter::~ LogWriter(){
    //
    if (nullptr != m_ptrOutStream){
        m_ptrOutStream->flush();
        delete m_ptrOutStream;
    }
    //
    if(nullptr != m_ptrFile){
        if (m_ptrFile->isOpen() == true){
            m_ptrFile->close();
        }
        //
        delete m_ptrFile;
    }
    //
    if (nullptr != m_ptrAccessLocker){
        delete m_ptrAccessLocker;
    }
}


LogWriter& LogWriter::operator<<(const QByteArray& msg){
    QMutexLocker locker (m_ptrAccessLocker);
    QString string = QTextCodec::codecForMib(106)->toUnicode(msg);
    if(m_ptrOutStream){
        (*m_ptrOutStream)<<string;
        m_ptrOutStream->flush();
    };
    //
    if(m_ptrConsoleStream){
        (*m_ptrConsoleStream)<<string;
        m_ptrConsoleStream->flush();
    };
    return (*this);
}

LogWriter&  LogWriter::operator<<(const QString &string)
{
    QMutexLocker locker (m_ptrAccessLocker);
    if(m_ptrOutStream){
        (*m_ptrOutStream)<<string;
        m_ptrOutStream->flush();
    };
    //
    if(m_ptrConsoleStream){
        (*m_ptrConsoleStream)<<string;
        m_ptrConsoleStream->flush();
    };
    return (*this);
}

LogWriter& LogWriter::operator<<(int value){
    QMutexLocker locker (m_ptrAccessLocker);
    //
    if(m_ptrOutStream){
        (*m_ptrOutStream)<<value;
        m_ptrOutStream->flush();
    };
    //
    if(m_ptrConsoleStream){
        (*m_ptrConsoleStream)<<value;
        m_ptrConsoleStream->flush();
    };
    //
    return (*this);
}

LogWriter& LogWriter::operator<<(const char* t){
    QMutexLocker locker (m_ptrAccessLocker);
    if (nullptr == t){
        return (*this);
    };
    //
    if(m_ptrOutStream){
        (*m_ptrOutStream)<<t;
        m_ptrOutStream->flush();
    };
    //
    if(m_ptrConsoleStream){
        (*m_ptrConsoleStream)<<t;
        m_ptrConsoleStream->flush();
    };
    //
    return (*this);
}

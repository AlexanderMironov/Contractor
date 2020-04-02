#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QByteArray>

//
class QMutex;

class LogWriter : public QObject
{
    Q_OBJECT
public:
    explicit  LogWriter(const char* logger_name, const QString& file_name, QObject *parent = nullptr);
    ~ LogWriter();

    LogWriter& operator<<(const QString &string);
    LogWriter& operator<<(int value);
    LogWriter& operator<<(const char* t);
    LogWriter& operator<<(const QByteArray& msg);

signals:

public slots:

private:
    QString     logger_name;
    QString     m_strFileName;
    QFile*      m_ptrFile;
    QTextStream* m_ptrOutStream;
    QTextStream* m_ptrConsoleStream;
    QMutex*     m_ptrAccessLocker;
};

#endif // LOGWRITER_H

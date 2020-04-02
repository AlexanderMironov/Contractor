#ifndef DBCONNECTION_H
#define DBCONNECTION_H
//
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QString>
//
class DBAcccessSafe;
class DbConnectionManager;
class LogWriter;
//

class DBConnection
{
public:
    enum ConnectionStatus{CONN_UNKNOWN, CONN_FAIL, CONN_SUCCESS, IN_USE};

    explicit DBConnection(const QString &str_conn_name,
                          const QString &str_db_type,
                          const QString &str_host,
                          const QString &str_db_name,
                          const QString &str_db_user,
                          const QString &str_db_pwd,
                          int i_port);
    ~DBConnection(){}
    //
    bool                isConnOK() const;
    ConnectionStatus    getStatus() const; //   {return m_enStatus;}

private:
    //do not allow to copy it
    DBConnection (DBConnection const&);
    void operator=(DBConnection const&);
    //---------------------------------------
    QSqlDatabase *get();
    //---------------------------------------
    //initial connection to the database makes here
    ConnectionStatus    init(const QString &str_db_type,
                             const QString &str_host,
                             const QString &str_db_name,
                             const QString &str_db_user,
                             const QString &str_db_pwd,
                             int   i_port);
    void                setStatus(ConnectionStatus e_status);
    bool                adjustSqliteDB();
    void                log(const QString& str_message) const;
    void                lock();
    void                release();
private: //members
    //
    QSqlDatabase            m_DB;
    //
    QString                 m_strConnName;
    ConnectionStatus        m_enStatus;
    mutable LogWriter*      m_ptrLog;
    //
    friend class DBAcccessSafe;
    friend class DbConnectionManager;
};

#endif // DBCONNECTION_H

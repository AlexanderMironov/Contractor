#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

/*
class manages pool of connections
*/
#include <QObject>
#include <QVector>
//
#include "dbconnection.h"


class DBAcccessSafe; //forward declaration
//
//
class DbConnectionManager : public QObject
{
    Q_OBJECT
public:
    ~DbConnectionManager ();
    //
    static DbConnectionManager&     getInstance     ();
    bool                            init(int i_required_conn_num,
                                         const QString &str_db_type,
                                         const QString &str_host,
                                         const QString &str_db_name,
                                         const QString &str_db_user,
                                         const QString &str_db_pwd,
                                         int i_port);
    //const QString&              getHostName     () const;
    //const QString&              getDBName       () const;
    //int                         getConnNumber   () const;
    //
signals:
    void takeConn       ();
    void releaseConn    ();

public slots:



private: //functions
    DBConnection*   getConnection       (int& id); //& - because we need to know what to unlock
    void            releaseConnection   (int id); //lock makes int
    void            shutdown();
    //
    explicit DbConnectionManager(QObject *parent = nullptr);
             DbConnectionManager (DbConnectionManager const&);
    void operator=(DbConnectionManager const&);
    //
    QVector<DBConnection*> m_ConnectionPool;
    friend class DBAcccessSafe;
};

#endif // CONNECTIONMANAGER_H

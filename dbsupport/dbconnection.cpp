#include <QtSql>
#include <QtDebug>
//
#include "dbconnection.h"
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
#include "config/configdef.h"
//
DBConnection::DBConnection(const QString &str_conn_name,
                           const QString& str_db_type,
                           const QString& str_host,
                           const QString& str_db_name,
                           const QString& str_db_user,
                           const QString& str_db_pwd,
                           int   i_port)
{
    setStatus(CONN_UNKNOWN);
    m_strConnName = str_conn_name;
    m_ptrLog = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    init(str_db_type, str_host, str_db_name, str_db_user, str_db_pwd, i_port);

}

DBConnection::ConnectionStatus DBConnection::init(const QString& str_db_type,
                                                  const QString& str_host,
                                                  const QString& str_db_name,
                                                  const QString& str_db_user,
                                                  const QString& str_db_pwd,
                                                  int   i_port)
{

        m_DB = QSqlDatabase::addDatabase ( str_db_type, m_strConnName );//( "QOCI", "main");  // my ORACLE or MySQL Server
        m_DB.setHostName    ( str_host      ); //localhost   "192.168.178.3"
        m_DB.setDatabaseName( str_db_name   ); //the name of my database
        m_DB.setUserName    ( str_db_user   ); // the name of my database user
        m_DB.setPassword    ( str_db_pwd    ); //the password of my database user. DO NOT use ONLY from notebook
        m_DB.setPort        ( i_port        );
        //
        if ( !m_DB.open() )
        {
            QSqlError err = m_DB.lastError();
            QString str_msg = err.text();
            //
            str_msg += "\nConnection params:";
            str_msg += "\nDatabase type: ";
            str_msg += str_db_type;
            str_msg += "\nHost name: ";
            str_msg += str_host;
            str_msg += "\nUser: ";
            str_msg += str_db_user;
            str_msg += "\nPassword: ";
            str_msg += str_db_pwd;
            str_msg += "\nPort N: ";
            str_msg += QString::number(i_port);
            str_msg += "\n";
            //
            const QString str_msg_log = QString("Can not establish connection to database, reason: [%1]").arg(str_msg);
            log(str_msg_log);
            setStatus (CONN_FAIL);
        }else //if opened
        {
            bool b_res = true;
            //
            if (str_db_type.compare("QSQLITE", Qt::CaseInsensitive) == 0 )
            {
                b_res = adjustSqliteDB();
            };
            if (b_res){
                setStatus (CONN_SUCCESS);
            }else{
                const QString str_msg_log = QString("Can not adjust connection to SQL Lite");
                log(str_msg_log);
                setStatus (CONN_FAIL);
            };
        };
    //
    return getStatus();
}

bool DBConnection::adjustSqliteDB()
{
    QSqlQuery qry(m_DB);
    //
    bool b_res = qry.exec("PRAGMA foreign_keys = ON;");
    return b_res;
}

QSqlDatabase* DBConnection::get()
{
    return &m_DB;
}

void DBConnection::setStatus(ConnectionStatus e_status)
{
    m_enStatus = e_status;
}

DBConnection::ConnectionStatus DBConnection::getStatus() const
{
    ConnectionStatus status = m_enStatus;
    return status;
}

bool DBConnection::isConnOK() const{
    if ((this->getStatus() == CONN_SUCCESS) ||(this->getStatus() == IN_USE)){
        return true;
    };
    //
    return false;
}

void DBConnection::lock(){
    setStatus(IN_USE);
}

void DBConnection::release(){
    setStatus(CONN_SUCCESS);
}

void DBConnection::log(const QString& str_message) const{
    if (nullptr != m_ptrLog){
        (*m_ptrLog)<<str_message<<"\n";
    };
}

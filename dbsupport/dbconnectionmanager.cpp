//
/*
 This file is part of project pdb.

    pdb is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    pdb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pdb.  If not, see <http://www.gnu.org/licenses/>.
*/
//
#include "dbconnectionmanager.h"
//
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSettings>
//
#include "dbsupport/dbacccesssafe.h"

DbConnectionManager::DbConnectionManager(QObject *parent) :
    QObject(parent)
{
    return;
}

DbConnectionManager::~DbConnectionManager()
{
    shutdown();
}

void DbConnectionManager::shutdown()
{
    for (int i = 0; i < m_ConnectionPool.size(); i++)
    {
        DBConnection* ptr_conn = m_ConnectionPool[i];
        ptr_conn->get()->close();
        //
        delete ptr_conn;
    };
}

DbConnectionManager& DbConnectionManager::getInstance()
{
    static DbConnectionManager instance;
    return instance;
}

DBConnection*   DbConnectionManager::getConnection (int& id)
{
    DBConnection* ptr_conn = nullptr;
    for (int i = 0; i < m_ConnectionPool.size(); ++i){
        ptr_conn = m_ConnectionPool[i];
        if ( ptr_conn->getStatus() == DBConnection::CONN_SUCCESS){
            ptr_conn->lock();
            id = i;
            break;
        };
    };
   return ptr_conn;
}

void DbConnectionManager::releaseConnection (int id)
{
    DBConnection* ptr_conn = m_ConnectionPool[id];
    ptr_conn->release();
    emit releaseConn();
}

bool DbConnectionManager::init(int i_required_conn_num,
                               const QString &str_db_type,
                               const QString &str_host,
                               const QString &str_db_name,
                               const QString &str_db_user,
                               const QString &str_db_pwd,
                               int i_port)
{
    if (m_ConnectionPool.size() > 0){
        return true; //already initialized
    };
    //
    bool b_ret = false;
    for (int i = 0; i < i_required_conn_num; i++)
    {
        DBConnection* ptr_conn = new DBConnection(QString::number(i),str_db_type,str_host,str_db_name,str_db_user,str_db_pwd,i_port);
        if (ptr_conn->isConnOK() == true){
            m_ConnectionPool.push_back(ptr_conn);
            b_ret = true;
        };
    };
    //
    return b_ret;
}

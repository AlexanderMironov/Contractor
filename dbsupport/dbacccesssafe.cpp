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
#include "dbacccesssafe.h"
#include "dbconnectionmanager.h"
//

DBAcccessSafe::DBAcccessSafe()
{
    m_iDBID = 0;
};

DBAcccessSafe::~DBAcccessSafe()
{
    DbConnectionManager& manager = DbConnectionManager::getInstance();
    manager.releaseConnection(m_iDBID);
};
//
QSqlDatabase* DBAcccessSafe::getDB()
{
    QSqlDatabase* ret_value =  nullptr;
    DbConnectionManager& manager = DbConnectionManager::getInstance();
    DBConnection* conn = manager.getConnection(m_iDBID);
    if (nullptr != conn){
        ret_value =  conn->get();
    };
    //
    return ret_value;
};

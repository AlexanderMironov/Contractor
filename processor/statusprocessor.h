#ifndef StatusProcessor_H
#define StatusProcessor_H

#include <QObject>
#include <QMap>
#include <QString>
//
class StatusDTO;
/*
id -> name
*/

typedef QMap<int, StatusDTO*> StatusStorage;

class StatusProcessor : public QObject
{
    Q_OBJECT
public:
        static StatusProcessor&     getInstance();
        bool                        init();
        int                         add(const QString& str_status_name);
        const StatusStorage&        getStorage() const;
        const QString               getStatusNameByID(int i_id);
signals:

public slots:


private:
    explicit        StatusProcessor(QObject *parent = nullptr);
    bool            readAllFromDB();
    int             insertIntoDB(const QString& str_status_name);
    void            addNewValueToStorage(int id, const QString& str_name);

private:
    StatusStorage   m_mapStorage;
};

#endif // StatusProcessor_H

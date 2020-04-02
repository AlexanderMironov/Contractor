#ifndef StatusProcessor_H
#define StatusProcessor_H

#include <QObject>
#include <QMap>
#include <QString>
//
class LogWriter;
class StatusDTO;
/*
id -> name
*/
typedef QMap<int, StatusDTO*> StatusStorage;
//
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
    explicit                StatusProcessor(QObject *parent = nullptr);
    bool                    readAllFromDB();
    void                    log(const QString& str_message) const;
    int                     insertIntoDB(const QString& str_status_name);
    void                    addNewValueToStorage(int id, const QString& str_name);

private:
    StatusStorage           m_mapStorage;
    mutable LogWriter*      m_ptrLog;
};

#endif // StatusProcessor_H

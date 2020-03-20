#ifndef TownProcessor_H
#define TownProcessor_H

#include <QObject>
#include <QMap>
#include <QString>
//
class TownDTO;
/*
id -> name
*/

typedef QMap<int, TownDTO*> TownStorage;

class TownProcessor : public QObject
{
    Q_OBJECT
public:
        static TownProcessor&       getInstance();
        bool                        init();
        int                         add(const QString& str_country_name);
        QString                     getTownNameByID(int i_id) const;
        const TownStorage&          getStorage() const;
signals:

public slots:


private:
    explicit        TownProcessor(QObject *parent = nullptr);
    bool            readAllFromDB();
    int             insertIntoDB(const QString& str_country_name);
    void            addNewValueToStorage(int id, const QString& str_name);

private:
    TownStorage     m_mapStorage;
};

#endif // TownProcessor_H

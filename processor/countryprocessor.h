#ifndef COUNTRYPROCESSOR_H
#define COUNTRYPROCESSOR_H

#include <QObject>
#include <QMap>
#include <QString>
//
class CountryDTO;
/*
id -> name
*/

typedef QMap<int, CountryDTO*> CountryStorage;

class CountryProcessor : public QObject
{
    Q_OBJECT
public:
        static CountryProcessor&    getInstance();
        bool                        init();
        int                         add(const QString& str_country_name);
        QString                     getCountryNameByID(int id);
        const CountryStorage&       getStorage();
        //returns VALUE_UNDEFINED id does not exists, or returns country ID if exists
        int                         isCountryAlreadyExists(const QString& str_country_name);
signals:

public slots:


private:
    explicit        CountryProcessor(QObject *parent = nullptr);
    bool            readAllFromDB();
    int             insertIntoDB(const QString& str_country_name);
    void            addNewValueToStorage(int id, const QString& str_name);

private:
    CountryStorage  m_mapStorage;
};

#endif // COUNTRYPROCESSOR_H

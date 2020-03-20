#ifndef AGENCYPROCESSOR_H
#define AGENCYPROCESSOR_H

#include <QObject>
#include <QMap>
#include <QString>
//
class AgencyDTO;
//
//agencyId->AgencyDTO*
//
typedef QMap<int, AgencyDTO*> AgencyStorage;

class AgentBaseDTO;

class AgencyProcessor : public QObject
{
    Q_OBJECT
public:
    static AgencyProcessor&     getInstance();
    int                         add(const QString& str_agency_name);
    bool                        init();
    QString                     getAgencyNameByID(int i_id);
    const AgencyStorage&        getStorage() const;

signals:

public slots:

private:
    explicit                    AgencyProcessor(QObject *parent = nullptr);
    int                         insertIntoDB(const QString& str_agency_name);
    bool                        readAllFromDB();
    void                        addNewValueToStorage(int id, const QString& str_name, const QString& str_description);

private:
    AgencyStorage               m_mapStorage;

};

#endif // AGENCYPROCESSOR_H

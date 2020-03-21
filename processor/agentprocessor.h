#ifndef AGENTPROCESSOR_H
#define AGENTPROCESSOR_H

#include <QObject>
#include <QMap>
#include <QString>
//
class AgentBaseDTO;
/*
Email -> instance
*/
typedef QMap<QString, AgentBaseDTO*> AgentStorage;

class AgentProcessor : public QObject
{
    Q_OBJECT
public:
    static AgentProcessor&  getInstance();
    int                     add(AgentBaseDTO* ptr_agent_base_info_dto);
    bool                    init();
    AgentBaseDTO*           getAgentByID(int i_id) const;
    const AgentStorage&     getStorage() const;
    bool                    updateRank(int i_agent_id, int i_rank);
private:
    explicit                AgentProcessor(QObject *parent = nullptr);
    int                     insertIntoDB(AgentBaseDTO* ptr_agent_base_info_dto);
    bool                    readAllFromDB();
    void                    addNewValueToStorage(int id,
                                              const QString& str_name,
                                              const QString& str_email,
                                              const QString& str_phone1,
                                              const QString& str_phone2,
                                              const QString& str_description,
                                              int i_agency_id,
                                              int i_rank,
                                              const QString &str_web_profile);

signals:

public slots:

private:
    AgentStorage            m_mapStorage;
};

#endif // AGENTPROCESSOR_H

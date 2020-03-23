#ifndef OFFERBASEDTO_H
#define OFFERBASEDTO_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QDate>
//
#include "dto/skilldto.h"


class OfferBaseDTO
{
public:
    OfferBaseDTO();
    //
    int                 getId() const;
    void                setId(int i_id);
    //
    const QDate&        getCreationDate() const;
    void                setCreationDate(const QDate& creation_date);
    //
    const QString&      getDescription() const;
    void                setDescription(const QString& str_pos_description);
    //
    const QString&      getComments() const;
    void                setComments(const QString& str_pos_comments);

    //
    const QString&      getPositionTitle() const;
    void                setPositionTitle(const QString& str_pos_title);
    //
    int                 getCountryId() const;
    void                setCountryId(int i_country_id);
    //
    int                 getTownId() const;
    void                setTownId(int i_pos_town);
    //
    int                 getRate() const;
    void                setRate(int rate);
    //
    int                 getStatusId() const;
    void                setStatusId(int i_status);
    //
    int                 getAgentId() const;
    void                setAgentId(int i_agent_id);
    //
    int                 getAttractivity() const;
    void                setAttractivity(int i_attractivity);

private:
    int                 m_iId;
    QDate               m_dCreationDate;
    QString             m_strPositionTitle;
    QString             m_strDescription;
    QString             m_strComments;
    int                 m_iCountryId;
    int                 m_iTownId;
    int                 m_iRate;
    int                 m_iStatusId;
    int                 m_iAgentId;
    int                 m_iAttractivity;
};

#endif // OFFERBASEDTO_H

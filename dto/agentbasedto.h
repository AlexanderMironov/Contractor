#ifndef AGENTBASEDTO_H
#define AGENTBASEDTO_H

#include <QString>

class AgentBaseDTO
{
public:
    AgentBaseDTO();
    int             getId() const;
    void            setId(int i_id);
    //
    const QString&  getName() const;
    void            setName(const QString& str_name);
    //
    const QString&  getEMail() const;
    void            setEMail(const QString& str_email);
    //
    const QString&  getPhone1() const;
    void            setPhone1(const QString& str_phone_1);
    //
    const QString&  getPhone2() const;
    void            setPhone2(const QString& str_phone_2);
    //
    const QString&  getWebProfile() const;
    void            setWebProfile(const QString& str_web_profile);
    //
    const QString&  getDescription() const;
    void            setDescription(const QString& str_description);
    //
    int             getAgencyId() const;
    void            setAgencyId(int i_agency_id);
    //
    int             getRank() const;
    void            setRank(int i_rank);

private:

private:
    int         m_iId;
    QString     m_strName;
    QString     m_strEMail;
    QString     m_strPhone1;
    QString     m_strPhone2;
    QString     m_strWebProfile;
    QString     m_strDescription;
    int         m_iAgencyId;
    int         m_iRank;
};

#endif // AGENTBASEDTO_H

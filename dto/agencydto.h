#ifndef AGENCYDTO_H
#define AGENCYDTO_H

#include <QString>

class AgencyDTO
{
public:
    AgencyDTO();
    AgencyDTO (AgencyDTO const& val);

    int             getId() const;
    void            setId(int i_id);
    //
    const QString&  getName() const;
    void            setName(const QString& str_name);
    //
    const QString&  getDescription() const;
    void            setDescription(const QString& str_description);

private:
    int         m_iId;
    QString     m_strName;
    QString     m_strDescription;
};

#endif // AGENCYDTO_H

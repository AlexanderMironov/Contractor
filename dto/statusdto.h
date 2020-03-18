#ifndef STATUSDTO_H
#define STATUSDTO_H

#include <QString>

class StatusDTO
{
public:
    StatusDTO();

    int             getId() const;
    void            setId(int i_id);
    //
    const QString&  getName() const;
    void            setName(const QString& str_name);

private:
    int         m_iId;
    QString     m_strName;
};

#endif // STATUSDTO_H

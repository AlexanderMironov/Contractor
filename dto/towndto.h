#ifndef TownDTO_H
#define TownDTO_H

#include <QString>

class TownDTO
{
public:
    TownDTO();
    //
    int             getId() const;
    void            setId(int i_id);
    //
    const QString&  getName() const;
    void            setName(const QString& str_name);



private:
    int         m_iID;
    QString     m_strName;
};

#endif // TownDTO_H

#ifndef COUNTRYDTO_H
#define COUNTRYDTO_H

#include <QString>

class CountryDTO
{
public:
    CountryDTO();
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

#endif // COUNTRYDTO_H

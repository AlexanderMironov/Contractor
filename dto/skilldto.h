#ifndef SkillDTO_H
#define SkillDTO_H

#include <QString>
#include <QVector>
//
typedef QVector<int> SkillsList;
//
class SkillDTO
{
public:
    SkillDTO();
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

#endif // SkillDTO_H

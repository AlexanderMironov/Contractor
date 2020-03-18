#ifndef SkillProcessor_H
#define SkillProcessor_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QStringList>
//
#include "dto/skilldto.h"
/*
id -> name
*/

typedef QMap<int, SkillDTO*> SkillStorage;

class SkillProcessor : public QObject
{
    Q_OBJECT
public:
        static SkillProcessor&    getInstance();
        bool                        init();
        int                         add(const QString& str_skill_name);
        SkillsList                  add(const QStringList& str_list_skills);
        QString                     getSkillNameById(int id);

signals:

public slots:


private:
    explicit        SkillProcessor(QObject *parent = nullptr);
    bool            readAllFromDB();
    int             insertIntoDB(const QString& str_skill_name);
    void            addNewValueToStorage(int id, const QString& str_name);

private:
    SkillStorage    m_mapStorage;
};

#endif // Skill

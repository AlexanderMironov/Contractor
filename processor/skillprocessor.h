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
class LogWriter;
//
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
        const SkillStorage&         getStorage() const;

signals:

public slots:


private:
    explicit                SkillProcessor(QObject *parent = nullptr);
    bool                    readAllFromDB();
    int                     insertIntoDB(const QString& str_skill_name);
    void                    addNewValueToStorage(int id, const QString& str_name);
    void                    log(const QString& str_message) const;

private:
    SkillStorage            m_mapStorage;
    mutable LogWriter*      m_ptrLog;
};

#endif // Skill

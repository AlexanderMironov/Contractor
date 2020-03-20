#ifndef OFFERSCANER_H
#define OFFERSCANER_H

#include <QObject>
#include <QString>

class OfferScaner : public QObject
{
    Q_OBJECT
public:
    explicit            OfferScaner(QObject *parent = nullptr);
    void                parse(const QString& str_original_text);
    const QString&      getModifiedText() const;
    const QString&      getSkills() const;
    //
    int                 getAgentId() const;
    int                 getAgencyId() const;
    const QString&      getAgentName() const;
    const QString&      getAgentEmail() const;
    const QString&      getAgentPhone1() const;
    const QString&      getAgentPhone2() const;
    //
    const QString&      getAgencyName() const;
    const QString&      getTownName() const;
    //

signals:

public slots:

private:
    void                resetFields();
    void                removeEmptyStrings();
    void                generateSkillsList();
    void                generateAgentInfo();
    void                generateTownInfo();

private:

    QString m_strModifiedText;
    //
    QString m_strSkills;
    //
    QString                 m_strTown;
    //
    int                     m_iAgentId;
    int                     m_iAgencyId;
    QString                 m_strAgencyName;
    QString                 m_strAgentName;
    QString                 m_strAgentEmail;
    QString                 m_strAgentPhone1;
    QString                 m_strAgentPhone2;


};

#endif // OFFERSCANER_H

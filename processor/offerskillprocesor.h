#ifndef OFFERSKILLPROCESOR_H
#define OFFERSKILLPROCESOR_H

#include <QObject>
#include <QVector>
//
#include "dto/offerbasedto.h"
#include "dto/offerskilldto.h"

//
typedef  QVector<OfferSkillDTO*> OfferSkillStorage;
//


class OfferSkillProcesor : public QObject
{
    Q_OBJECT
public:
    static OfferSkillProcesor&  getInstance();
    bool                        init();
    void                        add(int i_offer_id, const SkillsList& skill_list);
    SkillsList                  getSkillsList(int i_offer_id);
    bool                        removeOffer(int i_offer_id);
signals:

public slots:

private:
    explicit        OfferSkillProcesor(QObject *parent = nullptr);
    bool            readAllFromDB();
    int             insertIntoDB(int i_offer_id, int i_skill_id);
    bool            isExist(int i_offer_id, int i_skill_id);
    void            addNewValueToStorage(int id, int i_offer_id, int i_skill_id);

private:
    OfferSkillStorage   m_vStorage;

};

#endif // OFFERSKILLPROCESOR_H

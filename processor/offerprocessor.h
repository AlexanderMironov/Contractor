#ifndef OFFERPROCESSOR_H
#define OFFERPROCESSOR_H

#include <QObject>
#include <QMap>
//
class OfferBaseDTO;
class LogWriter;
/*
id -> object
*/
typedef QMap<int, OfferBaseDTO*> OfferStorage;

class OfferProcessor : public QObject
{
    Q_OBJECT
public:
    static OfferProcessor&  getInstance();
    int                     add(OfferBaseDTO* pos_description);
    bool                    init();
    const OfferStorage&     getStorage() const;
    OfferBaseDTO*           getOfferById(int i_offer_id);
    bool                    updateOfferStatus(int i_offer_id, int i_offer_status);
    bool                    updateAttractivity(int i_offer_id, int i_offer_attractivity);
    bool                    updateRate(int i_offer_id, int i_rate);
    bool                    updateDescription(int i_offer_id, const QString& str_descripiton);
    bool                    updateComment(int i_offer_id, const QString& str_comment);
    bool                    updatePositionTitle(int i_offer_id, const QString& str_position_title);
    bool                    updateCountry(int i_offer_id, int i_country_id);
    bool                    updateTown(int i_offer_id, int i_town_id);
    bool                    removeOffer(int i_offer_id);

signals:

public slots:

private:
    explicit                OfferProcessor(QObject *parent = nullptr);
    bool                    readAllFromDB();
    void                    log(const QString& str_message) const;
    int                     insertIntoDB(OfferBaseDTO* pos_description);
    void                    addNewValueToStorage(int i_id,
                                              const QDate& d_creation_date,
                                              const QString& str_pos_title,
                                              const QString& str_pos_decription,
                                              const QString& str_pos_comments,
                                              int i_id_country,
                                              int i_id_town,
                                              int i_id_agent,
                                              int i_id_status,
                                              int i_attractivity,
                                              int i_rate);

private:
    OfferStorage            m_mapStorage;
    mutable LogWriter*      m_ptrLog;
};

#endif // OFFERPROCESSOR_H

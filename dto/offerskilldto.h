#ifndef OFFERSKILLDTO_H
#define OFFERSKILLDTO_H


class OfferSkillDTO
{
public:
    OfferSkillDTO();
    //
    int getId() const;
    void setId(int i_id);
    //
    int getOfferId() const;
    void setOfferId(int i_offer_id);
    //
    int getSkillId() const;
    void setSkillId(int i_skill_id);

private:
    int m_iID;
    int m_iOfferID;
    int m_iSkillID;
};

#endif // OFFERSKILLDTO_H

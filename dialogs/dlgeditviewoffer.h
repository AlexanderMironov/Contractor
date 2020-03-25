#ifndef DLGEDITVIEWOFFER_H
#define DLGEDITVIEWOFFER_H

#include <QDialog>
#include <QObject>
//
#include <QGridLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QAction>
//
class OfferBaseDTO;
class AgentBaseDTO;
//
class DlgEditViewOffer : public QDialog
{
    Q_OBJECT

public:
                    DlgEditViewOffer(QWidget *parent = nullptr);
                    ~DlgEditViewOffer();
    void            init(int i_offer_id);
    bool            isSomethingChanged() const;

signals:

public slots:

private slots:
    void            onClickBtnUpdateOffer();
    void            onChangeDescription();
    void            onChangeComment();
    void            onChangePositionTitle();
    void            onChangeCountry();
    void            onChangeTown();
    void            onChangeSkillsList();
    void            onChangeRate();
    void            onChangeStatus();
    void            onChangeAttractivity();

private:
    void            setDlgSizes();
    void            setElementSizes();
    void            setDlgLayout();
    void            setMenuAction();
    void            createWidgets();
    void            createOfferWidgets();
    void            createAgentWidgets();
    void            createControlButtons();
    void            addWidgetsToLayout();
    void            fillCountryCombo();
    void            fillSkillList();
    void            fillStatusCombo();
    void            fillAttractivityCombo();
    //
    void            updateDesctiption();
    void            updateComment();
    void            updatePositionTitle();
    void            updateCountry();
    void            updateTown();
    void            updateRate();
    void            updateSkillList();
    void            updateStatus();
    void            updateAttractivity();

private:
    int             m_iMinButtonWidth;
    int             m_iMinLabelWidth;
    int             m_iMinEditWidth;
    int             m_iMaxElementWidth;
    int             m_iMaxLabelHeight;
    //
    QGridLayout     m_MainLayout;
    //
    QLabel          m_LblnsertOffer;
    QPlainTextEdit  m_OfferEdit;
    QLabel          m_LblOfferInfo;
    //
    QLabel          m_LblOfferCore;
    QLineEdit       m_EditOfferCore;
    QPushButton     m_ButtonAcceptOfferCore;
    //
    QLabel          m_LblCountry;
    QComboBox       m_ComboCountry;
    //
    QLabel          m_LblTown;
    QLineEdit       m_EditTown;
    QPushButton     m_ButtonAcceptTown;
    //
    QLabel          m_LblSkills;
    QLineEdit       m_EditSkills;
    QPushButton     m_ButtonAcceptSkills;
    //
    QLabel          m_LblRate;
    QLineEdit       m_EditRate;
    //
    QLabel          m_LblStatus;
    QComboBox       m_ComboStatus;
    //
    QLabel          m_LblAttractivity;
    QComboBox       m_ComboAttractivity;
    //-------------------------------
    QSpacerItem*    m_ptrSpacer;
    QLabel          m_LblnsertComment;
    QPlainTextEdit  m_CommentEdit;
    QLabel          m_LblAgentInfo;
    //
    QLabel          m_LblAgentName;
    QLabel          m_LblAgentNameValue;
    //
    QLabel          m_LblAgentEmail;
    QLabel          m_LblAgentEmailValue;
    //
    QLabel          m_LblAgentPhone1;
    QLabel          m_LblAgentPhone1Value;
    //
    QLabel          m_LblAgentPhone2;
    QLabel          m_LblAgentPhone2Value;
    //
    QLabel          m_LblAgencyName;
    QLabel          m_LblAgencyNameValue;
    //
    QLabel          m_LblAgentRank;
    QLabel          m_LblAgentRankValue;
    //
    QPushButton     m_ButtonUpdateOffer;
    //
    QPushButton     m_ButtonClose;
    //
    QAction         m_actionAcceptOfferCore;
    QAction         m_actionAcceptCountry;
    QAction         m_actionAcceptTown;
    QAction         m_actionAcceptSkills;
    QAction         m_actionAcceptAgentName;
    QAction         m_actionAcceptAgentEmail;
    QAction         m_actionAcceptAgentPhone1;
    QAction         m_actionAcceptAgentPhone2;
    QAction         m_actionAcceptAgencyName;
    QAction         m_actionScan;
    QAction         m_actionPaste;
    //
    OfferBaseDTO*   m_ptrDtoOffer;
    AgentBaseDTO*   m_ptrDtoAgent;
    //
    bool            m_bOfferUpdated;
    //
    bool            m_bChangeDescription;
    bool            m_bChangeComment;
    bool            m_bChangePositionTitle;
    bool            m_bChangeCountry;
    bool            m_bChangeTown;
    bool            m_bChangeSkillsList;
    bool            m_bChangeRate;
    bool            m_bChangeStatus;
    bool            m_bChangeAttractivity;
};

#endif // DLGEDITVIEWOFFER_H

#ifndef DLGNEWOFFER_H
#define DLGNEWOFFER_H

#include <QDialog>
#include <QObject>
//
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QAction>
//
#include "dto/offerbasedto.h"
#include "dto/agentbasedto.h"
//

//
class DlgNewOffer : public QDialog
{
    Q_OBJECT

public:
    DlgNewOffer(QWidget *parent = nullptr);
    ~DlgNewOffer();

public slots:

private slots:
    void        onSelectText(bool b_selected);
    void        onRequestUserMenu();
    void        onClickBtnAcceptPositionDescription();
    void        onClickBtnAcceptCountry();
    void        onClickBtnAcceptTown();
    void        onClickBtnAcceptSkills();
    void        onClickBtnAcceptAgentName();
    void        onClickBtnAcceptAgentEmail();
    void        onClickBtnAcceptAgentPhone1();
    void        onClickBtnAcceptAgentPhone2();
    void        onClickBtnAcceptAgencyName();
    void        onClickBtnSaveOffer();
    void        onClickBtnScan();
signals:

private:
    void        setMenuAction();
    void        setDlgSizes();
    void        setElementSizes();
    void        setDlgLayout();
    void        createWidgets();
    void        createOfferWidgets();
    void        createAgentWidgets();
    void        createControlButtons();
    void        addWidgetsToLayout();
    QString     getSelectedPartOfOffer() const;

    void        saveAgentInfo();
    void        saveOffer();

private:
    int             m_iMinButtonWidth;
    int             m_iMinLabelWidth;
    int             m_iMinEditWidth;
    int             m_iMaxElementWidth;
    int             m_iMaxLabelHeight;
    //
    QGridLayout     m_MainLayout;
    //
    QPlainTextEdit  m_OfferEdit;
    QLabel          m_LblOfferInfo;
    //
    QLabel          m_LblOfferCore;
    QLineEdit       m_EditOfferCore;
    QPushButton     m_ButtonAcceptOfferCore;
    //
    QLabel          m_LblCountry;
    QLineEdit       m_EditCountry;
    QPushButton     m_ButtonAcceptCountry;
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
    QLabel          m_LblAgentInfo;
    //
    QLabel          m_LblAgentName;
    QLineEdit       m_EditAgentName;
    QPushButton     m_ButtonAcceptAgentName;
    //
    QLabel          m_LblAgentEmail;
    QLineEdit       m_EditAgentEmail;
    QPushButton     m_ButtonAcceptAgentEmail;
    //
    QLabel          m_LblAgentPhone1;
    QLineEdit       m_EditAgentPhone1;
    QPushButton     m_ButtonAcceptAgentPhone1;
    //
    QLabel          m_LblAgentPhone2;
    QLineEdit       m_EditAgentPhone2;
    QPushButton     m_ButtonAcceptAgentPhone2;
    //
    QLabel          m_LblAgencyName;
    QLineEdit       m_EditAgencyName;
    QPushButton     m_ButtonAcceptAgencyName;
    //
    QLabel          m_LblAgentRank;
    QComboBox       m_ComboAgentRank;
    //
    QPushButton     m_ButtonSaveOffer;
    //
    QPushButton     m_ButtonShowAgentInfo;
    //
    QPushButton     m_ButtonShareOffer;
    //
    QPushButton     m_ButtonScan;
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
    //
    OfferBaseDTO    m_dtoOffer;
    AgentBaseDTO    m_dtoAgent;
};


#endif // DLGNEWOFFER_H

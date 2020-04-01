#ifndef DLGNEWOFFER_H
#define DLGNEWOFFER_H

#include <QDialog>
#include <QObject>
//
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QAction>
#include <QCloseEvent>
#include <QSpacerItem>
//
#include "dto/offerbasedto.h"
#include "dto/agentbasedto.h"
//
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QPlainTextEdit;
class QGridLayout;
//
class DlgNewOffer : public QDialog
{
    Q_OBJECT

public:
    DlgNewOffer(QWidget *parent = nullptr);
    ~DlgNewOffer();
    void init();
    bool isbOfferSaved() const;
    bool isNewAgentAdded();

public slots:

private slots:
    void        onSelectText(bool b_selected);
    void        onRequestUserMenu();
    void        onClickBtnAcceptPositionTitle();
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

protected:
    void closeEvent (QCloseEvent *event);

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
    void        onAddNewCountry();
    void        detachElements();

    bool        saveAgentInfo();
    bool        saveOffer();
    void        clearFields();

private:
    int             m_iMinButtonWidth;
    int             m_iMinLabelWidth;
    int             m_iMinEditWidth;
    int             m_iMaxElementWidth;
    int             m_iMaxLabelHeight;
    //
    QGridLayout     m_MainLayout;
    //
    QLabel           m_LblnsertOffer;
    QPlainTextEdit   m_OfferEdit;
    QLabel           m_LblOfferInfo;
    //
    QLabel          m_LblPositonTitle;
    QLineEdit       m_EditPositonTitle;
    QPushButton     m_ButtonAcceptPositonTitle;
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
    QLineEdit      m_EditRate;
    //
    QLabel          m_LblStatus;
    QComboBox       m_ComboStatus;
    //
    QLabel          m_LblAttractivity;
    QComboBox       m_ComboAttractivity;
    //-------------------------------
    QSpacerItem     m_Spacer;
    QLabel          m_LblnsertComment;
    QPlainTextEdit  m_CommentEdit;
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
    QPushButton     m_ButtonScan;
    //
    QPushButton     m_ButtonSaveOffer;
    //
    QPushButton     m_ButtonClose;
    //
    QLineEdit       m_EditStatusBar;
    //
    QAction         m_actionAcceptOfferCore;
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
    OfferBaseDTO    m_dtoOffer;
    AgentBaseDTO    m_dtoAgent;
    //
    bool            m_bOfferSaved;
    bool            m_bAgentAdded;
};

#endif // DLGNEWOFFER_H

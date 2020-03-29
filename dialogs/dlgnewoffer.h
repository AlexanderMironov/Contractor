#ifndef DLGNEWOFFER_H
#define DLGNEWOFFER_H

#include <QDialog>
#include <QObject>
//

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
    void        onAddNewCountry();


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
    QGridLayout*    m_ptrMainLayout;
    //
    QLabel*          m_ptrLblnsertOffer;
    QPlainTextEdit*  m_ptrOfferEdit;
    QLabel*          m_ptrLblOfferInfo;
    //
    QLabel*         m_ptrLblPositonTitle;
    QLineEdit*      m_ptrEditPositonTitle;
    QPushButton*    m_ptrButtonAcceptPositonTitle;
    //
    QLabel*         m_ptrLblCountry;
    QComboBox*      m_ptrComboCountry;
    //
    QLabel*         m_ptrLblTown;
    QLineEdit*      m_ptrEditTown;
    QPushButton*    m_ptrButtonAcceptTown;
    //
    QLabel*         m_ptrLblSkills;
    QLineEdit*      m_ptrEditSkills;
    QPushButton*    m_ptrButtonAcceptSkills;
    //
    QLabel*         m_ptrLblRate;
    QLineEdit*      m_ptrEditRate;
    //
    QLabel*         m_ptrLblStatus;
    QComboBox*      m_ptrComboStatus;
    //
    QLabel*         m_ptrLblAttractivity;
    QComboBox*      m_ptrComboAttractivity;
    //-------------------------------
    QSpacerItem*    m_ptrSpacer;
    QLabel*         m_ptrLblnsertComment;
    QPlainTextEdit* m_ptrCommentEdit;
    QLabel*         m_ptrLblAgentInfo;
    //
    QLabel*         m_ptrLblAgentName;
    QLineEdit*      m_ptrEditAgentName;
    QPushButton*    m_ptrButtonAcceptAgentName;
    //
    QLabel*         m_ptrLblAgentEmail;
    QLineEdit*      m_ptrEditAgentEmail;
    QPushButton*    m_ptrButtonAcceptAgentEmail;
    //
    QLabel*         m_ptrLblAgentPhone1;
    QLineEdit*      m_ptrEditAgentPhone1;
    QPushButton*    m_ptrButtonAcceptAgentPhone1;
    //
    QLabel*         m_ptrLblAgentPhone2;
    QLineEdit*      m_ptrEditAgentPhone2;
    QPushButton*    m_ptrButtonAcceptAgentPhone2;
    //
    QLabel*         m_ptrLblAgencyName;
    QLineEdit*      m_ptrEditAgencyName;
    QPushButton*    m_ptrButtonAcceptAgencyName;
    //
    QLabel*         m_ptrLblAgentRank;
    QComboBox*      m_ptrComboAgentRank;
    //
    QPushButton*    m_ptrButtonScan;
    //
    QPushButton*    m_ptrButtonSaveOffer;
    //
    QPushButton*    m_ptrButtonClose;
    //
    QLineEdit*      m_ptrEditStatusBar;
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

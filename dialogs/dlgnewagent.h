#ifndef DLGNEWAGENT_H
#define DLGNEWAGENT_H

#include <QDialog>
#include <QObject>
//
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
/*
class   QGridLayout;
class   QLabel;
class   QPlainTextEdit;
class   QLineEdit;
class   QComboBox;
class   QPushButton;
*/


class DlgNewAgent : public QDialog
{
    Q_OBJECT

public:
    DlgNewAgent();
    ~DlgNewAgent();
    void init (int i_agent_id = -1);
    bool isSomethingChanged() const;
    int  getAgentId() const;
    bool  isNameOrDescriptionChanged() const;

public slots:

private slots:
    void onChangeDescription();
    void onChangeName();
    void onChangeEmail();
    void onChangePhone1();
    void onChangePhone2();
    void onChangeWebProfile();
    void onClickBtnUpdateSaveOffer();
    void onRankChanged(int);
    void onClickBtnCheckEmail();

signals:

private:
    void    setInitialFlags();
    void    setDlgSizes();
    void    setDlgLayout();
    void    createGraficElements();
    void    fillInitialData();
    void    addWidgetsToLayout();
    void    detachElements();
    void    saveAgent();
    int     saveAgency(const QString& str_agency_name);
    void    updateAgent();
    bool    isPossibleToSaveOrUpdate(QString &str_message) const;
    void    whenSomethingChanged();

protected:
    void closeEvent (QCloseEvent *event);

private:
    int             m_iAgentId;
    //
    int             m_iMinLabelWidth;
    int             m_iMaxElementWidth;
    int             m_iMaxLabelHeight;
    int             m_iMinEditWidth;
    int             m_iMinButtonWidth;
    int             m_iMinButtonHeight;
    //
    QGridLayout      m_MainLayout;
    //
    QLabel           m_LblDescription;
    QPlainTextEdit   m_EditDescription;
    //
    QLabel           m_LblName;
    QLineEdit        m_EditName;
    //
    QLabel           m_LblEmail;
    QLineEdit        m_EditEmail;
    //
    QLabel           m_LblPhone1;
    QLineEdit        m_EditPhone1;
    //
    QLabel           m_LblPhone2;
    QLineEdit        m_EditPhone2;
    //
    QLabel           m_LblWebProfile;
    QLineEdit        m_EditWebProfile;
    //
    QLabel           m_LblAgency;
    QLineEdit        m_EditAgency;
    //
    QLabel           m_LblRank;
    QComboBox        m_comboRank;
    //
    QPushButton      m_ButtonCheckEmail;
    QPushButton      m_ButtonUpdateSaveOffer;
    QPushButton      m_ButtonClose;
    //
    QLineEdit        m_EditStatusBar;
    //
    bool            m_bFillModeOn;
    //
    bool            m_bDataChanged;
    bool            m_bDescriptionChanged;
    bool            m_bNameChanged;
    bool            m_bEmailChanged;
    bool            m_bPhone1Changed;
    bool            m_bPhone2Changed;
    bool            m_bWebProfileChanged;
    bool            m_bRankChanged;

};

#endif // DLGNEWAGENT_H

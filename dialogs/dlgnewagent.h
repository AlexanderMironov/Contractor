#ifndef DLGNEWAGENT_H
#define DLGNEWAGENT_H

#include <QDialog>
#include <QObject>
//
class   QGridLayout;
class   QLabel;
class   QPlainTextEdit;
class   QLineEdit;
class   QComboBox;
class   QPushButton;


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
    //
    QGridLayout*     m_ptrMainLayout;
    //
    QLabel*          m_ptrLblDescription;
    QPlainTextEdit*  m_ptrEditDescription;
    //
    QLabel*          m_ptrLblName;
    QLineEdit*       m_ptrEditName;
    //
    QLabel*          m_ptrLblEmail;
    QLineEdit*       m_ptrEditEmail;
    //
    QLabel*          m_ptrLblPhone1;
    QLineEdit*       m_ptrEditPhone1;
    //
    QLabel*          m_ptrLblPhone2;
    QLineEdit*       m_ptrEditPhone2;
    //
    QLabel*          m_ptrLblWebProfile;
    QLineEdit*       m_ptrEditWebProfile;
    //
    QLabel*          m_ptrLblAgency;
    QLineEdit*       m_ptrEditAgency;
    //
    QLabel*          m_ptrLblRank;
    QComboBox*       m_ptrcomboRank;
    //
    QPushButton*     m_ptrButtonCheckEmail;
    QPushButton*     m_ptrButtonUpdateSaveOffer;
    QPushButton*     m_ptrButtonClose;
    //
    QLineEdit*       m_ptrEditStatusBar;
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

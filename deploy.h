#ifndef DEPLOY_H
#define DEPLOY_H

#include "infomodel.h"

#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTableView>
#include <QPlainTextEdit>

class Deploy : public QFrame
{
    Q_OBJECT

public:
    explicit Deploy(QWidget *parent = 0);
    ~Deploy();

private slots:
    void chooseConfigFile();
    void confirmSelectedList();
    void showInfoView();
    void startDeploy();

private:
    QLineEdit *m_filePathEdit;
    QPushButton *m_fileChooseBtn;
    QPushButton *m_nextStepBtn;
    QPushButton *m_prevStepBtn;
    QPushButton *m_deployBtn;
    QPushButton *m_exitBtn;
    QTableView *m_infoView;
    InfoModel *m_infoModel;
    QPlainTextEdit *m_deployDetail;
};

#endif // DEPLOY_H

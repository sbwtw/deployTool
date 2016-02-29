#ifndef DEPLOY_H
#define DEPLOY_H

#include "infomodel.h"
#include "categoryinfomodel.h"

#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QTableView>
#include <QLabel>
#include <QPlainTextEdit>

class Deploy : public QFrame
{
    Q_OBJECT

public:
    explicit Deploy(QWidget *parent = 0);
    ~Deploy();

private slots:
    void confirmSelectedList();
    void showInfoView();
    void startDeploy();
    void readFile();

private:
    QTableView *m_infoView1;
    QTableView *m_infoView2;
    QTableView *m_infoView3;
    QTableView *m_infoView4;
    CategoryInfoModel *m_cateModel1;
    CategoryInfoModel *m_cateModel2;
    CategoryInfoModel *m_cateModel3;
    CategoryInfoModel *m_cateModel4;
    QLabel *m_label1;
    QLabel *m_label2;
    QLabel *m_label3;
    QLabel *m_label4;
    QPushButton *m_nextStepBtn;
    QPushButton *m_prevStepBtn;
    QPushButton *m_deployBtn;
    QPushButton *m_exitBtn;
    QPlainTextEdit *m_deployDetail;
};

#endif // DEPLOY_H

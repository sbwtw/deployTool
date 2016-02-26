#include "deploy.h"

#include <QApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QHeaderView>
#include <QProcess>

Deploy::Deploy(QWidget *parent) :
    QFrame(parent)
{
    m_infoModel = new InfoModel;
    m_fileChooseBtn = new QPushButton(tr("选择"));
    m_prevStepBtn = new QPushButton(tr("上一步"));
    m_nextStepBtn = new QPushButton(tr("下一步"));
    m_deployBtn = new QPushButton(tr("部署"));
    m_exitBtn = new QPushButton(tr("退出"));
    m_exitBtn->hide();
    m_filePathEdit = new QLineEdit;
    m_filePathEdit->setReadOnly(true);
    m_infoView = new QTableView;
    m_infoView->setModel(m_infoModel);
    m_infoView->verticalHeader()->hide();
    m_infoView->setSortingEnabled(true);
    m_infoView->setSelectionMode(QAbstractItemView::NoSelection);
    m_deployDetail = new QPlainTextEdit;
    m_deployDetail->setReadOnly(true);

    QHBoxLayout *fileChooseLayout = new QHBoxLayout;
    fileChooseLayout->addWidget(m_filePathEdit);
    fileChooseLayout->addWidget(m_fileChooseBtn);

    QHBoxLayout *toolBarLayout = new QHBoxLayout;
    toolBarLayout->addStretch();
    toolBarLayout->addWidget(m_nextStepBtn);
    toolBarLayout->addWidget(m_prevStepBtn);
    toolBarLayout->addWidget(m_deployBtn);
    toolBarLayout->addWidget(m_exitBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fileChooseLayout);
    mainLayout->addWidget(m_infoView);
    mainLayout->addWidget(m_deployDetail);
    mainLayout->addLayout(toolBarLayout);

    setLayout(mainLayout);
    setFixedSize(600, 400);
    move(qApp->primaryScreen()->geometry().center() - rect().center());

    connect(m_exitBtn, &QPushButton::clicked, qApp, &QApplication::exit);
    connect(m_deployBtn, &QPushButton::clicked, this, &Deploy::startDeploy);
    connect(m_prevStepBtn, &QPushButton::clicked, this, &Deploy::showInfoView);
    connect(m_nextStepBtn, &QPushButton::clicked, this, &Deploy::confirmSelectedList);
    connect(m_fileChooseBtn, &QPushButton::clicked, this, &Deploy::chooseConfigFile);
    connect(m_infoView, &QTableView::clicked, [this] (const QModelIndex &index) {
        m_infoModel->selectByIndex(index);
    });

    showInfoView();

#ifdef QT_DEBUG
    m_infoModel->readInfoFile("/home/test.csv");
#endif
}

Deploy::~Deploy()
{
}

void Deploy::chooseConfigFile()
{
    QFileDialog chooser;
    chooser.setMimeTypeFilters(QStringList() << "text/csv");
    if (!chooser.exec())
        return;

    if (chooser.selectedFiles().isEmpty())
        return;

    const QString file = chooser.selectedFiles().first();
    m_filePathEdit->setText(file);
    m_infoModel->readInfoFile(file);
}

void Deploy::confirmSelectedList()
{
    QString result = "以下为安装列表: \n";
    const QList<QStringList> &infoList = m_infoModel->selectedList();

    if (infoList.isEmpty())
        return;

    for (const QStringList info : infoList)
    {
        if (info[1].isEmpty())
            continue;

        result += QString(tr("厂商: %1, 软件包: %2, 类型: %3\n")).arg(info[0])
                                                                .arg(info[1])
                                                                .arg(info[3]);
    }

    m_deployDetail->clear();
    m_deployDetail->appendPlainText(result);
    m_deployDetail->show();
    m_infoView->hide();
    m_nextStepBtn->hide();
    m_deployBtn->show();
    m_prevStepBtn->show();
    m_deployBtn->setText(tr("部署"));
}

void Deploy::showInfoView()
{
    m_infoView->show();
    m_nextStepBtn->show();
    m_deployDetail->hide();
    m_prevStepBtn->hide();
    m_deployBtn->hide();
}

void Deploy::startDeploy()
{
    m_deployDetail->appendPlainText("开始部署...\n");

    QDir dir(m_filePathEdit->text());
    dir.cdUp();

    QStringList fileList;

    const QList<QStringList> &infoList = m_infoModel->selectedList();
    for (const QStringList info : infoList)
    {
        qDebug() << "deploy: " << dir.absoluteFilePath(info[1]);
        fileList << dir.absoluteFilePath(info[1]);
    }

    QStringList args;
    args << "--user" << "root" << "--" << "dpkg" << "-i" << fileList;

    qDebug() << "args: " << args;

    QProcess *process = new QProcess;
    connect(process, &QProcess::readyReadStandardOutput, [process, this] {
        m_deployDetail->appendPlainText(process->readAllStandardOutput());
    });
    connect(process, static_cast<void (QProcess::*)(int)>(&QProcess::finished), [process, this] (int ret) {

        if (!ret) {
            m_deployDetail->appendPlainText("部署成功");
            m_exitBtn->show();
            m_deployBtn->hide();
            m_prevStepBtn->hide();
        } else {
            m_deployDetail->appendPlainText("部署失败:");
            m_deployDetail->appendPlainText(process->readAllStandardError());
            m_deployBtn->setText(tr("重新部署"));
        }

        process->deleteLater();
    });

    process->start("gksu", args);
}

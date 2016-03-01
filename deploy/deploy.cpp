
#include <gtk/gtk.h>

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
    m_prevStepBtn = new QPushButton(tr("上一步"));
    m_nextStepBtn = new QPushButton(tr("下一步"));
    m_deployBtn = new QPushButton(tr("部署"));
    m_exitBtn = new QPushButton(tr("退出"));
    m_exitBtn->hide();
    m_deployDetail = new QPlainTextEdit;
    m_deployDetail->setReadOnly(true);

    m_label1 = new QLabel(tr("投影仪"));
    m_cateModel1 = new CategoryInfoModel;
    m_infoView1 = new QTableView;
    m_infoView1->setModel(m_cateModel1);
    QVBoxLayout *viewLayout1 = new QVBoxLayout;
    viewLayout1->addWidget(m_label1);
    viewLayout1->addWidget(m_infoView1);

    m_label2 = new QLabel(tr("电子白板"));
    m_cateModel2 = new CategoryInfoModel;
    m_infoView2 = new QTableView;
    m_infoView2->setModel(m_cateModel2);
    QVBoxLayout *viewLayout2 = new QVBoxLayout;
    viewLayout2->addWidget(m_label2);
    viewLayout2->addWidget(m_infoView2);

    m_label3 = new QLabel(tr("实物展台"));
    m_cateModel3 = new CategoryInfoModel;
    m_infoView3 = new QTableView;
    m_infoView3->setModel(m_cateModel3);
    QVBoxLayout *viewLayout3 = new QVBoxLayout;
    viewLayout3->addWidget(m_label3);
    viewLayout3->addWidget(m_infoView3);

    m_label4 = new QLabel(tr("互动触控显示屏"));
    m_cateModel4 = new CategoryInfoModel;
    m_infoView4 = new QTableView;
    m_infoView4->setModel(m_cateModel4);
    QVBoxLayout *viewLayout4 = new QVBoxLayout;
    viewLayout4->addWidget(m_label4);
    viewLayout4->addWidget(m_infoView4);

    QHBoxLayout *viewsLayout = new QHBoxLayout;
    viewsLayout->addLayout(viewLayout1);
    viewsLayout->addLayout(viewLayout2);
    viewsLayout->addLayout(viewLayout3);
    viewsLayout->addLayout(viewLayout4);

    QHBoxLayout *toolBarLayout = new QHBoxLayout;
    toolBarLayout->addStretch();
    toolBarLayout->addWidget(m_nextStepBtn);
    toolBarLayout->addWidget(m_prevStepBtn);
    toolBarLayout->addWidget(m_deployBtn);
    toolBarLayout->addWidget(m_exitBtn);

    m_fileLineEdit = new QLineEdit;
    m_fileLineEdit->setReadOnly(true);
    m_fileChooseBtn = new QPushButton(tr("浏览"));

    QHBoxLayout *fileChooseLayout = new QHBoxLayout;
    fileChooseLayout->addWidget(m_fileLineEdit);
    fileChooseLayout->addWidget(m_fileChooseBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fileChooseLayout);
    mainLayout->addLayout(viewsLayout);
    mainLayout->addWidget(m_deployDetail);
    mainLayout->addLayout(toolBarLayout);

    setLayout(mainLayout);
    setMinimumSize(1000, 400);
    move(qApp->primaryScreen()->geometry().center() - rect().center());

    connect(m_infoView1, &QTableView::clicked, m_cateModel1, &CategoryInfoModel::toggleByIndex);
    connect(m_infoView2, &QTableView::clicked, m_cateModel2, &CategoryInfoModel::toggleByIndex);
    connect(m_infoView3, &QTableView::clicked, m_cateModel3, &CategoryInfoModel::toggleByIndex);
    connect(m_infoView4, &QTableView::clicked, m_cateModel4, &CategoryInfoModel::toggleByIndex);
    connect(m_exitBtn, &QPushButton::clicked, qApp, &QApplication::exit);
    connect(m_deployBtn, &QPushButton::clicked, this, &Deploy::startDeploy);
    connect(m_prevStepBtn, &QPushButton::clicked, this, &Deploy::showInfoView);
    connect(m_nextStepBtn, &QPushButton::clicked, this, &Deploy::confirmSelectedList);
    connect(m_fileChooseBtn, &QPushButton::clicked, this, &Deploy::chooseFile);

    showInfoView();
//    readFile();

    gtk_init(nullptr, nullptr);
}

Deploy::~Deploy()
{
}

void Deploy::confirmSelectedList()
{
    QString result = "以下为安装列表: \n";
    QList<QStringList> infoList;
    infoList.append(m_cateModel1->selectedList());
    infoList.append(m_cateModel2->selectedList());
    infoList.append(m_cateModel3->selectedList());
    infoList.append(m_cateModel4->selectedList());

    if (infoList.isEmpty())
        return;

    for (const QStringList info : infoList)
    {
        if (info[1].isEmpty())
            continue;

        result += QString(tr("厂商: %1, 软件包: %2, 期数: %3\n")).arg(info[0])
                                                                .arg(info[1])
                                                                .arg(info[2]);
    }

    m_label1->hide();
    m_label2->hide();
    m_label3->hide();
    m_label4->hide();
    m_infoView1->hide();
    m_infoView2->hide();
    m_infoView3->hide();
    m_infoView4->hide();
    m_deployDetail->clear();
    m_deployDetail->appendPlainText(result);
    m_deployDetail->show();
    m_nextStepBtn->hide();
    m_deployBtn->show();
    m_prevStepBtn->show();
    m_deployBtn->setText(tr("部署"));
}

void Deploy::showInfoView()
{
    m_label1->show();
    m_label2->show();
    m_label3->show();
    m_label4->show();
    m_infoView1->show();
    m_infoView2->show();
    m_infoView3->show();
    m_infoView4->show();
    m_nextStepBtn->show();
    m_deployDetail->hide();
    m_prevStepBtn->hide();
    m_deployBtn->hide();
}

void Deploy::startDeploy()
{
    m_deployDetail->appendPlainText("开始部署...\n");

    QDir dir(qApp->applicationDirPath());
//    dir.cdUp();

    QStringList fileList;

    QList<QStringList> infoList;
    infoList.append(m_cateModel1->selectedList());
    infoList.append(m_cateModel2->selectedList());
    infoList.append(m_cateModel3->selectedList());
    infoList.append(m_cateModel4->selectedList());
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

void Deploy::readFile()
{
    QFile info(m_fileLineEdit->text());
//    QFile info(qApp->applicationDirPath() + "/Deploy.csv");
    if (!info.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&info);
    QStringList itemInfo;
    QString itemType;

    // pass first line
    stream.readLine();

    while (!stream.atEnd()) {
        itemInfo = stream.readLine().split(',');
        if (itemInfo.size() != 4)
            continue;

        itemType = itemInfo[2];

        if (itemInfo[1].isEmpty())
            continue;

        itemInfo.removeAt(2);

        if (!itemType.compare(tr("电子白板")))
            m_cateModel2->append(itemInfo);
        else if (!itemType.compare(tr("投影仪")))
            m_cateModel1->append(itemInfo);
        else if (!itemType.compare(tr("实物展台")))
            m_cateModel3->append(itemInfo);
        else if (!itemType.compare(tr("互动触摸显示屏")))
            m_cateModel4->append(itemInfo);
        else
            qDebug() << itemType << itemInfo;
    }
}

void Deploy::chooseFile()
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Choose File",
                                         nullptr,
                                         GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         nullptr);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *fileName = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        m_fileLineEdit->setText(fileName);
        g_free(fileName);
    }

    gtk_widget_destroy(dialog);
    readFile();
}

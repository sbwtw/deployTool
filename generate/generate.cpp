#include "generate.h"
#include "itemdialog.h"

#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QDebug>
#include <QFileDialog>

Generate::Generate(QWidget *parent) :
    QMainWindow(parent)
{
    m_menuFile = new QMenu(tr("文件"));
    m_importAction = m_menuFile->addAction(tr("导入"));
    m_exportAction = m_menuFile->addAction(tr("导出"));
    m_menuBar = new QMenuBar;
    m_menuBar->addMenu(m_menuFile);
    m_infoModel = new InfoModel;
    m_infoModel->setSelectable(false);
    m_infoView = new QTableView;
    m_infoView->setModel(m_infoModel);
    m_modifyBtn = new QPushButton(tr("修改"));
    m_deleteBtn = new QPushButton(tr("删除"));
    m_addBtn = new QPushButton(tr("添加"));

    QHBoxLayout *toolLayout = new QHBoxLayout;
    toolLayout->addWidget(m_modifyBtn);
    toolLayout->addWidget(m_deleteBtn);
    toolLayout->addStretch();
    toolLayout->addWidget(m_addBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_infoView);
    mainLayout->addLayout(toolLayout);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(mainLayout);
    setMenuBar(m_menuBar);
    setFixedSize(600, 400);
    move(qApp->primaryScreen()->geometry().center() - rect().center());

    connect(m_importAction, &QAction::triggered, this, &Generate::importFromFile);
    connect(m_exportAction, &QAction::triggered, this, &Generate::exportToFile);
    connect(m_modifyBtn, &QPushButton::clicked, this, &Generate::modifyItem);
}

void Generate::importFromFile()
{
    QFileDialog chooser;
    chooser.setMimeTypeFilters(QStringList() << "text/csv");
    if (!chooser.exec())
        return;

    if (chooser.selectedFiles().isEmpty())
        return;

    const QString file = chooser.selectedFiles().first();
    m_infoModel->readInfoFile(file);
}

void Generate::exportToFile()
{
    QFileDialog chooser;
    chooser.setFileMode(QFileDialog::DirectoryOnly);
    chooser.setOption(QFileDialog::ShowDirsOnly);
    if (!chooser.exec())
        return;

    const QString dir = chooser.selectedFiles().first();
}

void Generate::modifyItem()
{
    ItemDialog dia;
    dia.exec();
}

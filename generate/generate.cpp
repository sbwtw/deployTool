#include "generate.h"
#include "itemdialog.h"

#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QHeaderView>
#include <QModelIndex>

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
    m_infoView->verticalHeader()->hide();
    m_infoView->setSortingEnabled(true);
    m_infoView->setSelectionMode(QAbstractItemView::NoSelection);
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
    connect(m_addBtn, &QPushButton::clicked, this, &Generate::addInfoItem);
    connect(m_deleteBtn, &QPushButton::clicked, this, &Generate::deleteInfoItem);

    m_infoModel->readInfoFile("/home/test.csv");
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
    const QModelIndex currentIndex = m_infoView->currentIndex();
    if (!currentIndex.isValid())
        return;

    ItemDialog dia;
    dia.setTypeCategory(m_infoModel->category());
    dia.setCompany(m_infoModel->data(currentIndex.sibling(currentIndex.row(), 0), Qt::DisplayRole).toString());
    dia.setPackage(m_infoModel->data(currentIndex.sibling(currentIndex.row(), 1), Qt::DisplayRole).toString());
    dia.setTime(m_infoModel->data(currentIndex.sibling(currentIndex.row(), 3), Qt::DisplayRole).toString());
    dia.setCurrentType(m_infoModel->category().indexOf(m_infoModel->data(currentIndex.sibling(currentIndex.row(), 2), Qt::DisplayRole).toString()));
    if (!dia.exec())
        return;

    m_infoModel->updateInfoItem(currentIndex, dia.company(), dia.package(), dia.type(), dia.time());
}

void Generate::addInfoItem()
{
    ItemDialog dia;
    dia.setTypeCategory(m_infoModel->category());
    if (!dia.exec())
        return;

    m_infoModel->appendInfoItem(dia.company(), dia.package(), dia.type(), dia.time());
}

void Generate::deleteInfoItem()
{
    m_infoModel->removeRow(m_infoView->currentIndex().row(), QModelIndex());
}

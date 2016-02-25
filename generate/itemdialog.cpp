#include "itemdialog.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

ItemDialog::ItemDialog(QWidget *parent) :
    QDialog(parent)
{
    m_company = new QLineEdit;
    m_type = new QComboBox;
    m_time = new QLineEdit;
    m_package = new QLineEdit;
    m_choosePackageBtn = new QPushButton(tr("选择"));
    m_cancelBtn = new QPushButton(tr("取消"));
    m_confirmBtn = new QPushButton(tr("确定"));

    QHBoxLayout *packageChooseLayout = new QHBoxLayout;
    packageChooseLayout->addWidget(m_package);
    packageChooseLayout->addWidget(m_choosePackageBtn);

    QGridLayout *infoGridLayout = new QGridLayout;
    infoGridLayout->addWidget(new QLabel(tr("厂商")), 0, 0);
    infoGridLayout->addWidget(m_company, 0, 1);
    infoGridLayout->addWidget(new QLabel(tr("类型")), 1, 0);
    infoGridLayout->addWidget(m_type, 1, 1);
    infoGridLayout->addWidget(new QLabel(tr("期数")), 2, 0);
    infoGridLayout->addWidget(m_time, 2, 1);
    infoGridLayout->addWidget(new QLabel(tr("软件包")), 3, 0);
    infoGridLayout->addLayout(packageChooseLayout, 3, 1);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(m_cancelBtn);
    btnLayout->addWidget(m_confirmBtn);
    btnLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(infoGridLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
}

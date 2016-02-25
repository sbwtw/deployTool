#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class ItemDialog : public QDialog
{
public:
    explicit ItemDialog(QWidget *parent = nullptr);

private:
    QLineEdit *m_company;
    QComboBox *m_type;
    QLineEdit *m_time;
    QLineEdit *m_package;
    QPushButton *m_choosePackageBtn;
    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
};

#endif // ITEMDIALOG_H

#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class ItemDialog : public QDialog
{
public:
    explicit ItemDialog(QWidget *parent = nullptr);

    void setTypeCategory(const QStringList &categoryList);
    void setCurrentType(const int index);
    inline const QString company() const {return m_company->text();}
    inline void setCompany(const QString &company) {m_company->setText(company);}
    inline const QString time() const {return m_time->text();}
    inline void setTime(const QString &time) {m_time->setText(time);}
    inline const QString package() const {return m_package->text();}
    inline void setPackage(const QString &package) {m_package->setText(package);}
    inline const QString type() const {return m_type->currentText();}

private slots:
    void choosePackageFile();

private:
    QLineEdit *m_company;
    QComboBox *m_type;
    QLineEdit *m_time;
    QLineEdit *m_package;
    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
    QPushButton *m_choosePackageBtn;
};

#endif // ITEMDIALOG_H

#ifndef GENERATE_H
#define GENERATE_H

#include "infomodel.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QTableView>

class Generate : public QMainWindow
{
public:
    explicit Generate(QWidget *parent = nullptr);

private slots:
    void importFromFile();
    void exportToFloder();
    void modifyItem();
    void addInfoItem();
    void deleteInfoItem();

private:
    QMenuBar *m_menuBar;
    QMenu *m_menuFile;
    QAction *m_importAction;
    QAction *m_exportAction;
    QTableView *m_infoView;
    InfoModel *m_infoModel;
    QPushButton *m_modifyBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_addBtn;
};

#endif // GENERATE_H

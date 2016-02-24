#ifndef INFOMODEL_H
#define INFOMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class InfoModel : public QAbstractTableModel
{
public:
    explicit InfoModel(QObject *parent = nullptr);

    void readInfoFile(const QString &file);

public:
    void selectByIndex(const QModelIndex &index);
    void sort(int column, Qt::SortOrder order);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QList<QStringList> selectedList() const;
//    QModelIndex index(int row, int column, const QModelIndex &parent) const;
//    QModelIndex parent(const QModelIndex &child) const;

//    Info *findInfoNode(const QModelIndex &parent) const;


private:
    QStringList m_headerList;
    QStringList m_categoryList;
//    QMap<QString, Info *> m_infoList;
    QList<QStringList> m_selectedList;
    QList<QStringList> m_infoList;
};

#endif // INFOMODEL_H

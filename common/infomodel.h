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
    void sort(int column, Qt::SortOrder order);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    inline void setSelectable(const bool selectable) {m_selectable = selectable;}
    inline QString currentFile() const {return m_currentFile;}
    void removeRow(int row, const QModelIndex &parent);
    void selectByIndex(const QModelIndex &index);
    void appendInfoItem(const QString &company, const QString &package, const QString &type, const QString &time);
    void updateInfoItem(const QModelIndex &index, const QString &company, const QString &package, const QString &type, const QString &time);
    QStringList category() const;
    QList<QStringList> selectedList() const;
//    QModelIndex index(int row, int column, const QModelIndex &parent) const;
//    QModelIndex parent(const QModelIndex &child) const;

//    Info *findInfoNode(const QModelIndex &parent) const;


private:
    QString m_currentFile;
    QStringList m_headerList;
    QStringList m_categoryList;
//    QMap<QString, Info *> m_infoList;
    QList<QStringList> m_selectedList;
    QList<QStringList> m_infoList;

    bool m_selectable = true;
};

#endif // INFOMODEL_H

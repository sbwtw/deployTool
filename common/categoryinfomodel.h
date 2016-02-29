#ifndef CATEGORYINFOMODEL_H
#define CATEGORYINFOMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class CategoryInfoModel : public QAbstractTableModel
{
public:
    explicit CategoryInfoModel(QObject *parent = nullptr);

    void append(const QStringList &data);
    QList<QStringList> selectedList() const;

public slots:
    void toggleByIndex(const QModelIndex &index);

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<QStringList> m_data;
    QList<QStringList> m_selectedData;
};

#endif // CATEGORYINFOMODEL_H

#include "categoryinfomodel.h"

#include <QDebug>

CategoryInfoModel::CategoryInfoModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

void CategoryInfoModel::append(const QStringList &data)
{
    const int rows = rowCount(QModelIndex());

    beginInsertRows(QModelIndex(), rows, rows);
    m_data.append(data);
    endInsertRows();
}

QList<QStringList> CategoryInfoModel::selectedList() const
{
    return m_selectedData;
}

void CategoryInfoModel::toggleByIndex(const QModelIndex &index)
{
    const QStringList item = m_data[index.row()];

    if (m_selectedData.contains(item))
        m_selectedData.removeOne(item);
    else
        m_selectedData.append(item);

    emit dataChanged(index, index);
}

int CategoryInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_data.size();
}

int CategoryInfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 3;
}

QVariant CategoryInfoModel::data(const QModelIndex &index, int role) const
{
    static int convert[] = {0, 2, 1};

    switch (role)
    {
    case Qt::DisplayRole:
        return m_data[index.row()][convert[index.column()]];
    case Qt::CheckStateRole:
        if (index.column())
            return QVariant();
        return m_selectedData.contains(m_data[index.row()]) ? Qt::Checked : Qt::Unchecked;
    default:
        return QVariant();
    }

    return QVariant();
}

QVariant CategoryInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        if (orientation == Qt::Vertical)
            return QString::number(section + 1);
        switch (section)
        {
        case 0:     return "厂家";        break;
        case 2:     return "Deb 包";     break;
        case 1:     return "期数";        break;
        default:    return QVariant();
        }
    default:
        return QVariant();
    }

    return QVariant();
}

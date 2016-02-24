#include "infomodel.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

InfoModel::InfoModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int InfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_infoList.size();
}

int InfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_headerList.size();
}

QVariant InfoModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return m_infoList[index.row()][index.column()];

    if (role == Qt::CheckStateRole && index.column() == 0)
        return m_selectedList.contains(m_infoList[index.row()]) ? Qt::Checked : Qt::Unchecked;

    return QVariant();
}

QVariant InfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_headerList[section];

    return QVariant();
}

QList<QStringList> InfoModel::selectedList() const
{
    return m_selectedList;
}

void InfoModel::selectByIndex(const QModelIndex &index)
{
    const QStringList &list = m_infoList[index.row()];

    if (m_selectedList.contains(list))
        m_selectedList.removeOne(list);
    else
        m_selectedList.append(list);

    emit dataChanged(index, index);
}

void InfoModel::sort(int column, Qt::SortOrder order)
{
    qSort(m_infoList.begin(), m_infoList.end(), [=] (const QStringList &a, const QStringList &b) {
        if (order == Qt::AscendingOrder)
            return a[column] > b[column];
        else
            return a[column] < b[column];
    });

    emit dataChanged(QModelIndex(), QModelIndex());
}

void InfoModel::readInfoFile(const QString &file)
{
    qDebug() << file;
    m_headerList.clear();
    m_categoryList.clear();
    m_infoList.clear();

    QFile info(file);
    if (!info.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&info);
    QStringList itemInfo;
    QString itemType;

    m_headerList = stream.readLine().split(',');

    while (!stream.atEnd()) {
        itemInfo = stream.readLine().split(',');
        itemType = itemInfo.first();

        if (itemInfo[1].isEmpty())
            continue;

        if (!m_categoryList.contains(itemType))
            m_categoryList.append(itemType);

        m_infoList.append(itemInfo);
    }

    // reload all data
    emit layoutChanged();
}

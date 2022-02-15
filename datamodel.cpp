#include "datamodel.h"
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QDebug>

DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent),
    currentRowCount(0)
{
    for (int i = 0; i < 10000; i++) {
//        QVariant value = QCryptographicHash::hash(QString::number(QRandomGenerator::global()->generate() & std::numeric_limits<qint64>::max()).toLatin1(), QCryptographicHash::Md5);
        QVariant value = QString::number(i) + "." + QString::number(QRandomGenerator::global()->generate() & std::numeric_limits<qint64>::max()).toLatin1();
        dataList.append(value);

    }
    wholeRowCount = dataList.size();
    headers << QString("Value");
}

DataModel::~DataModel()
{

}

int DataModel::rowCount(const QModelIndex &parent) const
{
    return currentRowCount;
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    return 12;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return dataList.at(index.row()).toString();

     return QVariant();
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal || section >= headers.size())
        return QVariant();

    return headers.at(section);
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    return {
        {Qt::DisplayRole, "display"},
        {1, "markId"},
        {2, "trackId"},
        {3, "rlsId"},
        {4, "time"},
        {5, "position"},
        {6, "velocity"},
        {7, "acceleration"},
        {8, "sigmasRBetaEps"},
        {9, "sigmasdRdBetadEps"},
    };
}

bool DataModel::canFetchMore(const QModelIndex &parent) const
{
    if (parent.isValid())
        return false;
    return (currentRowCount < wholeRowCount);
}

void DataModel::fetchMore(const QModelIndex &index)
{
    if (index.isValid())
        return;

    int toFetch = qMin(100, wholeRowCount - currentRowCount);

    if (toFetch <= 0)
        return;

    beginInsertRows(QModelIndex(), currentRowCount, currentRowCount + toFetch - 1);
    currentRowCount += toFetch;
    endInsertRows();
}

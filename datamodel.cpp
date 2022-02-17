#include "datamodel.h"
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QDebug>

DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent),
    currentRowCount(0)
{
}

DataModel::~DataModel()
{
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return currentRowCount;
//    return (dataModel.size() > 100) ? 100 : dataModel.size();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (dataModel.size() > 0)
        return dataModel.at(0).size();
    return 0;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return dataModel.at(index.row()).at(index.column()).toString();

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
//        {1, "markId"},
//        {2, "trackId"},
//        {3, "rlsId"},
//        {4, "time"},
//        {5, "position"},
//        {6, "velocity"},
//        {7, "acceleration"},
//        {8, "sigmasRBetaEps"},
//        {9, "sigmasdRdBetadEps"},
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

void DataModel::setDataModel(const QVector<QVector<QVariant>> &data)
{
    wholeRowCount = dataModel.size();
    beginResetModel();
    currentRowCount = dataModel.size();
    dataModel = data;
    endResetModel();
}

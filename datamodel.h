#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QtQml>

class DataModel : public QAbstractTableModel
{
        Q_OBJECT

    public:
        explicit DataModel(QObject *parent = nullptr);
        ~DataModel();

        static void declareQML(QQmlContext *context) {
            qmlRegisterType<DataModel>("com.aviacominfo.datapreparationtools.datamodel", 0, 1, "DataModel");
//            context->setContextProperty("dataModel", new DataModel());
        }

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        QHash<int, QByteArray> roleNames() const override;
        Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        void setDataModel(const QVector<QVector<QVariant>> &data);
        void setHeader(const QVector<QVariant> &headers) { this->headers = headers; }

    protected:
        bool canFetchMore(const QModelIndex &parent) const override;
        void fetchMore(const QModelIndex &index) override;

    private:
        QVector<QVector<QVariant>> dataModel;
        QVector<QVariant> headers;
        int wholeRowCount;
        int currentRowCount;
};

#endif // DATAMODEL_H

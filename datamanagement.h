#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QObject>
#include <QVariant>
#include <QDebug>

class DataModel;
class DatabaseAccess;
class QAbstractTableModel;
class DataManagement: public QObject
{
        Q_OBJECT

    public:
        DataManagement();

        Q_INVOKABLE void connectToSourceData(const QVariant config = QVariant());
        Q_INVOKABLE void fillDataModel(const QString name, const QVariant config = QVariant());
        Q_INVOKABLE DataModel* dataModel() { return model; }
        Q_INVOKABLE void createShp();

    public:
        DataModel *model;
        DatabaseAccess *databaseAccess;

    private:
        QString currentNameDate;

    signals:
        void complitedCreateShape();
        void rejectedDataSource();
        void count(QString);
};

#endif // DATAMANAGEMENT_H

#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QObject>
#include <QVariant>

class DataModel;
class QAbstractTableModel;
class DataManagement: public QObject
{
        Q_OBJECT

    public:
        DataManagement();

        Q_INVOKABLE void connectToSourceData(const QVariant config = QVariant());
        Q_INVOKABLE void getData();
        Q_INVOKABLE DataModel* dataModel() { return model; }

    public:
        DataModel *model;
};

#endif // DATAMANAGEMENT_H

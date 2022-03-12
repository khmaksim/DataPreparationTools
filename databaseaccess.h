#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QVariant>

typedef QMap<QVariant, QVariant> Record;
class DatabaseAccess : public QObject
{
        Q_OBJECT
    public:
        DatabaseAccess(QObject *parent = nullptr);

        void getData(QVector<Record> &airways, QVector<QVariant> &header, const QVariant &configConnectDatabase = QVariant());

        void initConnectDatabase(const QString &host, int port, const QString &nameDatabase, const QString &user, const QString &password);
        bool isConnected() const;
        bool connect(const QVariant &configConectDatabase = QVariant());

    private:
        QString host;
        QString nameDatabase;
        QString user;
        QString password;
        int port;

        QSqlDatabase db;

    signals:
        void connected();
        void notificationConnected(const QString);
};

#endif // DATABASEACCESS_H

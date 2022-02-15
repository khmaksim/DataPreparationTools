#include "databaseaccess.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>

DatabaseAccess::DatabaseAccess(QObject *parent) : QObject(parent)
{
}

DatabaseAccess* DatabaseAccess::instance()
{
    static DatabaseAccess instance;
//    instance.connect();               // SQLite
    return &instance;
}

//DatabaseAccess* DatabaseAccess::getInstance()
//{
//    if(databaseAccess == 0)
//       databaseAccess = new DatabaseAccess;
//    return databaseAccess;
//}


void DatabaseAccess::initConnectDatabase(const QString &host, int port, const QString &nameDatabase, const QString &user, const QString &password)
{
    this->host = host;
    this->port = port;
    this->nameDatabase = nameDatabase;
    this->user = user;
    this->password = password;
}

bool DatabaseAccess::connect(const QVariant &configConectDatabase)
{
    QMap<QString, QVariant> config = configConectDatabase.toMap();

    if (config.isEmpty())
        db = QSqlDatabase::addDatabase("QPSQL");
    else {
        db = QSqlDatabase::addDatabase("QPSQL", QString("test"));
        host = config.value("host").toString();
        port = config.value("port").toInt();
        nameDatabase = config.value("nameDatabase").toString();
        user = config.value("user").toString();
        password = config.value("password").toString();
    }

    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(nameDatabase);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        if (!host.isEmpty() && !nameDatabase.isEmpty() && !user.isEmpty() && !password.isEmpty())
            emit notificationConnected(db.lastError().text());
        return false;
    }
    emit connected();

    // remove test connect to database
    if (db.connectionName().contains("test"))
        QSqlDatabase::removeDatabase(QString("test"));

    return true;
}

QVector<Record> DatabaseAccess::getData()
{
    qDebug() << "Call from QML";
    QSqlQuery query(db);
    QVector<Record> points = QVector<Record>();

    query.exec("SELECT * FROM backup.CATALOG");

    if (query.lastError().isValid())
        qDebug() << query.lastError().text() << query.lastQuery();

    while (query.next()) {
        Record record;
        QSqlRecord sqlRecord = query.record();
        int col = 0;
        while (col < sqlRecord.count()){
            record.insert(col, query.value(col));
            col++;
        }
        points.append(record);
    }

    return points;
}

bool DatabaseAccess::isConnected() const
{
    return QSqlDatabase::database().isOpen();
}

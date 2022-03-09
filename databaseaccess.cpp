#include "databaseaccess.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>
#include <QTextCodec>

DatabaseAccess::DatabaseAccess(QObject *parent) : QObject(parent)
{
}

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
        db = QSqlDatabase::addDatabase("QPSQL");//, QString("test"));
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

void DatabaseAccess::getData(const QVariant &configConectDatabase, QVector<Record> &airways, QVector<QVariant> &header)
{
    this->connect(configConectDatabase);

    QSqlQuery query(db);

    query.exec("SELECT rt.txt_desig, COALESCE(point_st.txt_name, '') AS point_st, COALESCE(point_nx.txt_name, '') AS point_nx, "
               "COALESCE(rts.val_mag_track, 0) AS val_mag_track, COALESCE(rts.val_revers_mag_track, 0) AS val_revers_mag_track, "
               "COALESCE(ct_lw.txt_code, '') AS ct_lw, COALESCE(rts.val_dist_ver_upper, 0) AS val_dist_ver_upper, "
               "COALESCE(ct_up.txt_code, '') AS ct_up, COALESCE(rts.val_dist_ver_lower, 0) AS val_dist_ver_lower, "
               "ROUND(COALESCE(rts.val_len, 0), 0) AS rts_val_len, COALESCE(geo_b.txt_code, '') AS geo_code, "
               "COALESCE(ct_dir.full_name, '') AS ct_dir_full_name "
               "FROM public.en_route_rte as rt "
               "LEFT JOIN rte_seg_m as rts ON rt.id = rts.route "
               "LEFT JOIN rte_seg_use as rts_u ON rts_u.segment = rts.id "
               "LEFT JOIN significant_point as point_st ON point_st.id = rts.start "
               "LEFT JOIN significant_point as point_nx ON point_nx.id = rts.next "
               "LEFT JOIN \"CATALOG\" as ct_lw ON rts.uom_dist_ver_lower = ct_lw.id "
               "LEFT JOIN \"CATALOG\" as ct_up ON rts.uom_dist_ver_upper = ct_up.id "
               "LEFT JOIN \"GEO_BORDER\" as geo_b ON geo_b.id = rts.border "
               "LEFT JOIN \"CATALOG\" as ct_dir ON ct_dir.id = rts_u.code_dir "
               "ORDER BY rt.txt_desig");

    if (query.lastError().isValid()) {
        QTextCodec *coding = QTextCodec::codecForName("cp-1251");
        coding->setCodecForLocale(coding);
        qDebug() << query.lastError().text() << query.lastQuery();
    }

    bool isHeaderFull = false;
    while (query.next()) {
        Record record;
        QSqlRecord sqlRecord = query.record();
        int col = 0;

        while (col < sqlRecord.count()) {
            if (!isHeaderFull)
                header.append(sqlRecord.fieldName(col));

            record.insert(col, query.value(col));
            col++;
        }
        airways.append(record);
        isHeaderFull = true;
    }
}

bool DatabaseAccess::isConnected() const
{
    return QSqlDatabase::database().isOpen();
}

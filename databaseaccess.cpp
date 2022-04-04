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
    querySqlStr.insert("airways", QString("SELECT rt.txt_desig, COALESCE(point_st.txt_name, '') AS point_st, COALESCE(point_nx.txt_name, '') AS point_nx, "
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
                                          "ORDER BY rt.txt_desig"));

    querySqlStr.insert("points", QString("SELECT COALESCE(cat.txt_name, '') AS type, COALESCE(sp.txt_name, '') AS name, "
                                         "CAST(CASE WHEN COALESCE(sp.geo_lat, 0) > 0 THEN CONCAT(split_part(sp.geo_lat::varchar, '.', 1), 'N') "
                                         "WHEN COALESCE(sp.geo_lat, 0) < 0 THEN CONCAT(split_part(sp.geo_lat::varchar, '.', 1), 'S') "
                                         "ELSE '0' END AS text) AS lat, "
                                         "CAST(CASE WHEN COALESCE(sp.geo_long, 0) > 0 THEN CONCAT(split_part(sp.geo_long::varchar, '.', 1), 'E') "
                                         "WHEN COALESCE(sp.geo_long, 0) < 0 THEN CONCAT(split_part(sp.geo_long::varchar, '.',  1), 'W') "
                                         "ELSE '0' END AS text) AS lon, "
                                         "COALESCE(sp.id, 0), COALESCE(gb.txt_name, '') AS country "
                                         "FROM designated_point dp, significant_point sp, \"GEO_BORDER\" gb, \"CATALOG\" cat "
                                         "WHERE dp.id = sp.id AND sp.border = gb.id AND cat.id = dp.code_type"));

    querySqlStr.insert("rts", QString("SELECT COALESCE(sp.txt_name_alt, '') as name_rus, COALESCE(sp.txt_name, '') as name, "
                                      "CASE WHEN sp.point_type::integer = 1 THEN 'VOR' "
                                      "WHEN sp.point_type::integer = 2 THEN 'NDB' "
                                      "WHEN sp.point_type::integer = 3 THEN 'VOR/NDB' "
                                      "WHEN sp.point_type::integer = 16 THEN 'DME' "
                                      "WHEN sp.point_type::integer = 17 THEN 'VOR/DME' "
                                      "ELSE '' END AS typ, "
                                      "COALESCE(CASE "
                                      "WHEN sp.point_type::integer = ANY (ARRAY[1, 3, 5, 17]) THEN v.val_freq "
                                      "WHEN sp.point_type::integer = ANY (ARRAY[2, 34]) THEN n.val_freq "
                                      "WHEN sp.point_type::integer = 16 THEN d.val_ghost_freq "
                                      "WHEN sp.point_type::integer = 32 THEN m.val_freq "
                                      "ELSE 0 END, 0) AS freq, "
                                      "CASE WHEN sp.point_type::integer = ANY (ARRAY[1, 3, 5, 17]) THEN v.code_id::character varying "
                                      "WHEN sp.point_type::integer = ANY (ARRAY[2, 34]) THEN n.code_id::character varying "
                                      "WHEN sp.point_type::integer = 16 THEN d.code_id::character varying "
                                      "WHEN sp.point_type::integer = 32 THEN btrim(k1.txt_code::text)::character varying "
                                      "ELSE NULL::character varying "
                                      "END::character varying(16) AS designator, "
                                      "COALESCE(sp.val_mag_var, 0) AS magvar, "
                                      "COALESCE(sp.id, 0) AS id, "
                                      "CAST(CASE WHEN sp.geo_lat > 0 THEN CONCAT(split_part(sp.geo_lat::varchar, '.', 1), 'N') "
                                      "WHEN sp.geo_lat < 0 THEN CONCAT(split_part(sp.geo_lat::varchar, '.', 1), 'S') "
                                      "ELSE '0' END AS text) AS lat, "
                                      "CAST(CASE WHEN sp.geo_long > 0 THEN "
                                      "CASE WHEN length(split_part(sp.geo_long::varchar, '.', 1)) = 6 "
                                      "THEN '0' || split_part(sp.geo_long::varchar, '.', 1) || 'E' "
                                      "ELSE split_part(sp.geo_long::varchar, '.', 1) || 'E' END "
                                      "WHEN sp.geo_long < 0 THEN "
                                      "CASE WHEN length(split_part(sp.geo_long::varchar, '.', 1)) = 6 "
                                      "THEN '0' || split_part(sp.geo_long::varchar, '.', 1) || 'W' "
                                      "ELSE split_part(sp.geo_long::varchar, '.', 1) || 'W' END "
                                      "ELSE '0' END AS text) AS lon, "
                                      "CASE WHEN sp.point_type::integer = 16 THEN d.code_channel "
                                      "ELSE '' END AS channel, "
                                      "CASE WHEN sp.point_type::integer = 16 THEN d.val_elev "
                                      "ELSE 0 END AS Habs, "
                                      "COALESCE(gb.txt_name, '') AS country "
                                      "FROM significant_point sp "
                                      "LEFT JOIN ndb n ON n.id::integer = sp.id::integer AND n.valid = 'Y'::bpchar "
                                      "LEFT JOIN vor v ON v.id::integer = sp.id::integer AND v.valid = 'Y'::bpchar "
                                      "LEFT JOIN dme d ON d.id::integer = sp.id::integer AND d.valid = 'Y'::bpchar "
                                      "LEFT JOIN mkr m ON m.id::integer = sp.id::integer AND m.valid = 'Y'::bpchar "
                                      "LEFT JOIN \"CATALOG\" k1 ON k1.id::integer = m.code_id::integer "
                                      "LEFT JOIN \"TIMETABLE\" tm ON tm.object::integer = sp.id::integer "
                                      "LEFT JOIN \"CATALOG\" k2 ON k2.id::integer = tm.code_work_hr::integer "
                                      "LEFT JOIN \"GEO_BORDER\" gb ON sp.border = gb.id"));

    querySqlStr.insert("obstacle", QString("SELECT vob.txt_name, vob.code_id AS designator, vob.box_len, vob.box_wid, "
                                           "vob.isfrangible, vob.hobj, vob.uomelev, vob.lightcolor, vob.lightmode "
                                           "FROM public.vobstacle vob"));
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

void DatabaseAccess::getData(const QString &name, QVector<Record> &data, QVector<QVariant> &header, const QVariant &configConnectDatabase)
{
    if (!configConnectDatabase.isNull())
        this->connect(configConnectDatabase);

    if (!querySqlStr.contains(name))
        return;

    QSqlQuery query(db);

    query.exec(querySqlStr.value(name));

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
        data.append(record);
        isHeaderFull = true;
    }
}

bool DatabaseAccess::isConnected() const
{
    return QSqlDatabase::database().isOpen();
}

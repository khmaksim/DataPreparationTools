#include "datamanagement.h"
#include "databaseaccess.h"
#include "datamodel.h"
#include "Singleton.h"
#include <Python.h>

DataManagement::DataManagement()
{
    model = new DataModel(this);
}

void DataManagement::connectToSourceData(const QVariant config)
{
    Singleton<DatabaseAccess>::instance().connect(config);
}

void DataManagement::getData(const QVariant config)
{
    QVector<Record> airways;
    QVector<QVariant> headers;
    Singleton<DatabaseAccess>::instance().getData(config, airways, headers);
    QVector<Record>::const_iterator it = airways.cbegin();
    QVector<QVector<QVariant>> dataAll;

    while (it != airways.cend()) {
        QList<QVariant> values = (*it).values();
        QList<QVariant>::const_iterator itValue = values.cbegin();
        QVector<QVariant> dataLine;

        while (itValue != values.cend()) {
            dataLine.append((*itValue));
            ++itValue;
        }
        dataAll.append(dataLine);
        ++it;
    }

    model->setDataModel(dataAll);
    model->setHeader(headers);
}

void DataManagement::createShp()
{
    Py_Initialize();
    do {
//        PyObject *sys = PyImport_ImportModule("sys");
//        PyObject *sysPath = PyObject_GetAttrString(sys, "path");
//        PyObject *pathToScripts = PyUnicode_FromString((const char*) "./scripts");
//        PyList_Append(sysPath, pathToScripts);
//        PyObject *dect;
//        PyObject *result;
//        dect = Py_BuildValue("{s:i}", "name", 2);

//        result = PyObject_Call(callback, NULL, dict);

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./scripts')");
        PyRun_SimpleString("import create_shp");

        for (int iRow = 0; iRow < model->rowCount(); iRow++) {
            QStringList row = QStringList();

            for (int iCol = 0; iCol < model->columnCount(); iCol++)
                row.append(model->index(iRow, iCol).data().toString());
            PyRun_SimpleString(QString("create_shp.addData('%1')").arg(row.join(";")).toLocal8Bit().constData()/*.toLatin1()*/);
        }

        QDir dir(qApp->applicationDirPath());
        if (!dir.exists("shp")) {
            dir.mkpath("shp");
            qDebug() << "mkdir";
        }

        PyRun_SimpleString(QString("create_shp.createShp('%1')").arg(qApp->applicationDirPath().append("\\shp")).toLocal8Bit().constData());

//        PyRun_SimpleString("print(simple.get_value(2.0))");
//        PyRun_SimpleString("print(simple.get_value(\"Hello!\"))");

//        PyObject *nameModule = PyUnicode_FromString("create_shp");
//        if (!nameModule) {
//            break;
//        }

//        // Загрузить объект модуля
//        PyObject *module = PyImport_Import(nameModule);
//        if (!module) {
//            break;
//        }

//        PyObject *pObjct = PyDict_GetItemString(pDict, (const char *) "get_value");
//        if (!pObjct) {
//            return ret;
//        }
    } while (0);

    PyErr_Print();
    Py_Finalize();
    emit complitedCreateShape();
}

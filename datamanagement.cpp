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
        PyObject *sys = PyImport_ImportModule("sys");
        PyObject *sysPath = PyObject_GetAttrString(sys, "path");
        PyObject *pathToScripts = PyUnicode_FromString((const char*) "./scripts");
        PyList_Append(sysPath, pathToScripts);

        PyObject *nameModule = PyUnicode_FromString("create_shp");
        if (!nameModule) {
            break;
        }

        // Загрузить объект модуля
        PyObject *module = PyImport_Import(nameModule);
        if (!module) {
            break;
        }

    } while (0);

    Py_Finalize();
}

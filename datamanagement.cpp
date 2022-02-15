#include "datamanagement.h"
#include "databaseaccess.h"
#include "datamodel.h"

DataManagement::DataManagement()
{
    model = new DataModel(this);
}

void DataManagement::connectToSourceData(const QVariant config)
{
    DatabaseAccess::instance()->connect(config);
}

void DataManagement::getData()
{

}

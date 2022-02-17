QT += quick sql

CONFIG += c++11 staticlib
QMAKE_CXXFLAGS_WARN_ON = -Wall -fPIE

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        datamanagement.cpp \
        main.cpp \
        databaseaccess.cpp \
        datamodel.cpp

HEADERS += \
        databaseaccess.h \
        datamanagement.h \
        datamodel.h \
        patterns/Singleton.h

RESOURCES += qml.qrc

LIBS += C:\Python27\ArcGIS10.8\libs\python27.lib

INCLUDEPATH += patterns/ \
            C:\Python27\ArcGIS10.8\include

QMAKE_CXXFLAGS += C:\Python27\ArcGIS10.8\libs\python27.lib

TRANSLATIONS += \
    DataPreparationTools_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

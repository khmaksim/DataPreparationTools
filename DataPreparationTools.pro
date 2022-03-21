QT += quick sql

CONFIG += c++11# staticlib
#QMAKE_CXXFLAGS_WARN_ON = -Wall -fPIE

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

INCLUDEPATH += $$PWD/patterns/ \
            C:\Python27\ArcGIS10.8\include

OTHER_FILES += \
    $$PWD/scripts

#QMAKE_CXXFLAGS += C:\Python27\ArcGIS10.8\libs\python27.lib

TRANSLATIONS += \
    DataPreparationTools_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Var_1 Copy files
## Задаём переменную, которая должна содержать путь к папке с данными
#DESTDIR_WIN = $$PWD/scripts
#DESTDIR_WIN ~= s,/,\\,g
## Задаём путь откуда всё приложение с DLL-ками нужно будет скопировать
##PWD_WIN = $$OUT_PWD/../../HelloRelease
##PWD_WIN ~= s,/,\\,g

## Прежде, чем выполнять сборку инсталляторов, необходимо скопировать файлы
## из выходной папки проекта вместе со всеми DLL в папку data, которая относится
## к собираемому пакету
#copydata.commands = $(COPY_DIR) $$DESTDIR_WIN
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata

DIR_WITH_SCRIPTS = scripts

exists($$DIR_WITH_SCRIPTS) {
        message("Scripts directory existing")
    } else {
        QMAKE_POST_LINK += $$quote(mkdir $${DIR_WITH_SCRIPTS} $$escape_expand(\n\t))
    }

#create.commands = $(MKDIR) $$DIR_WITH_SCRIPTS
#export(create.commands)
#QMAKE_EXTRA_TARGETS += create
#POST_TARGETDEPS += create

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Var_2 Copy files
# copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # replace slashes in destination path for Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # replace slashes in source path for Windows
        win32:file ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

copyToDestDir($$OTHER_FILES, $$OUT_PWD/scripts/)

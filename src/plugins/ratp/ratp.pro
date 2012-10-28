include(../../../globals.pri)

TARGET = ratp
TEMPLATE = lib
QT = core network xml
CONFIG += plugin
INCLUDEPATH += ../../lib/base/
INCLUDEPATH += ../../lib/pluginhelper
LIBS += -L../../lib/base -l$${NAME}
LIBS += -L../../lib/pluginhelper -l$${NAME}pluginhelper

HEADERS +=      ratp.h \
                ratpwaitingtimehelper.h

SOURCES +=      ratp.cpp \
                ratpwaitingtimehelper.cpp

RESOURCES +=    res.qrc

OTHER_FILES +=  ratp.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

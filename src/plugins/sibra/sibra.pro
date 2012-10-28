include(../../../globals.pri)

TARGET = sibra
TEMPLATE = lib
QT = core network
CONFIG += plugin
INCLUDEPATH += ../../lib/base/
INCLUDEPATH += ../../lib/pluginhelper/
LIBS += -L../../lib/base -l$${NAME}
LIBS += -L../../lib/pluginhelper/ -l$${NAME}pluginhelper

HEADERS +=      sibra.h \

SOURCES +=      sibra.cpp \

OTHER_FILES +=  sibra.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

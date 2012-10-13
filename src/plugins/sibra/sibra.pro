include(../../../globals.pri)

TARGET = sibra
TEMPLATE = lib
QT = core network
CONFIG += plugin
INCLUDEPATH += ../../lib/
#INCLUDEPATH += ../../3rdparty/qjson/src
LIBS += -L../../lib/ -l$${NAME}
#LIBS += -L../../3rdparty/qjson/ -lqjson

HEADERS +=      sibra.h \

SOURCES +=      sibra.cpp \

OTHER_FILES +=  sibra.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

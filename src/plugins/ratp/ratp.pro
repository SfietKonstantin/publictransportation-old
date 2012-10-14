include(../../../globals.pri)

TARGET = ratp
TEMPLATE = lib
QT = core network xml
CONFIG += plugin
INCLUDEPATH += ../../lib/
#INCLUDEPATH += ../../3rdparty/qjson/src
LIBS += -L../../lib/ -l$${NAME}
#LIBS += -L../../3rdparty/qjson/ -lqjson

HEADERS +=      ratp.h \

SOURCES +=      ratp.cpp \

RESOURCES +=    res.qrc

OTHER_FILES +=  ratp.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

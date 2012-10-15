include(../../../globals.pri)

TARGET = hsl
TEMPLATE = lib
QT = core network xml
CONFIG += plugin
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=      hsl.h \

SOURCES +=      hsl.cpp \

OTHER_FILES +=  hsl.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

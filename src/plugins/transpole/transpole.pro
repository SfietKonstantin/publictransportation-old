include(../../../globals.pri)

TARGET = transpole
TEMPLATE = lib
QT = core network
CONFIG += plugin
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=      transpole.h \

SOURCES +=      transpole.cpp \

OTHER_FILES +=  transpole.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

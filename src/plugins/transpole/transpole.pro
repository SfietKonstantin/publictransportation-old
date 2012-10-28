include(../../../globals.pri)

TARGET = transpole
TEMPLATE = lib
QT = core network
CONFIG += plugin
INCLUDEPATH += ../../lib/base/
INCLUDEPATH += ../../lib/pluginhelper/
LIBS += -L../../lib/base -l$${NAME}
LIBS += -L../../lib/pluginhelper/ -l$${NAME}pluginhelper

HEADERS +=      transpole.h \
                transpolesuggestedstationshelper.h \
                transpolejourneysfromstationhelper.h \
                transpolewaitingtimehelper.h

SOURCES +=      transpole.cpp \
                transpolesuggestedstationshelper.cpp \
                transpolejourneysfromstationhelper.cpp \
                transpolewaitingtimehelper.cpp

OTHER_FILES +=  transpole.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

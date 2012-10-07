include(../../../globals.pri)

TARGET = tl
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=      transportlausannois.h \
                tllist.h \

SOURCES +=      transportlausannois.cpp \
                tllist.cpp \

OTHER_FILES +=  tl.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

include(../../../globals.pri)

TARGET = tl
TEMPLATE = lib
QT = core network xml
CONFIG += plugin
INCLUDEPATH += ../../lib/base/
INCLUDEPATH += ../../lib/pluginhelper/
INCLUDEPATH += ../../3rdparty/qjson/src
LIBS += -L../../lib/base -l$${NAME}
LIBS += -L../../lib/pluginhelper/ -l$${NAME}pluginhelper
LIBS += -L../../3rdparty/qjson/ -lqjson

HEADERS +=      transportlausannois.h \
                transportlausannoiswaitingtimehelper.h

SOURCES +=      transportlausannois.cpp \
                transportlausannoiswaitingtimehelper.cpp

RESOURCES +=    res.qrc

OTHER_FILES +=  tl.desktop

# deployment
target.path = $${PLUGIN_FOLDER}

desktopFile.path = $${PLUGIN_FOLDER}
desktopFile.files = $${OTHER_FILES}

INSTALLS += target desktopFile

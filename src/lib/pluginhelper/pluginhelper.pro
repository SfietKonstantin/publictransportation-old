include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}pluginhelper
QT = core xml

INCLUDEPATH += ../base/
LIBS += -L../base/ -l$${NAME}

DEFINES += PUBLICTRANSPORTATIONPLUGINHELPER_LIBRARY

HEADERS +=      publictransportationpluginhelper_global.h \
                languagehelper.h \
                abstractsuggestedstationshelper.h \
                abstractsuggestedstationshelper_p.h \
                abstractcachedsuggestedstationshelper.h \
                offlinesuggestedstationshelper.h \
                offlinexmljourneysfromstationhelper.h \
                abstractwaitingtimehelper.h \

SOURCES +=      languagehelper.cpp \
                abstractsuggestedstationshelper.cpp \
                abstractcachedsuggestedstationshelper.cpp \
                offlinesuggestedstationshelper.cpp \
                offlinexmljourneysfromstationhelper.cpp \
                abstractwaitingtimehelper.cpp \

# Deployment
target.path = $${LIBDIR}
export(target.path)

INSTALLS += target



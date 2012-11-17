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
                abstractonlinehelper.h \
                abstractonlinehelper_p.h \
                abstractsuggestedstationshelper.h \
                abstractsuggestedstationshelper_p.h \
                abstractcachedsuggestedstationshelper.h \
                abstractjourneysfromstationhelper.h \
                abstractjourneysfromstationhelper_p.h \
                abstractwaitingtimehelper.h \
                abstractwaitingtimehelper_p.h \
                offlinesuggestedstationshelper.h \
                offlinexmljourneysfromstationhelper.h \

SOURCES +=      languagehelper.cpp \
                abstractonlinehelper.cpp \
                abstractsuggestedstationshelper.cpp \
                abstractcachedsuggestedstationshelper.cpp \
                abstractjourneysfromstationhelper.cpp \
                abstractwaitingtimehelper.cpp \
                offlinesuggestedstationshelper.cpp \
                offlinexmljourneysfromstationhelper.cpp \

# Deployment
target.path = $${LIBDIR}
export(target.path)

INSTALLS += target



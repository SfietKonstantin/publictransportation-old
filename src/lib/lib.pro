include(../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = publictransportation
QT = core dbus

DEFINES += PUBLICTRANSPORTATION_LIBRARY

HEADERS =   publictransportation_global.h \
            debug.h \
            common/capabilitiesconstants.h \
            common/commonhelper.h \
            common/transportationobject.h \
            common/company.h \
            common/line.h \
            common/journey.h \
            common/station.h \
            common/dbus/dbusconstants.h \
            common/dbus/dbushelper.h

SOURCES +=  common/transportationobject.cpp \
            common/company.cpp \
            common/line.cpp \
            common/journey.cpp \
            common/station.cpp \
            common/dbus/dbushelper.cpp

# Deployment
target.path = $${LIBDIR}
export(target.path)

INSTALLS += target

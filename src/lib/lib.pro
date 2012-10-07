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
            common/dbus/dbushelper.h \
            manager/desktopfileparser_p.h \
            manager/backendinfo.h \
            manager/abstractbackendwrapper.h \
            manager/abstractbackendwrapper_p.h \
            manager/dbus/dbusbackendwrapper.h \
            manager/dbus/dbusbackendwrapperadaptor.h \

SOURCES +=  common/transportationobject.cpp \
            common/company.cpp \
            common/line.cpp \
            common/journey.cpp \
            common/station.cpp \
            common/dbus/dbushelper.cpp \
            manager/desktopfileparser_p.cpp \
            manager/backendinfo.cpp \
            manager/abstractbackendwrapper.cpp \
            manager/dbus/dbusbackendwrapper.cpp \
            manager/dbus/dbusbackendwrapperadaptor.cpp \

# Deployment
target.path = $${LIBDIR}
export(target.path)

INSTALLS += target

include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}
QT = core dbus

DEFINES += PT2_LIBRARY

HEADERS =   pt2_global.h \
            debug.h \
            common/capabilitiesconstants.h \
            common/errorid.h \
            common/object.h \
            common/company.h \
            common/line.h \
            common/ride.h \
            common/station.h \
#            common/infojourneys.h \
#            common/waitingtime.h \
#            common/journeyandwaitingtime.h \
#            common/infojourneywaitingtime.h \
#            common/dbus/dbusconstants.h \
#            manager/desktopfileparser_p.h \
#            manager/backendinfo.h \
#            manager/abstractbackendwrapper.h \
#            manager/abstractbackendwrapper_p.h \
#            manager/abstractbackendmanager.h \
#            manager/backendlistmanager.h \
#            manager/dbus/dbusbackendwrapper.h \
#            manager/dbus/dbusbackendwrapperadaptor.h \
#            manager/dbus/dbusbackendmanager.h \
#            provider/providerplugininterface.h \
#            provider/providerpluginobject.h \
#            provider/dbus/backenddbusproxy.h \
#            provider/dbus/providerplugindbuswrapper.h \

SOURCES +=  common/object.cpp \
            common/company.cpp \
            common/line.cpp \
            common/ride.cpp \
            common/station.cpp \
#            common/infojourneys.cpp \
#            common/waitingtime.cpp \
#            common/journeyandwaitingtime.cpp \
#            common/infojourneywaitingtime.cpp \
#            common/dbus/dbushelper.cpp \
#            manager/desktopfileparser_p.cpp \
#            manager/backendinfo.cpp \
#            manager/abstractbackendwrapper.cpp \
#            manager/abstractbackendmanager.cpp \
#            manager/backendlistmanager.cpp \
#            manager/dbus/dbusbackendwrapper.cpp \
#            manager/dbus/dbusbackendwrapperadaptor.cpp \
#            manager/dbus/dbusbackendmanager.cpp \
#            provider/providerpluginobject.cpp \
#            provider/dbus/backenddbusproxy.cpp \
#            provider/dbus/providerplugindbuswrapper.cpp \

# Deployment
target.path = $${LIBDIR}
export(target.path)

INSTALLS += target

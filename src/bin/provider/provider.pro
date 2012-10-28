include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-provider

QT = core dbus
INCLUDEPATH += ../../lib/base/
LIBS += -L../../lib/base/ -l$${NAME}

HEADERS +=  \

SOURCES +=  main.cpp

# deployment
target.path = $${APPLICATION_FOLDER}
INSTALLS += target

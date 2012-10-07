include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-provider

QT = core dbus
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=  \

SOURCES +=  main.cpp

# deployment
target.path = $${APPLICATION_FOLDER}
INSTALLS += target

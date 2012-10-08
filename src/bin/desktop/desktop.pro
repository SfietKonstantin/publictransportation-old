include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}

QT = core
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=  dbushandle.h

SOURCES +=  main.cpp \
            dbushandle.cpp

# deployment
target.path = $${APPLICATION_FOLDER}
INSTALLS += target

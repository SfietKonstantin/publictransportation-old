include(../../../globals.pri)

TEMPLATE = app
TARGET = dbuswrappertesthelper

QT = core dbus
INCLUDEPATH += ../../../src/lib/
LIBS += -L../../../src/lib/ -l$${NAME}

SOURCES +=  main.cpp \

# Deployment
target.path = $${TEST_FOLDER}/helpers
INSTALLS += target

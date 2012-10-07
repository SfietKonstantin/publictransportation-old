include(../../../globals.pri)

TEMPLATE = app
TARGET = dbustesthelper

QT = core dbus
INCLUDEPATH += ../../../src/lib/
INCLUDEPATH += ../../tests
LIBS += -L../../../src/lib/ -l$${NAME}

SOURCES +=  main.cpp \

# Deployment
target.path = $${TEST_FOLDER}/helpers
INSTALLS += target

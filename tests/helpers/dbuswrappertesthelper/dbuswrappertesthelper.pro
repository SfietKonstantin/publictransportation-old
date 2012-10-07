include(../../../globals.pri)

TEMPLATE = app
TARGET = dbuswrappertesthelper

QT = core dbus
INCLUDEPATH += ../../../src/lib/
#INCLUDEPATH += ../../tests
LIBS += -L../../../src/lib/ -l$${NAME}

SOURCES +=  main.cpp \

# Deployment
target.path = $${TEST_FOLDER}/helpers
export(target.path)

INSTALLS += target

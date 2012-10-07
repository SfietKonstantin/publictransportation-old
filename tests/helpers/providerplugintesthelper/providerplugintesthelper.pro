include(../../../globals.pri)

TARGET = providerplugintesthelper
TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH += ../../../src/lib/
LIBS += -L../../../src/lib/ -l$${NAME}

HEADERS +=      providerplugintesthelper.h \

SOURCES +=      providerplugintesthelper.cpp \

# deployment
target.path = $${TEST_FOLDER}/helpers
INSTALLS += target

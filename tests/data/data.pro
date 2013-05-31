include(../../globals.pri)

TARGET = tst_pt2_data
QT = core dbus
CONFIG  += qtestlib
INCLUDEPATH += ../../src/lib/base/

LIBS += -L../../src/lib/base/ -l$${NAME}

HEADERS +=  generator.h \

SOURCES +=  generator.cpp \
            tst_pt2_data.cpp

# Deployment
target.path = $${TEST_FOLDER}
export(target.path)

INSTALLS += target

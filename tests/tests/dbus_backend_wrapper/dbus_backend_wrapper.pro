include(../../../globals.pri)

TARGET = tst_pt2_dbus_backend_wrapper
QT = core dbus
CONFIG  += qtestlib
INCLUDEPATH += ../../../src/lib/base/

LIBS += -L../../../src/lib/base/ -l$${NAME}

SOURCES +=  tst_pt2_dbus_backend_wrapper.cpp

# Deployment
target.path = $${TEST_FOLDER}

INSTALLS += target helper

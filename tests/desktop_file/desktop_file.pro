include(../../globals.pri)

TARGET = tst_pt2_desktop_file
QT = core dbus
CONFIG  += qtestlib
INCLUDEPATH += ../../src/lib/base/

LIBS += -L../../src/lib/base/ -l$${NAME}

SOURCES +=  tst_pt2_desktop_file.cpp

# Deployment
target.path = $${TEST_FOLDER}
export(target.path)

INSTALLS += target

RESOURCES += \
    res.qrc

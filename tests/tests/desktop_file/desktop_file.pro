include(../../../globals.pri)

TARGET = tst_pt2_desktop_file
QT = core
CONFIG  += qtestlib
INCLUDEPATH += ../../../src/lib/base/

LIBS += -L../../../src/lib/base/ -l$${NAME}

SOURCES +=  tst_pt2_desktop_file.cpp

RESOURCES += res.qrc

# Deployment
target.path = $${TEST_FOLDER}

INSTALLS += target


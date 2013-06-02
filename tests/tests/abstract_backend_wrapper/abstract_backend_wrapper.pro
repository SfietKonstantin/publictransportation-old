include(../../../globals.pri)

TARGET = tst_pt2_abstract_backend_wrapper
QT = core
CONFIG  += qtestlib
INCLUDEPATH += ../../../src/lib/base/

LIBS += -L../../../src/lib/base/ -l$${NAME}

HEADERS +=  ../generator.h \

SOURCES +=  ../generator.cpp \
            tst_pt2_abstract_backend_wrapper.cpp

# Deployment
target.path = $${TEST_FOLDER}

INSTALLS += target

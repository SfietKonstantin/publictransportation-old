include(../globals.pri)

QT = core
CONFIG  += qtestlib
INCLUDEPATH += ../src/lib/

LIBS += -L../src/lib/ -l$${NAME}

HEADERS +=  generator.h \
            testbase.h \

SOURCES +=  main.cpp \
            generator.cpp \
            testbase.cpp \

# Deployment
target.path = $${TEST_FOLDER}
export(target.path)

INSTALLS += target

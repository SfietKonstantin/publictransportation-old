include(../../globals.pri)

QT = core dbus
CONFIG  += qtestlib
INCLUDEPATH += ../../src/lib/

LIBS += -L../../src/lib/ -l$${NAME}

DEFINES += 'HELPER_FOLDER=\'\"$${TEST_FOLDER}/helpers\"\''

HEADERS +=  generator.h \
            testbase.h \
            dbusobject.h \
            testdbus.h \

SOURCES +=  main.cpp \
            generator.cpp \
            testbase.cpp \
            dbusobject.cpp \
            testdbus.cpp \

# Deployment
target.path = $${TEST_FOLDER}
export(target.path)

INSTALLS += target

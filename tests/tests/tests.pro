include(../../globals.pri)

QT = core dbus
CONFIG  += qtestlib
INCLUDEPATH += ../../src/lib/

LIBS += -L../../src/lib/ -l$${NAME}

DEFINES += 'HELPER_FOLDER=\'\"$${TEST_FOLDER}/helpers\"\''

HEADERS +=  generator.h \
            dbusobject.h \
            test.h \

SOURCES +=  generator.cpp \
            dbusobject.cpp \
            test.cpp \

# Deployment
target.path = $${TEST_FOLDER}
export(target.path)

INSTALLS += target

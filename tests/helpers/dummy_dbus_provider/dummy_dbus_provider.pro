include(../../../globals.pri)

TEMPLATE = app
TARGET = dummy_dbus_provider

QT = core dbus

INCLUDEPATH += ../../../src/lib/base/

# Deployment
target.path = $${TEST_HELPER_FOLDER}

INSTALLS += target

SOURCES += \
    main.cpp


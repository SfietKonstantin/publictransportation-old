include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}

DEFINES += 'MAIN_QML_FILE=\'\"$${QML_FOLDER}/main.qml\"\''

QT = core gui declarative
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=      backendmodel.h \
                companiesmodel.h \

SOURCES +=      main.cpp \
                backendmodel.cpp \
                companiesmodel.cpp \

OTHER_FILES +=  main.qml \
                UiConstants.js \
                HorizontalSeparator.qml \
                AbstractPage.qml \
                AbstractNavigationPage.qml \
                ClickableEntry.qml \
                MainPage.qml \
                BackendEntry.qml \
                BackendSelectorPage.qml \

# deployment
target.path = $${APPLICATION_FOLDER}

qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${OTHER_FILES}

INSTALLS += target qmlFiles

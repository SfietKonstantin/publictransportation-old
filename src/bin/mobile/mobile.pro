include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}

DEFINES += 'MAIN_QML_FILE=\'\"$${QML_FOLDER}/main.qml\"\''

QT = core gui declarative
INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}

HEADERS +=      backendmodel.h \
                searchstationmodel.h \
                journeysfromstationmodel.h \
                waitingtimemodel.h \

SOURCES +=      main.cpp \
                backendmodel.cpp \
                searchstationmodel.cpp \
                journeysfromstationmodel.cpp \
                waitingtimemodel.cpp \

OTHER_FILES +=  main.qml \
                UiConstants.js \
                HorizontalSeparator.qml \
                GroupIndicator.qml \
                AbstractPage.qml \
                AbstractNavigationPage.qml \
                ClickableEntry.qml \
                MainPage.qml \
                BackendEntry.qml \
                BackendSelectorPage.qml \
                SearchStationPage.qml \
                JourneysFromStationPage.qml \
                WaitingTimePage.qml \

# deployment
target.path = $${APPLICATION_FOLDER}

qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${OTHER_FILES}

contains(MEEGO_EDITION,harmattan):{
desktopFile.path = /usr/share/applications
desktopFile.files = publictransportation.desktop

icon.path = /usr/share/icons/hicolor/80x80/apps
icon.files = publictransportation.png
}

INSTALLS += target qmlFiles desktopFile

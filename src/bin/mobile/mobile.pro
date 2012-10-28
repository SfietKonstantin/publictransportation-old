include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}

DEFINES += 'MAIN_QML_FILE=\'\"$${QML_FOLDER}/main.qml\"\''
DEFINES += 'ICON_FILE=\'\"$${DATA_FOLDER}/publictransportation-big.png\"\''
DEFINES += 'I18N_FOLDER=\'\"$${I18N_FOLDER}/\"\''


QT = core gui xml declarative

INCLUDEPATH += ../../lib/
LIBS += -L../../lib/ -l$${NAME}


HEADERS +=      xmlconversionhelper.h \
                favouritemanager.h \
                backendmodel.h \
                backendcopyrightmanager.h \
                searchstationmodel.h \
                journeysfromstationmodel.h \
                waitingtimemodel.h \
                stationsfromjourneymodel.h \
                support/countriesmodel.h \


SOURCES +=      main.cpp \
                xmlconversionhelper.cpp \
                favouritemanager.cpp \
                backendmodel.cpp \
                backendcopyrightmanager.cpp \
                searchstationmodel.cpp \
                journeysfromstationmodel.cpp \
                waitingtimemodel.cpp \
                stationsfromjourneymodel.cpp \
                support/countriesmodel.cpp \

OTHER_FILES +=  main.qml \
                UiConstants.js \
                HorizontalSeparator.qml \
                GroupIndicator.qml \
                UpdateHeader.qml \
                AbstractPage.qml \
                AbstractNavigationPage.qml \
                ClickableEntry.qml \
                MainPage.qml \
                BackendInfoSheet.qml \
                BackendEntry.qml \
                BackendSelectorPage.qml \
                SearchStationPage.qml \
                JourneysFromStationPage.qml \
                WaitingTimePage.qml \
                AboutPage.qml \

DATA_FILES +=   publictransportation-big.png

TRANSLATIONS_FILES += i18n/*.qm

# deployment
target.path = $${APPLICATION_FOLDER}

qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${OTHER_FILES}

dataFiles.path = $${DATA_FOLDER}
dataFiles.files = $${DATA_FILES}

translationsFiles.path = $${I18N_FOLDER}
translationsFiles.files = $${TRANSLATIONS_FILES}

contains(MEEGO_EDITION,harmattan):{
desktopFile.path = /usr/share/applications
desktopFile.files = publictransportation.desktop

iconFile.path = /usr/share/icons/hicolor/80x80/apps
iconFile.files = publictransportation.png
}

INSTALLS += target qmlFiles dataFiles translationsFiles

contains(MEEGO_EDITION,harmattan):{
INSTALLS += desktopFile iconFile
}

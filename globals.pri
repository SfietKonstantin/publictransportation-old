# name
NAME = publictransportation

# version
VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 51

isEmpty(DEPLOYMENT_PREFIX) {
    DEPLOYMENT_PREFIX = /usr
}

isEmpty(PREFIX) {
    CONFIG(release):PREFIX = /usr
    CONFIG(debug, debug|release):PREFIX = $${DEPLOYMENT_PREFIX}
}

DEFAULT_IMPORT_FOLDER = /usr/lib$${64_BITS}/qt4/imports/

# Default directories
isEmpty(BINDIR) {
    BINDIR = $${PREFIX}/bin
}
isEmpty(LIBDIR) {
    LIBDIR = $${PREFIX}/lib
}
isEmpty(IMPORTDIR) {
    CONFIG(noqtimport):{
        IMPORTDIR = $${PREFIX}/imports/
    } else {
        IMPORTDIR = $${DEFAULT_IMPORT_FOLDER}
    }
}
isEmpty(SHAREDIR) {
    SHAREDIR = $${PREFIX}/share/$${NAME}
}

isEmpty(OPTDIR) {

    OPTDIR = /opt/$${NAME}
}

isEmpty(INCLUDEDIR) {
    INCLUDEDIR = $${PREFIX}/include/$${NAME}
}

# Application + data + qml folders
contains(MEEGO_EDITION,harmattan):{
    APPLICATION_FOLDER  = $${OPTDIR}/bin
    DATA_FOLDER = $${OPTDIR}/data
    PLUGIN_FOLDER = $${OPTDIR}/plugins
    QML_FOLDER = $${OPTDIR}/qml
} else {
    APPLICATION_FOLDER  = $${BINDIR}
    DATA_FOLDER = $${SHAREDIR}/data
    PLUGIN_FOLDER = $${SHAREDIR}/plugins
    QML_FOLDER = $${SHAREDIR}/qml
}

# Test folder
TEST_FOLDER = $${SHAREDIR}/tests/

# QML include folder
QML_PLUGIN_BASE_PATH = $${IMPORTDIR}/org/SfietKonstantin/
QML_PLUGIN_PATH = $${QML_PLUGIN_BASE_PATH}/$${NAME}


# Useful defines
DEFINES += 'VERSION_MAJOR=$${VERSION_MAJOR}'
DEFINES += 'VERSION_MINOR=$${VERSION_MINOR}'
DEFINES += 'VERSION_PATCH=$${VERSION_PATCH}'

DEFINES += 'APPLICATION_FOLDER=\'\"$${APPLICATION_FOLDER}\"\''
DEFINES += 'PLUGIN_FOLDER=\'\"$${PLUGIN_FOLDER}\"\''
DEFINES += 'PROVIDER_PATH=\'\"$${APPLICATION_FOLDER}/$${NAME}-provider\"\''

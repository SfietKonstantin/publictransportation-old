#!/bin/sh
PLUGINPATH=../../plugins
HSL=$PLUGINPATH/hsl/hsl.cpp
RATP=$PLUGINPATH/ratp/ratp.cpp
SIBRA=$PLUGINPATH/sibra/sibra.cpp
TL=$PLUGINPATH/tl/transportlausannois.cpp
TRANSPOLE=$PLUGINPATH/transpole/transpole.cpp

COUNTRIESMODEL=support/countriesmodel.cpp
BACKENDCOPYRIGHTMANAGER=backendcopyrightmanager.cpp
QMLFILES=*.qml

lupdate $COUNTRIESMODEL $BACKENDCOPYRIGHTMANAGER $QMLFILES $HSL $RATP $SIBRA $TL $TRANSPOLE -ts i18n/en.ts
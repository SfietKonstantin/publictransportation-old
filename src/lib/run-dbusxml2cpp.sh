#!/bin/sh
qdbusxml2cpp -i common/company.h -i dbusbackendwrapper.h -a manager/dbus/dbusbackendwrapperadaptor -l PublicTransportation::DBusBackendWrapper common/dbus/backend.xml
qdbusxml2cpp -p provider/dbus/backenddbusproxy -i common/company.h -i common/line.h -i common/journey.h -i common/station.h common/dbus/backend.xml

#!/bin/sh
qdbusxml2cpp -a manager/dbus/dbusbackendwrapperadaptor -i dbusbackendwrapper.h -l PublicTransportation::DBusBackendWrapper common/dbus/backend.xml
qdbusxml2cpp -p provider/dbus/backenddbusproxy -i common/company.h -i common/line.h -i common/journey.h -i common/station.h -i common/waitingtime.h common/dbus/backend.xml

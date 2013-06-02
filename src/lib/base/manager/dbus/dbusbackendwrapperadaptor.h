/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -a manager/dbus/dbusbackendwrapperadaptor -i dbusbackendwrapper.h -l PT2::DBusBackendWrapper common/dbus/backend.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef DBUSBACKENDWRAPPERADAPTOR_H_1370116919
#define DBUSBACKENDWRAPPERADAPTOR_H_1370116919

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "dbusbackendwrapper.h"
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface org.SfietKonstantin.pt2
 */
class Pt2Adaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.SfietKonstantin.pt2")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.SfietKonstantin.pt2\">\n"
"    <!-- Methods for registration -->\n"
"    <method name=\"registerBackendStart\"/>\n"
"    <method name=\"registerBackendProgress\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"progress\"/>\n"
"    </method>\n"
"    <method name=\"registerBackendReady\">\n"
"      <arg direction=\"in\" type=\"as\" name=\"capabilities\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"copyright\"/>\n"
"    </method>\n"
"    <!-- Method used to transmit errors -->\n"
"    <method name=\"registerError\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"request\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"errorId\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"error\"/>\n"
"    </method>\n"
"    <!-- Copyright -->\n"
"    <!--<signal name=\"copyrightRequested\">\n"
"            <arg name=\"request\" type=\"s\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerCopyright\">\n"
"            <arg name=\"request\" type=\"s\" direction=\"in\" />,\n"
"            <arg name=\"copyright\" type=\"s\" direction=\"in\" />,\n"
"        </method>-->\n"
"    <!-- Autocompletion for station search -->\n"
"    <!--<signal name=\"suggestStationsRequested\">\n"
"            <arg name=\"request\" type=\"s\" direction=\"out\" />\n"
"            <arg name=\"partialStation\" type=\"s\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerSuggestedStations\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const QList&lt;PublicTransportation::Station&gt; &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"in\" />,\n"
"            <arg name=\"suggestedStationList\" type=\"a(a{sv}sa{sv})\" direction=\"in\" />\n"
"        </method>-->\n"
"    <!-- All journeys from a station -->\n"
"    <!--<signal name=\"journeysFromStationRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const PublicTransportation::Station &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"out\" />\n"
"            <arg name=\"station\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"limit\" type=\"i\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerJourneysFromStation\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const QList&lt;PublicTransportation::InfoJourneys&gt; &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"in\" />\n"
"            <arg name=\"infoJourneysList\"\n"
"                 type=\"a((a{sv}sa{sv})(a{sv}sa{sv})a((a{sv}sa{sv})(a{sv}sa{sv})))\"\n"
"                 direction=\"in\" />\n"
"             </method>-->\n"
"    <!-- All journeys + waiting time from a station -->\n"
"    <!--<signal name=\"journeysAndWaitingTimesFromStationRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const PublicTransportation::Station &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"out\" />\n"
"            <arg name=\"station\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"limit\" type=\"i\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerJourneysAndWaitingTimesFromStation\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const QList&lt;PublicTransportation::InfoJourneyWaitingTime&gt; &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"in\" />\n"
"            <arg name=\"infoJourneyWaitingTimeList\"\n"
"                 type=\"a((a{sv}sa{sv})(a{sv}sa{sv})(a{sv}sa{sv})(a{sv}sa{sv})(ia{sv}))\"\n"
"                 direction=\"in\" />\n"
"             </method>-->\n"
"    <!-- Waiting time for a journey -->\n"
"    <!--<signal name=\"waitingTimeRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\"\n"
"                        value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In3\"\n"
"                        value=\"const PublicTransportation::Journey &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In4\"\n"
"                        value=\"const PublicTransportation::Station &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"out\" />\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"journey\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"station\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerWaitingTime\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const QList&lt;PublicTransportation::JourneyAndWaitingTime&gt; &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"in\" />\n"
"            <arg name=\"journeyAndWaitingTimeList\" type=\"a((a{sv}sa{sv})(ia{sv}))\" direction=\"in\" />\n"
"        </method>-->\n"
"    <!-- List of stations for a given journey -->\n"
"    <!--<signal name=\"stationsFromJourneyRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\"\n"
"                        value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In3\"\n"
"                        value=\"const PublicTransportation::Journey &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In4\"\n"
"                        value=\"const PublicTransportation::Station &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"out\" />\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"journey\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"station\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerStationsFromJourney\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\"\n"
"                        value=\"const QList&lt;PublicTransportation::Station&gt; &amp;\"/>\n"
"            <arg name=\"request\" type=\"s\" direction=\"in\" />\n"
"            <arg name=\"stationList\" type=\"a(a{sv}sa{sv})\" direction=\"in\" />\n"
"        </method>-->\n"
"  </interface>\n"
        "")
public:
    Pt2Adaptor(PT2::DBusBackendWrapper *parent);
    virtual ~Pt2Adaptor();

    inline PT2::DBusBackendWrapper *parent() const
    { return static_cast<PT2::DBusBackendWrapper *>(QObject::parent()); }

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void registerBackendProgress(int progress);
    void registerBackendReady(const QStringList &capabilities, const QString &copyright);
    void registerBackendStart();
    void registerError(const QString &request, const QString &errorId, const QString &error);
Q_SIGNALS: // SIGNALS
};

#endif

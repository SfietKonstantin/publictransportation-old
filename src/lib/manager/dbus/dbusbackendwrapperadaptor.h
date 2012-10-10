/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -a manager/dbus/dbusbackendwrapperadaptor -i dbusbackendwrapper.h -l PublicTransportation::DBusBackendWrapper common/dbus/backend.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef DBUSBACKENDWRAPPERADAPTOR_H_1349883541
#define DBUSBACKENDWRAPPERADAPTOR_H_1349883541

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
 * Adaptor class for interface org.SfietKonstantin.publictransportation
 */
class PublictransportationAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.SfietKonstantin.publictransportation")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.SfietKonstantin.publictransportation\">\n"
"    <!-- Method for registration -->\n"
"    <method name=\"registerBackend\">\n"
"      <arg direction=\"in\" type=\"as\" name=\"capabilities\"/>\n"
"    </method>\n"
"    <!-- Method used to transmit that something wrong happened -->\n"
"    <method name=\"registerError\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"request\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"error\"/>\n"
"    </method>\n"
"    <!-- Autocompletion for station search -->\n"
"    <signal name=\"suggestStationsRequested\">\n"
"      <arg direction=\"out\" type=\"i\" name=\"request\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"partialStation\"/>\n"
"    </signal>\n"
"    <method name=\"registerSuggestedStations\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"request\"/>,\n"
"            <arg direction=\"in\" type=\"as\" name=\"suggestedStations\"/>\n"
"    </method>\n"
"    <!--<signal name=\"listCompaniesRequested\" />\n"
"        <signal name=\"listLinesRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"        </signal>\n"
"        <signal name=\"listJourneysRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"        </signal>\n"
"        <signal name=\"listStationsRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\" value=\"const PublicTransportation::Journey &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"journey\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"        </signal>\n"
"        <signal name=\"getWaitingTimeRequested\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\" value=\"const PublicTransportation::Journey &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In3\" value=\"const PublicTransportation::Station &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"journey\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"            <arg name=\"station\" type=\"(a{sv}sa{sv})\" direction=\"out\" />\n"
"        </signal>\n"
"        <method name=\"registerBackend\">\n"
"            <arg name=\"capabilities\" type=\"as\" direction=\"in\"/>\n"
"        </method>\n"
"        <method name=\"registerListedCompanies\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const QList&lt;PublicTransportation::Company&gt; &amp;\"/>\n"
"            <arg name=\"companies\" type=\"a(a{sv}sa{sv})\" direction=\"in\"/>\n"
"        </method>\n"
"        <method name=\"registerListedLines\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const QList&lt;PublicTransportation::Line&gt; &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"lines\" type=\"a(a{sv}sa{sv})\" direction=\"in\"/>\n"
"        </method>\n"
"        <method name=\"registerListedJourneys\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\" value=\"const QList&lt;PublicTransportation::Journey&gt; &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"journeys\" type=\"a(a{sv}sa{sv})\" direction=\"in\"/>\n"
"        </method>\n"
"        <method name=\"registerListedStations\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\" value=\"const PublicTransportation::Journey &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In3\" value=\"const QList&lt;PublicTransportation::Station&gt; &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"journey\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"stations\" type=\"a(a{sv}sa{sv})\" direction=\"in\"/>\n"
"        </method>\n"
"        <method name=\"registerWaitingTime\">\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In0\" value=\"const PublicTransportation::Company &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In1\" value=\"const PublicTransportation::Line &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In2\" value=\"const PublicTransportation::Journey &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In3\" value=\"const PublicTransportation::Station &amp;\"/>\n"
"            <annotation name=\"org.qtproject.QtDBus.QtTypeName.In4\" value=\"const QList&lt;PublicTransportation::WaitingTime&gt; &amp;\"/>\n"
"            <arg name=\"company\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"line\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"journey\" type=\"(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"station\" type=\"a(a{sv}sa{sv})\" direction=\"in\"/>\n"
"            <arg name=\"waitingTime\" type=\"a(ia{sv})\" direction=\"in\" />\n"
"        </method>-->\n"
"  </interface>\n"
        "")
public:
    PublictransportationAdaptor(PublicTransportation::DBusBackendWrapper *parent);
    virtual ~PublictransportationAdaptor();

    inline PublicTransportation::DBusBackendWrapper *parent() const
    { return static_cast<PublicTransportation::DBusBackendWrapper *>(QObject::parent()); }

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void registerBackend(const QStringList &capabilities);
    void registerError(int request, const QString &error);
    void registerSuggestedStations(int request, const QStringList &suggestedStations);
Q_SIGNALS: // SIGNALS
    void suggestStationsRequested(int request, const QString &partialStation);
};

#endif

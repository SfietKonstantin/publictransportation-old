/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -p provider/dbus/backenddbusproxy -i common/company.h -i common/line.h -i common/journey.h -i common/station.h common/dbus/backend.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef BACKENDDBUSPROXY_H_1349602601
#define BACKENDDBUSPROXY_H_1349602601

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"

/*
 * Proxy class for interface org.SfietKonstantin.publictransportation
 */
class OrgSfietKonstantinPublictransportationInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.SfietKonstantin.publictransportation"; }

public:
    OrgSfietKonstantinPublictransportationInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgSfietKonstantinPublictransportationInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> registerBackend(const QStringList &capabilities)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(capabilities);
        return asyncCallWithArgumentList(QLatin1String("registerBackend"), argumentList);
    }

    inline QDBusPendingReply<> registerListedCompanies(const QList<PublicTransportation::Company> & companies)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(companies);
        return asyncCallWithArgumentList(QLatin1String("registerListedCompanies"), argumentList);
    }

    inline QDBusPendingReply<> registerListedJourneys(const PublicTransportation::Company & company, const PublicTransportation::Line & line, const QList<PublicTransportation::Journey> & journeys)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(company) << QVariant::fromValue(line) << QVariant::fromValue(journeys);
        return asyncCallWithArgumentList(QLatin1String("registerListedJourneys"), argumentList);
    }

    inline QDBusPendingReply<> registerListedLines(const PublicTransportation::Company & company, const QList<PublicTransportation::Line> & lines)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(company) << QVariant::fromValue(lines);
        return asyncCallWithArgumentList(QLatin1String("registerListedLines"), argumentList);
    }

    inline QDBusPendingReply<> registerListedStations(const PublicTransportation::Company & company, const PublicTransportation::Line & line, const PublicTransportation::Journey & journey, const QList<PublicTransportation::Station> & stations)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(company) << QVariant::fromValue(line) << QVariant::fromValue(journey) << QVariant::fromValue(stations);
        return asyncCallWithArgumentList(QLatin1String("registerListedStations"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void listCompaniesRequested();
    void listJourneysRequested(const PublicTransportation::Company & company, const PublicTransportation::Line & line);
    void listLinesRequested(const PublicTransportation::Company & company);
    void listStationsRequested(const PublicTransportation::Company & company, const PublicTransportation::Line & line, const PublicTransportation::Journey & journey);
};

namespace org {
  namespace SfietKonstantin {
    typedef ::OrgSfietKonstantinPublictransportationInterface publictransportation;
  }
}
#endif
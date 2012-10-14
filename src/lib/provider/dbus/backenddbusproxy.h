/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -p provider/dbus/backenddbusproxy -i common/company.h -i common/line.h -i common/journey.h -i common/station.h -i common/waitingtime.h -i common/infojourneys.h common/dbus/backend.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef BACKENDDBUSPROXY_H_1350203983
#define BACKENDDBUSPROXY_H_1350203983

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
#include "common/waitingtime.h"
#include "common/infojourneys.h"

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

    inline QDBusPendingReply<> registerCopyright(const QString &request, const QString &copyright)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(request) << QVariant::fromValue(copyright);
        return asyncCallWithArgumentList(QLatin1String("registerCopyright"), argumentList);
    }

    inline QDBusPendingReply<> registerError(const QString &request, const QString &errorId, const QString &error)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(request) << QVariant::fromValue(errorId) << QVariant::fromValue(error);
        return asyncCallWithArgumentList(QLatin1String("registerError"), argumentList);
    }

    inline QDBusPendingReply<> registerJourneysFromStation(const QString &request, const QList<PublicTransportation::InfoJourneys> & infoJourneys)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(request) << QVariant::fromValue(infoJourneys);
        return asyncCallWithArgumentList(QLatin1String("registerJourneysFromStation"), argumentList);
    }

    inline QDBusPendingReply<> registerSuggestedStations(const QString &request, const QList<PublicTransportation::Station> & suggestedStations)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(request) << QVariant::fromValue(suggestedStations);
        return asyncCallWithArgumentList(QLatin1String("registerSuggestedStations"), argumentList);
    }

    inline QDBusPendingReply<> registerWaitingTime(const QString &request, const QList<PublicTransportation::WaitingTime> & waitingTimeList)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(request) << QVariant::fromValue(waitingTimeList);
        return asyncCallWithArgumentList(QLatin1String("registerWaitingTime"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void copyrightRequested(const QString &request);
    void journeysFromStationRequested(const QString &request, const PublicTransportation::Station & station, int limit);
    void suggestStationsRequested(const QString &request, const QString &partialStation);
    void waitingTimeRequested(const QString &request, const PublicTransportation::Company & company, const PublicTransportation::Line & line, const PublicTransportation::Journey & journey, const PublicTransportation::Station & station);
};

namespace org {
  namespace SfietKonstantin {
    typedef ::OrgSfietKonstantinPublictransportationInterface publictransportation;
  }
}
#endif

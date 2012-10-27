/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#include "backendcopyrightmanager.h"

#include "common/capabilitiesconstants.h"
#include "manager/abstractbackendmanager.h"
#include "manager/abstractbackendwrapper.h"
#include "debug.h"

namespace PublicTransportation
{

namespace Gui
{

class BackendCopyrightManagerPrivate
{
public:
    BackendCopyrightManagerPrivate(BackendCopyrightManager *q);
    void queryCopyright(AbstractBackendWrapper *backend);
    void createCapabilities(AbstractBackendWrapper *backend);
    void slotStatusChanged();
    void slotCopyrightRegistered(const QString &request, const QString &newCopyright);
    /**
    * @internal
    * @brief Backend manager
    */
   AbstractBackendManager *backendManager;
    QString copyright;
    QString capabilities;
    bool loading;
private:
    BackendCopyrightManager * const q_ptr;
    Q_DECLARE_PUBLIC(BackendCopyrightManager)
};

BackendCopyrightManagerPrivate::BackendCopyrightManagerPrivate(BackendCopyrightManager *q):
    q_ptr(q)
{
}

void BackendCopyrightManagerPrivate::queryCopyright(AbstractBackendWrapper *backend)
{
    Q_Q(BackendCopyrightManager);
    q->connect(backend, SIGNAL(copyrightRegistered(QString,QString)),
               q, SLOT(slotCopyrightRegistered(QString,QString)));
    backend->requestCopyright();
}

void BackendCopyrightManagerPrivate::createCapabilities(AbstractBackendWrapper *backend)
{
    Q_Q(BackendCopyrightManager);
    QString newCapabilities;
    QTextStream stream (&newCapabilities);
    stream << "<ul>";
    foreach (QString capability, backend->capabilities()) {
        stream << "<li>";
        if (capability == SUGGEST_STATIONS) {
            stream << BackendCopyrightManager::tr("Search for a station");
        } else if (capability == JOURNEYS_FROM_STATION
                   || capability == JOURNEYS_WAITING_TIMES_FROM_STATION) {
            stream << BackendCopyrightManager::tr("List journeys from a station");
        } else if (capability ==  WAITING_TIME
                   || capability == JOURNEYS_WAITING_TIMES_FROM_STATION) {
            stream << BackendCopyrightManager::tr("Give waiting time at a station");
        }
        stream << "</li>";
    }
    stream << "</ul>";

    if (capabilities != newCapabilities) {
        capabilities = newCapabilities;
        emit q->capabilitiesChanged();
    }
}

void BackendCopyrightManagerPrivate::slotStatusChanged()
{
    Q_Q(BackendCopyrightManager);
    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(q->sender());
    q->sender()->disconnect(q);
    if (!backend) {
        return;
    }

    queryCopyright(backend);
}

void BackendCopyrightManagerPrivate::slotCopyrightRegistered(const QString &request,
                                                             const QString &newCopyright)
{
    Q_UNUSED(request)
    Q_Q(BackendCopyrightManager);
    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(q->sender());
    q->sender()->disconnect(q);
    if (!backend) {
        return;
    }

    if (copyright != newCopyright) {
        copyright = newCopyright;
        emit q->copyrightChanged();
    }
    createCapabilities(backend);

    loading = false;
    emit q->loadingChanged();
}

////// End of private class //////

BackendCopyrightManager::BackendCopyrightManager(QObject *parent) :
    QObject(parent), d_ptr(new BackendCopyrightManagerPrivate(this))
{
    Q_D(BackendCopyrightManager);
    d->loading = false;
}

BackendCopyrightManager::~BackendCopyrightManager()
{
}

bool BackendCopyrightManager::isLoading() const
{
    Q_D(const BackendCopyrightManager);
    return d->loading;
}

QString BackendCopyrightManager::copyright() const
{
    Q_D(const BackendCopyrightManager);
    return d->copyright;
}

QString BackendCopyrightManager::capabilities() const
{
    Q_D(const BackendCopyrightManager);
    return d->capabilities;
}

void BackendCopyrightManager::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(BackendCopyrightManager);
    if (d->backendManager != backendManager) {
        d->backendManager = backendManager;
    }
}

void BackendCopyrightManager::setBackend(const QString &identifier)
{
    Q_D(BackendCopyrightManager);
    if (!d->backendManager) {
        return;
    }

    if (!d->backendManager->contains(identifier)) {
        return;
    }

    d->copyright = QString();
    d->capabilities = QString();
    emit copyrightChanged();
    emit capabilitiesChanged();

    AbstractBackendWrapper *backend = d->backendManager->backend(identifier);
    AbstractBackendWrapper::Status status = backend->status();

    switch (status) {
    case AbstractBackendWrapper::Launching:
        connect(backend, SIGNAL(statusChanged()), this, SLOT(slotStatusChanged()));
        break;
    case AbstractBackendWrapper::Launched:
        d->queryCopyright(backend);
        break;
    default:
        return;
        break;
    }

    d->loading = true;
    emit loadingChanged();
}


}

}

#include "moc_backendcopyrightmanager.cpp"

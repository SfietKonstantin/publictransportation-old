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

/**
 * @file favouritemanager.h
 * @short Implementation of PublicTransportation::Gui::FavouriteManager
 */

#include "favouritemanager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtCore/QTextStream>
#include <QtGui/QDesktopServices>
#include <QtXml/QDomDocument>

#include "common/station.h"
#include "xmlconversionhelper.h"
#include "debug.h"

static const char *BACKEND_ATTRIBUTE = "backend";

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::FavouriteManager
 */
class FavouriteManagerPrivate
{
public:
    /**
     * @internal
     * @brief Load
     */
    void load();
    /**
     * @internal
     * @brief Save
     */
    void save();
    /**
     * @internal
     * @brief Filename
     */
    QString fileName;
    /**
     * @internal
     * @brief Data
     */
    QList<QPair<QString, Station> > data;
};

void FavouriteManagerPrivate::load()
{
    QDir favouriteDir = QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    if (!favouriteDir.exists(fileName)) {
        return;
    }

    QFile file (favouriteDir.absoluteFilePath(fileName));
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QDomDocument document;
    document.setContent(&file);
    file.close();

    QDomElement element = document.documentElement().firstChildElement();

    while (!element.isNull()) {
        Station station = XmlConversionHelper::fromXmlToStation(element);
        QString backend = element.attribute(BACKEND_ATTRIBUTE);

        data.append(QPair<QString, Station>(backend, station));

        element = element.nextSiblingElement();
    }
}

void FavouriteManagerPrivate::save()
{
    QDomDocument document;
    QDomElement rootElement = document.createElement("favourites");

    QListIterator<QPair<QString, Station> > iterator
            = QListIterator<QPair<QString, Station> >(data);
    while (iterator.hasNext()) {
        QPair<QString, Station> entry = iterator.next();
        QDomElement element = XmlConversionHelper::toXml(entry.second, &document);
        element.setAttribute(BACKEND_ATTRIBUTE, entry.first);
        rootElement.appendChild(element);
    }
    document.appendChild(rootElement);

    QDir favouriteDir = QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    if (!favouriteDir.exists()) {
        QDir::root().mkpath(favouriteDir.absolutePath());
    }


    QFile file (favouriteDir.absoluteFilePath(fileName));
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(&file);
    document.save(stream, 2);
    file.close();
}

////// End of private class //////

FavouriteManager::FavouriteManager(const QString &fileName, QObject *parent):
    QObject(parent), d_ptr(new FavouriteManagerPrivate)
{
    Q_D(FavouriteManager);
    d->fileName = fileName;
    d->load();
}

FavouriteManager::~FavouriteManager()
{
}

bool FavouriteManager::isFavourite(const QString &backend, const Station &station) const
{
    Q_D(const FavouriteManager);
    return d->data.contains(QPair<QString, Station>(backend, station));
}

QList<QPair<QString, Station> > FavouriteManager::favourites() const
{
    Q_D(const FavouriteManager);
    return d->data;
}

void FavouriteManager::addStation(const QString &backend, const Station &station)
{
    Q_D(FavouriteManager);
    if (isFavourite(backend, station)) {
        return;
    }

    d->data.append(QPair<QString, Station>(backend, station));
    emit favouritesChanged();

    QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
}

void FavouriteManager::removeStation(const QString &backend, const Station &station)
{
    Q_D(FavouriteManager);
    if (!isFavourite(backend, station)) {
        return;
    }

    d->data.removeAll(QPair<QString, Station>(backend, station));
    emit favouritesChanged();

    QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
}

bool FavouriteManager::event(QEvent *event)
{
    Q_D(FavouriteManager);
    if (event->type() == QEvent::UpdateRequest) {
        d->save();
        return true;
    }

    return QObject::event(event);
}

}

}

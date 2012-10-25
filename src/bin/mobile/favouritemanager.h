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

#ifndef PUBLICTRANSPORTATION_GUI_FAVOURITEMANAGER_H
#define PUBLICTRANSPORTATION_GUI_FAVOURITEMANAGER_H

/**
 * @file favouritemanager.h
 * @short Definition of PublicTransportation::Gui::FavouriteManager
 */

#include <QtCore/QObject>
#include <QtCore/QPair>

namespace PublicTransportation
{

class Station;
namespace Gui
{

class FavouriteManagerPrivate;

/**
 * @brief Favourite manager
 *
 * This class is used to provide a list of favourites
 * stations. It stores the list as an XML document,
 * given a name, and takes cares of loading or saving
 * operations.
 *
 * Favourites are stored in QDesktopServices::DataLocation.
 *
 * The list of favourites is given as a pair of data,
 * containing a backend identifier, associated to
 * the requested station.
 *
 * Checking if a station is a favourite can be done
 * with isFavourite(), while getting them is done with
 * favourites().
 *
 * Adding and removing a station can be done with
 * - addStation()
 * - removeStation()
 */
class FavouriteManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param fileName favourite filename.
     * @param parent parent object.
     */
    explicit FavouriteManager(const QString &fileName, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~FavouriteManager();
    /**
     * @brief If a station is a favourite
     * @param backend backend identifier.
     * @param station station.
     * @return if the station is a favourite.
     */
    bool isFavourite(const QString &backend, const Station &station) const;
    /**
     * @brief The list of favourites
     * @return the list of favourites.
     */
    QList<QPair<QString, Station> > favourites() const;
public Q_SLOTS:
    /**
     * @brief Add station
     * @param backend backend identifier.
     * @param station station.
     */
    void addStation(const QString &backend, const Station &station);
    /**
     * @brief Remove station
     * @param backend backend identifier.
     * @param station station.
     */
    void removeStation(const QString &backend, const Station &station);
Q_SIGNALS:
    /**
     * @brief Favourites changed
     */
    void favouritesChanged();
protected:
    /**
     * @brief Reimplementation of event
     * @param event event.
     * @return if the event was processed.
     */
    virtual bool event(QEvent *event);
    /**
     * @brief D-pointer
     */
    QScopedPointer<FavouriteManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FavouriteManager)
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_FAVOURITEMANAGER_H

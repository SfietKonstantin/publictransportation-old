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

#include <QtCore/QObject>
#include <QtCore/QPair>

namespace PublicTransportation
{

class Station;
namespace Gui
{

class FavouriteManagerPrivate;
class FavouriteManager : public QObject
{
    Q_OBJECT
public:
    explicit FavouriteManager(const QString &fileName, QObject *parent = 0);
    virtual ~FavouriteManager();
    bool isFavourite(const QString &backend, const Station &station) const;
    QList<QPair<QString, Station> > favourites() const;
public Q_SLOTS:
    void addStation(const QString &backend, const Station &station);
    void removeStation(const QString &backend, const Station &station);
Q_SIGNALS:
    void favouritesChanged();
protected:
    virtual bool event(QEvent *event);
    QScopedPointer<FavouriteManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FavouriteManager)
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_FAVOURITEMANAGER_H

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

#ifndef PUBLICTRANSPORTATION_PROVIDERPLUGINTESTHELPER_H
#define PUBLICTRANSPORTATION_PROVIDERPLUGINTESTHELPER_H

#include <QtCore/QObject>
#include "provider/providerpluginobject.h"

namespace PublicTransportation
{

class ProviderPluginTestHelper : public ProviderPluginObject
{
    Q_OBJECT
    Q_INTERFACES(PublicTransportation::ProviderPluginInterface)
public:
    explicit ProviderPluginTestHelper(QObject *parent = 0);
    virtual ~ProviderPluginTestHelper();
    virtual QStringList capabilities() const;
    virtual QList<PublicTransportation::Company> listCompanies() const;
    virtual QList<Line> listLines(const Company &company) const;
    virtual QList<Journey> listJourneys(const Company &company, const Line &line) const;
    virtual QList<Station> listStations(const Company &company, const Line &line,
                                        const Journey &journey) const;
};

}


#endif // PUBLICTRANSPORTATION_PROVIDERPLUGINTESTHELPER_H
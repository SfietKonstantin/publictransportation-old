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

#ifndef PUBLICTRANSPORTATION_GUI_XMLCONVERSIONHELPER_H
#define PUBLICTRANSPORTATION_GUI_XMLCONVERSIONHELPER_H

#include <QtCore/QVariantMap>

class QDomDocument;
class QDomElement;
namespace PublicTransportation
{

class Station;

namespace Gui
{

class XmlConversionHelper
{
public:
    static QDomElement toXml(const QVariantMap &variantMap, const QString &tagName,
                             QDomDocument *document);
    static QDomElement toXml(const Station &station, QDomDocument *document);
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_XMLCONVERSIONHELPER_H

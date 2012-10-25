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

/**
 * @file xmlconversionhelper.h
 * @short Definition of PublicTransportation::Gui::XmlConversionHelper
 */

#include <QtCore/QVariantMap>

class QDomDocument;
class QDomElement;
namespace PublicTransportation
{

class Station;

namespace Gui
{

/**
 * @brief Helper class managing serialization in XML
 *
 * This class is used to serialize data in some complex
 * data objects like a PublicTransportation::Station in
 * XML, in order to be stored and reused.
 *
 * This class provides static methods to deal with these
 * conversions.
 */
class XmlConversionHelper
{
public:
    /**
     * @brief Convert a variant map to XML
     * @param variantMap variant map to convert.
     * @param tagName tag name of the root element.
     * @param document document used to create elements.
     * @return the variant map as an XML element.
     */
    static QDomElement toXml(const QVariantMap &variantMap, const QString &tagName,
                             QDomDocument *document);
    /**
     * @brief Convert a XML element to a variant map
     * @param element XML element to convert.
     * @return the XML element as a variant map.
     */
    static QVariantMap fromXmlToVariantMap(const QDomElement &element);
    /**
     * @brief Convert a PublicTransportation::Station to XML
     * @param station station to convert.
     * @param document document used to create elements.
     * @return the station as an XML element.
     */
    static QDomElement toXml(const Station &station, QDomDocument *document);
    /**
     * @brief Convert a XML element to a PublicTransportation::Station
     * @param element XML element to convert.
     * @return the XML element as a station.
     */
    static Station fromXmlToStation(const QDomElement &element);
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_XMLCONVERSIONHELPER_H

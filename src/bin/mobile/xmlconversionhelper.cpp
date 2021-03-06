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
 * @file xmlconversionhelper.cpp
 * @short Implementation of PublicTransportation::Gui::XmlConversionHelper
 */

#include "xmlconversionhelper.h"

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "common/station.h"

/**
 * @brief VARIANT_MAP_ENTRY_TAG
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *VARIANT_MAP_ENTRY_TAG = "map_entry";
/**
 * @brief VARIANT_MAP_ENTRY_KEY_ATTRIBUTE
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *VARIANT_MAP_ENTRY_KEY_ATTRIBUTE = "key";
/**
 * @brief VARIANT_MAP_ENTRY_TYPE_ATTRIBUTE
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *VARIANT_MAP_ENTRY_TYPE_ATTRIBUTE = "type";
/**
 * @brief VARIANT_MAP_ENTRY_VALUE_ATTRIBUTE
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *VARIANT_MAP_ENTRY_VALUE_ATTRIBUTE = "value";

/**
 * @brief TRANSPORTATION_OBJECT_DISAMBIGUATION_TAG
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *TRANSPORTATION_OBJECT_DISAMBIGUATION_TAG = "disambiguation";
/**
 * @brief TRANSPORTATION_OBJECT_PROPERTIES_TAG
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *TRANSPORTATION_OBJECT_PROPERTIES_TAG = "properties";
/**
 * @brief TRANSPORTATION_OBJECT_NAME_ATTRIBUTE
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *TRANSPORTATION_OBJECT_NAME_ATTRIBUTE = "name";

/**
 * @brief STATION_TAG
 *
 * Used in PublicTransportation::Gui::XmlConversionHelper.
 */
static const char *STATION_TAG = "station";

namespace PublicTransportation
{

namespace Gui
{

QDomElement XmlConversionHelper::toXml(const QVariantMap &variantMap, const QString &tagName,
                                       QDomDocument *document)
{
    QDomElement element = document->createElement(tagName);
    foreach (QString key, variantMap.keys()) {
        QVariant value = variantMap.value(key);
        const char *typeName = QVariant::typeToName(value.type());
        QDomElement entryElement = document->createElement(VARIANT_MAP_ENTRY_TAG);
        entryElement.setAttribute(VARIANT_MAP_ENTRY_KEY_ATTRIBUTE, key);
        entryElement.setAttribute(VARIANT_MAP_ENTRY_TYPE_ATTRIBUTE, QString::fromAscii(typeName));
        entryElement.setAttribute(VARIANT_MAP_ENTRY_VALUE_ATTRIBUTE, value.toString());
        element.appendChild(entryElement);
    }

    return element;
}

QVariantMap XmlConversionHelper::fromXmlToVariantMap(const QDomElement &element)
{
    QVariantMap variantMap;
    QDomElement entryElement = element.firstChildElement(VARIANT_MAP_ENTRY_TAG);
    while (!entryElement.isNull()) {
        QString key = entryElement.attribute(VARIANT_MAP_ENTRY_KEY_ATTRIBUTE);
        QByteArray type = entryElement.attribute(VARIANT_MAP_ENTRY_TYPE_ATTRIBUTE).toAscii();
        QVariant value = entryElement.attribute(VARIANT_MAP_ENTRY_VALUE_ATTRIBUTE);
        QVariant::Type typeId = QVariant::nameToType(type);
        value.convert(typeId);
        variantMap.insert(key, value);
        entryElement = entryElement.nextSiblingElement(VARIANT_MAP_ENTRY_TAG);
    }
    return variantMap;
}

QDomElement XmlConversionHelper::toXml(const Station &station, QDomDocument *document)
{
    QDomElement element = document->createElement(STATION_TAG);
    element.appendChild(toXml(station.disambiguation(), TRANSPORTATION_OBJECT_DISAMBIGUATION_TAG,
                        document));

    element.setAttribute(TRANSPORTATION_OBJECT_NAME_ATTRIBUTE, station.name());

    element.appendChild(toXml(station.properties(), TRANSPORTATION_OBJECT_PROPERTIES_TAG,
                        document));

    return element;
}

Station XmlConversionHelper::fromXmlToStation(const QDomElement &element)
{
    QString name = element.attribute(TRANSPORTATION_OBJECT_NAME_ATTRIBUTE);
    QDomElement disambiguationElement
            = element.firstChildElement(TRANSPORTATION_OBJECT_DISAMBIGUATION_TAG);
    QDomElement propertiesElement = element.firstChildElement(TRANSPORTATION_OBJECT_PROPERTIES_TAG);
    QVariantMap disambiguation = fromXmlToVariantMap(disambiguationElement);
    QVariantMap properties = fromXmlToVariantMap(propertiesElement);

    return Station(disambiguation, name, properties);
}


}

}

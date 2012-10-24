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

#include "xmlconversionhelper.h"

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "common/station.h"

static const char *VARIANT_MAP_ENTRY_TAG = "map_entry";
static const char *VARIANT_MAP_ENTRY_KEY_ATTRIBUTE = "key";
static const char *VARIANT_MAP_ENTRY_TYPE_ATTRIBUTE = "type";
static const char *VARIANT_MAP_ENTRY_VALUE_ATTRIBUTE = "value";

static const char *TRANSPORTATION_OBJECT_DISAMBIGUATION_TAG = "disambiguation";
static const char *TRANSPORTATION_OBJECT_PROPERTIES_TAG = "properties";
static const char *TRANSPORTATION_OBJECT_NAME_ATTRIBUTE = "name";

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


}

}

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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_LANGUAGEHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_LANGUAGEHELPER_H

/**
 * @file languagehelper.h
 * @short Definition of PublicTransportation::PluginHelper::LanguageHelper
 */

#include "publictransportationpluginhelper_global.h"

#include <QtCore/QString>

namespace PublicTransportation
{

namespace PluginHelper
{

/**
 * @brief Language helper
 *
 * This class provide methods to help dealing with languages.
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT LanguageHelper
{
public:
    /**
     * @brief Remove accents
     * @param string input string.
     * @return string without accents.
     */
    static QString unaccent(const QString &string);
    /**
     * @brief Unstrip HTML accents
     * @param string string with stripped HTML accents.
     * @return string with unstripped HTML accents.
     */
    static QString unstripHtmlAccents(const QString &string);
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_LANGUAGEHELPER_H

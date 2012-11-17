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
 * @file languagehelper.cpp
 * @short Implementation of PublicTransportation::PluginHelper::LanguageHelper
 */

#include "languagehelper.h"

namespace PublicTransportation
{

namespace PluginHelper
{

QString LanguageHelper::unaccent(const QString &string)
{
    QString canonicalForm = string.toLower().normalized(QString::NormalizationForm_D);
    QString returnedString;
    foreach (QChar c, canonicalForm) {
        if (c.category() != QChar::Mark_NonSpacing &&
            c.category() != QChar::Mark_SpacingCombining) {
              returnedString.append(c);
         }
    }

    return returnedString;
}

QString LanguageHelper::unstripHtmlAccents(const QString &string)
{
    QString newString = string;
    newString.replace("&Agrave;", QString::fromUtf8("À"));
    newString.replace("&agrave;", QString::fromUtf8("à"));
    newString.replace("&Acirc;", QString::fromUtf8("Â"));
    newString.replace("&acirc;", QString::fromUtf8("â"));
    newString.replace("&Auml;", QString::fromUtf8("Ä"));
    newString.replace("&auml;", QString::fromUtf8("ä"));
    newString.replace("&Egrave;", QString::fromUtf8("È"));
    newString.replace("&egrave;", QString::fromUtf8("è"));
    newString.replace("&Eacute;", QString::fromUtf8("É"));
    newString.replace("&eacute;", QString::fromUtf8("é"));
    newString.replace("&Ecirc;", QString::fromUtf8("Ê"));
    newString.replace("&ecirc;", QString::fromUtf8("ê"));
    newString.replace("&Euml;", QString::fromUtf8("Ë"));
    newString.replace("&euml;", QString::fromUtf8("ë"));
    newString.replace("&Icirc;", QString::fromUtf8("Î"));
    newString.replace("&icirc;", QString::fromUtf8("î"));
    newString.replace("&Iuml;", QString::fromUtf8("Ï"));
    newString.replace("&iuml;", QString::fromUtf8("ï"));
    newString.replace("&Ocirc;", QString::fromUtf8("Ô"));
    newString.replace("&ocirc;", QString::fromUtf8("ô"));
    newString.replace("&Ouml;", QString::fromUtf8("Ö"));
    newString.replace("&ouml;", QString::fromUtf8("ö"));
    newString.replace("&Ugrave;", QString::fromUtf8("Ù"));
    newString.replace("&ugrave;", QString::fromUtf8("ù"));
    newString.replace("&Ucirc;", QString::fromUtf8("Û"));
    newString.replace("&ucirc;", QString::fromUtf8("û"));
    newString.replace("&Uuml;", QString::fromUtf8("Ü"));
    newString.replace("&uuml;", QString::fromUtf8("ü"));
    newString.replace("&Yuml;", QString::fromUtf8("Ÿ"));
    newString.replace("&yuml;", QString::fromUtf8("ÿ"));

    return newString;
}

}

}

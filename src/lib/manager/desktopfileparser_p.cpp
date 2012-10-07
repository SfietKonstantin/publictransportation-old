/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file desktopfileparser_p.cpp
 * @short Implementation of Widgets::Provider::PackageManager::DesktopFileParser
 */

#include "desktopfileparser_p.h"

#include <QtCore/QSettings>

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for Widgets::Provider::PackageManager::DesktopFileParser
 */
class DesktopFileParserPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param file the file to parse.
     */
    DesktopFileParserPrivate(const QString &file);
    /**
     * @internal
     * @brief Get the true key
     *
     * This method is used to get the true key,
     * provided a key, and a language code.
     *
     * The true key will be in the following form:
     * key[lang].
     *
     * If no language code is passed, the passed
     * key is returned.
     *
     * @param key key.
     * @param lang language code.
     * @return true key.
     */
    static QString trueKey(const QString &key, const QString &lang);

    /**
     * @internal
     * @brief QSettings
     *
     * This QSettings instance is used to parse
     * the desktop file.
     */
    QSettings settings;
    /**
     * @internal
     * @brief The file being parsed
     */
    QString file;
};

DesktopFileParserPrivate::DesktopFileParserPrivate(const QString &file):
    settings(file, QSettings::IniFormat)
{
    settings.setIniCodec("UTF-8");
    this->file = file;
}

QString DesktopFileParserPrivate::trueKey(const QString &key, const QString &lang)
{
    if (lang.isEmpty()) {
        return key;
    } else {
        QString trueKey = QString("%1[%2]").arg(key).arg(lang);
        return trueKey;
    }
}

////// End of private class //////

DesktopFileParser::DesktopFileParser(const QString &file):
    d_ptr(new DesktopFileParserPrivate(file))
{
}

DesktopFileParser::~DesktopFileParser()
{
}

QString DesktopFileParser::file() const
{
    Q_D(const DesktopFileParser);
    return d->file;
}

void DesktopFileParser::beginGroup(const QString &group)
{
    Q_D(DesktopFileParser);
    d->settings.beginGroup(group);
}

void DesktopFileParser::endGroup()
{
    Q_D(DesktopFileParser);
    d->settings.endGroup();
}

QStringList DesktopFileParser::keys() const
{
    Q_D(const DesktopFileParser);
    return d->settings.childKeys();
}

bool DesktopFileParser::contains(const QString &key, const QString &lang) const
{
    Q_D(const DesktopFileParser);
    return d->settings.contains(d->trueKey(key, lang));
}

QVariant DesktopFileParser::value(const QString &key, const QString &lang) const
{
    Q_D(const DesktopFileParser);
    return d->settings.value(d->trueKey(key, lang));
}

}

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

#ifndef PUBLICTRANSPORTATION_DESKTOPFILEPARSER_P_H
#define PUBLICTRANSPORTATION_DESKTOPFILEPARSER_P_H

// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.


/**
 * @internal
 * @file desktopfileparser_p.h
 * @short Definition of PublicTransportation::DesktopFileParser
 */

#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

namespace PublicTransportation
{

class DesktopFileParserPrivate;

/**
 * @internal
 * @brief A desktop file parser
 *
 * This class is used to parse desktop files,
 * that are INI-like files. It wraps a QSettings
 * and provides some more capabilities, like
 * finding language key.
 */
class DesktopFileParser
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param file desktop file to parse.
     */
    explicit DesktopFileParser(const QString &file);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DesktopFileParser();
    /**
     * @internal
     * @brief Desktop file to parse
     * @return desktop file to parse.
     */
    QString file() const;
    /**
     * @internal
     * @brief Begin group
     *
     * This method is used to set the current group
     * that is used to parse the desktop file.
     *
     * @param group name of the group.
     */
    void beginGroup(const QString &group);
    /**
     * @internal
     * @brief End group
     *
     * This method is used to unset the current group
     * that is used to parse the desktop file.
     */
    void endGroup();
    /**
     * @internal
     * @brief Available keys
     *
     * This method is used to get the available keys
     * in the current group.
     *
     * @return available keys.
     */
    QStringList keys() const;
    /**
     * @internal
     * @brief If the desktop file contains a key
     *
     * This method is used to check if the current group
     * contains a key, with an associated language key.
     *
     * @param key the key to check.
     * @param lang the language key associated to the key.
     * @return if the desktop file contains the key.
     */
    bool contains(const QString &key, const QString &lang = QString()) const;
    /**
     * @internal
     * @brief Value
     *
     * This method is used to get the value associated to
     * a key in the current group, with an associated language
     * key.
     *
     * @param key the key to retrieve.
     * @param lang the language key associated to the key.
     * @return value associated to the key and language key.
     */
    QVariant value(const QString &key, const QString &lang = QString()) const;
protected:
    /**
     * @internal
     * @brief D-pointer
     */
    const QScopedPointer<DesktopFileParserPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DesktopFileParser)
};

}

#endif // PUBLICTRANSPORTATION_DESKTOPFILEPARSER_P_H

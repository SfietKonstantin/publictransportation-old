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

#ifndef PUBLICTRANSPORTATION_GUI_SETTINGSHELPER_H
#define PUBLICTRANSPORTATION_GUI_SETTINGSHELPER_H

/**
 * @file settingshelper.h
 * @short Definition of PublicTransportation::Gui::SettingsHelper
 */

#include <QtCore/QObject>

namespace PublicTransportation
{

namespace Gui
{

class SettingsHelperPrivate;

/**
 * @brief Helper class for managing settings
 *
 * This class provides a QML enabled interface to
 * basic settings, like if the theme is inverted.
 */
class SettingsHelper : public QObject
{
    Q_OBJECT
    /**
     * @short If the theme is inverted
     */
    Q_PROPERTY(bool themeInverted READ isThemeInverted WRITE setThemeInverted
               NOTIFY themeInvertedChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit SettingsHelper(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~SettingsHelper();
    /**
     * @brief If the theme is inverted
     * @return if the theme is inverted.
     */
    bool isThemeInverted() const;
public Q_SLOTS:
    /**
     * @brief Set if the theme is inverted
     * @param themeInverted if the theme is inverted.
     */
    void setThemeInverted(bool themeInverted);
signals:
    /**
     * @brief If the theme is inverted changed
     */
    void themeInvertedChanged();
protected:
    /**
     * @short D-pointer
     */
    QScopedPointer<SettingsHelperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(SettingsHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_SETTINGSHELPER_H

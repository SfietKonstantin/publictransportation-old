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
 * @file settingshelper.cpp
 * @short Implementation of PublicTransportation::Gui::SettingsHelper
 */

#include "settingshelper.h"
#include <QtCore/QSettings>

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::SettingsHelper
 */
class SettingsHelperPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    SettingsHelperPrivate(SettingsHelper *q);
    /**
     * @internal
     * @brief Load settings
     */
    void loadSettings();
    /**
     * @internal
     * @brief Save settings
     */
    void saveSettings();
    /**
     * @internal
     * @brief If the theme is inverted
     */
    bool themeInverted;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    SettingsHelper * const q_ptr;
    Q_DECLARE_PUBLIC(SettingsHelper)
};

SettingsHelperPrivate::SettingsHelperPrivate(SettingsHelper *q):
    q_ptr(q)
{
}

void SettingsHelperPrivate::loadSettings()
{
    QSettings settings;
    themeInverted = settings.value("ui/themeInverted", false).toBool();
}

void SettingsHelperPrivate::saveSettings()
{
    QSettings settings;
    settings.setValue("ui/themeInverted", themeInverted);
}


////// End of private class //////

SettingsHelper::SettingsHelper(QObject *parent) :
    QObject(parent), d_ptr(new SettingsHelperPrivate(this))
{
    Q_D(SettingsHelper);
    d->loadSettings();
}

SettingsHelper::~SettingsHelper()
{
    Q_D(SettingsHelper);
    d->saveSettings();
}

bool SettingsHelper::isThemeInverted() const
{
    Q_D(const SettingsHelper);
    return d->themeInverted;
}

void SettingsHelper::setThemeInverted(bool themeInverted)
{
    Q_D(SettingsHelper);
    if (d->themeInverted != themeInverted) {
        d->themeInverted = themeInverted;
        emit themeInvertedChanged();
    }
}

}

}

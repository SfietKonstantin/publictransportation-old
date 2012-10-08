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

import QtQuick 1.0
import "UiConstants.js" as Ui

// This is a simple horizontal separator
// that have the Harmattan look and feel
//
// Width, height do not need to be set for
// this item.

BorderImage {
    id: container
    width: parent.width - 2 * Ui.MARGIN_DEFAULT; height: 2
    anchors.horizontalCenter: parent.horizontalCenter
    source: "image://theme/meegotouch-separator" + (theme.inverted ? "-inverted" : "") +
            "-background-horizontal"
    border {left: 0; top: 2; right: 0; bottom: 0}
}

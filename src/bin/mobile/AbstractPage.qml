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

import QtQuick 1.1
import com.nokia.meego 1.0
import "UiConstants.js" as Ui

Page {
    id: container
    property string title
    property color headerColor: "white"
    property color headerLabelColor: "black"
    property alias content: content.children
    signal back()

    Item {
        id: header
        anchors.top: parent.top
        anchors.left: parent.left; anchors.right: parent.right
        height: window.inPortrait ? Ui.HEADER_HEIGHT_PORTRAIT : Ui.HEADER_HEIGHT_LANDSCAPE

        Rectangle {
            anchors.fill: parent
            visible: !theme.inverted
            color: container.headerColor
        }

        Label {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            verticalAlignment: Text.AlignVCenter
            text: title
            color: theme.inverted ? "white" : container.headerLabelColor
            font.pixelSize: Ui.FONT_SIZE_XLARGE
        }
    }

    HorizontalSeparator {
        id: horizontalSeparator
        anchors.top: header.bottom
        visible: theme.inverted
    }

    Item {
        id: content
        anchors.top: horizontalSeparator.bottom;
        anchors.topMargin: theme.inverted ? Ui.MARGIN_DEFAULT : 0
        anchors.left: parent.left; anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}

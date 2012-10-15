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

import QtQuick 1.1
import com.nokia.meego 1.0
import "UiConstants.js" as Ui

AbstractPage {

    headerColor: "#006E29"
    headerLabelColor: "white"
    title: qsTr("About")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: window.pageStack.pop()
        }
    }
    content: Flickable {
        id: flickable
        clip: true
        anchors.fill: parent
        contentHeight: Ui.MARGIN_DEFAULT + icon.height
                       + Ui.MARGIN_DEFAULT + aboutText.height
                       + Ui.MARGIN_DEFAULT + copyrightText.height
        contentWidth: parent.width

        Image {
            id: icon
            source: ICON_FILE
            width: 120
            height: 120
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_LARGE
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: aboutText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: icon.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            text: qsTr("publictransportation is an attempt to give the user the \
best transportation application. Instead of multiple clients that do not share anything in \
common (no consistency in UI, in navigation etc.), publictransportation brings an unified \
UI for different information sources about different transportation companies.")
        }

        Label {
            id: copyrightText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: aboutText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            text: "(C) 2012 - Lucien XU"
        }
    }
}

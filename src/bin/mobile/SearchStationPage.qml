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
    title: qsTr("Search stations")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                window.pageStack.pop()
            }
        }
    }
    onVisibleChanged: {
        if (!visible) {
            SearchStationModelInstance.search("")
            searchField.text = ""
        }
    }

    content: Item {
        anchors.fill: parent

        TextField {
            id: searchField
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            placeholderText: qsTr("Search for a station")
            onTextChanged: SearchStationModelInstance.search(text)
        }

        ListView {
            anchors.top: searchField.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: parent.bottom
            clip: true
            model: SearchStationModelInstance
            delegate: ClickableEntry {
                text: model.name
                subText: model.providerName
            }
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: SearchStationModelInstance.updating
            running: SearchStationModelInstance.updating
            platformStyle: BusyIndicatorStyle {size: "large"}
        }
    }
}

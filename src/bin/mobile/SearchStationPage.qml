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
    id: page
    property bool shouldClean: false
    headerColor: "#006E29"
    headerLabelColor: "white"
    title: qsTr("Search stations")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                shouldClean = true
                window.pageStack.pop()
            }
        }
    }
    onVisibleChanged: {
        if (!visible && shouldClean) {
            SearchStationModelInstance.reset()
            searchField.text = ""
            shouldClean = false
        }
    }

    content: Item {
        anchors.fill: parent

        TextField {
            id: searchField
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_SMALL
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            placeholderText: qsTr("Search for a station")
            onTextChanged: SearchStationModelInstance.search(text)
        }

        ListView {
            anchors.top: searchField.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: parent.bottom
            opacity: !SearchStationModelInstance.loading ? 1 : 0.5
            clip: true
            model: SearchStationModelInstance
            delegate: ClickableEntry {
                text: model.name
                subText: model.providerName
                enabled: model.supportJourneysFromStation
                icon: !model.favourite ? "" : "image://theme/icon-m-common-favorite-mark"
                                              + (theme.inverted ? "-inverse" : "")
                onClicked: {
                    SearchStationModelInstance.requestJourneysFromStation(model.index)
                    journeysFromStationPage.station = model.name
                    journeysFromStationPage.provider = model.providerName
                    window.pageStack.push(journeysFromStationPage)
                }
            }

            ScrollDecorator { flickableItem: parent }
        }



        BusyIndicator {
            anchors.centerIn: parent
            visible: SearchStationModelInstance.loading && page.visible
            running: SearchStationModelInstance.loading
            platformStyle: BusyIndicatorStyle {size: "large"}
        }
    }

    JourneysFromStationPage {id: journeysFromStationPage}
}

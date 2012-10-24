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
    property string station
    property string provider
    property bool displayCategories: true
    headerColor: "#006E29"
    headerLabelColor: "white"
    title: qsTr("Journeys")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: window.pageStack.pop()
        }

        ToolIcon {
            iconId: JourneysFromStationModelInstance.favourite ? "toolbar-favorite-mark"
                                                               : "toolbar-favorite-unmark"
            onClicked: JourneysFromStationModelInstance.favourite =
                       !JourneysFromStationModelInstance.favourite
        }

        ToolIcon {
            iconId: "toolbar-view-menu"
            onClicked: menu.open()
        }
    }

    content: Item {
        anchors.fill: parent

        Item {
            id: labelItem
            anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
            height: 2 * Ui.MARGIN_DEFAULT + Ui.MARGIN_SMALL + stationText.height
                    + providerText.height

            Label {
                id: stationText
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_SMALL
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: page.station
                font.pixelSize: Ui.FONT_SIZE_XLARGE
                color: !theme.inverted ? Ui.FONT_COLOR_PRIMARY : Ui.FONT_COLOR_INVERTED_PRIMARY
            }

            Label {
                id: providerText
                anchors.top: stationText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: qsTr("Provided by") + " : "  + page.provider
                font.pixelSize: Ui.FONT_SIZE_DEFAULT
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }
        }

        HorizontalSeparator {
            id :horizontalSeparator
            visible: !page.displayCategories
            anchors.top: labelItem.bottom
        }

        ListView {
            id: view
            anchors.top: horizontalSeparator.bottom//; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: parent.bottom
            opacity: !JourneysFromStationModelInstance.loading ? 1 : 0.5
            clip: true
            model: JourneysFromStationModelInstance
            delegate: ClickableEntry {
                preText: "<b>" + model.line + "</b>"
                text: model.name
                enabled: model.supportWaitingTime
                onClicked: {
                    JourneysFromStationModelInstance.requestWaitingTime(model.index)
                    waitingTimePage.station = model.station
                    waitingTimePage.company = model.company
                    waitingTimePage.line = model.line
                    waitingTimePage.journey = model.name
                    window.pageStack.push(waitingTimePage)
                }
            }
            section.property: page.displayCategories ? "line" : ""
            section.delegate: GroupIndicator {
                id: groupIndicator
                text: qsTr("Line") + " " + section
            }

            UpdateHeader {
                id: updateHeader
                view: view
            }

            onMovingChanged: {
                if (!moving && atXBeginning && updateHeader.needUpdate) {
                    JourneysFromStationModelInstance.reload()
                }
                updateHeader.needUpdate = false
            }

            ScrollDecorator { flickableItem: parent }
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: JourneysFromStationModelInstance.loading && page.visible
            running: JourneysFromStationModelInstance.loading
            platformStyle: BusyIndicatorStyle {size: "large"}
        }
    }

    WaitingTimePage {id: waitingTimePage}

    Menu {
        id: menu

        MenuLayout {
            MenuItem {
                text: page.displayCategories ? qsTr("Hide categories") : qsTr("Display categories")
                onClicked: page.displayCategories = !page.displayCategories
            }
        }
    }
}

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
    property string line
    property string journey
    property string company
    headerColor: "#006E29"
    headerLabelColor: "white"
    title: station
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: window.pageStack.pop()
        }
    }

    content: Item {
        anchors.fill: parent

        Item {
            id: labelItem
            anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
            height: 2 * Ui.MARGIN_DEFAULT + Ui.MARGIN_SMALL + companyText.height
                    + lineAndDirectionText.height

            Label {
                id: lineAndDirectionText
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: "<b>" + page.line + "</b>   " + page.journey
                font.pixelSize: Ui.FONT_SIZE_DEFAULT
                color: !theme.inverted ? Ui.FONT_COLOR_PRIMARY : Ui.FONT_COLOR_INVERTED_PRIMARY
            }

            Label {
                id: companyText
                anchors.top: lineAndDirectionText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: page.company
                font.pixelSize: Ui.FONT_SIZE_DEFAULT
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }
        }

        HorizontalSeparator {
            id :horizontalSeparator
            anchors.top: labelItem.bottom
        }

        ListView {
            id: view
            anchors.top: horizontalSeparator.bottom
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: parent.bottom
            opacity: !WaitingTimeModelInstance.loading ? 1 : 0.5
            clip: true
            model: WaitingTimeModelInstance
            delegate: ClickableEntry {
                enabled: false
                preText: model.waitingTime
                text: model.destination
            }

            UpdateHeader {
                id: updateHeader
                view: view
            }

            onMovingChanged: {
                if (!moving && atXBeginning && updateHeader.needUpdate) {
                    WaitingTimeModelInstance.reload()
                }
                updateHeader.needUpdate = false
            }

            ScrollDecorator { flickableItem: parent }
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: WaitingTimeModelInstance.loading && page.visible
            running: WaitingTimeModelInstance.loading
            platformStyle: BusyIndicatorStyle {size: "large"}
        }
    }
}

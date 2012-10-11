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
    property string text
    property string subText
    property bool displayCategories: true
    headerColor: "#006E29"
    headerLabelColor: "white"
    title: qsTr("Journeys")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                window.pageStack.pop()
            }
        }

        ToolIcon {
            iconId: page.displayCategories ? "toolbar-list-selected" : "toolbar-list"
            onClicked: {
                page.displayCategories = !page.displayCategories
            }
        }
    }

    content: Item {
        anchors.fill: parent

        Item {
            id: labelItem
            anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
            height: 3 * Ui.MARGIN_DEFAULT + text.height + subText.height

            Label {
                id: text
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: page.text
                font.pixelSize: Ui.FONT_SIZE_XLARGE
                color: !theme.inverted ? Ui.FONT_COLOR_PRIMARY : Ui.FONT_COLOR_INVERTED_PRIMARY
            }

            Label {
                id: subText
                anchors.top: text.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: page.subText
                font.pixelSize: Ui.FONT_SIZE_DEFAULT
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }
        }

        ListView {
            anchors.top: labelItem.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: parent.bottom
            clip: true
            model: JourneysFromStationModelInstance
            delegate: ClickableEntry {
                text: "<b>" + model.line + "</b> " + model.name
            }
            section.property: page.displayCategories ? "line" : ""
            section.delegate: GroupIndicator {
                id: groupIndicator
                text: qsTr("Line") + " " + section
        }

            ScrollDecorator { flickableItem: parent }
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: JourneysFromStationModelInstance.updating && page.visible
            running: JourneysFromStationModelInstance.updating
            platformStyle: BusyIndicatorStyle {size: "large"}
        }
    }
}

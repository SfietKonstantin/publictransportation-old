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
    property string line
    property string destination
    property string company
    headerColor: "#006E29"
    headerLabelColor: "white"
    title: "<b>" + page.line + "</b>   " + page.destination
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
            height: 2 * Ui.MARGIN_DEFAULT + Ui.MARGIN_SMALL + lineAndDestinationText.height
                    + companyText.height

            Label {
                id: lineAndDestinationText
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_SMALL
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: "<b>" + page.line + "</b>   " + page.destination
                font.pixelSize: Ui.FONT_SIZE_XLARGE
                color: !theme.inverted ? Ui.FONT_COLOR_PRIMARY : Ui.FONT_COLOR_INVERTED_PRIMARY
            }

            Label {
                id: companyText
                anchors.top: lineAndDestinationText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                text: page.company
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
            opacity: !StationsFromJourneyModelInstance.loading ? 1 : 0.5
            clip: true
            model: StationsFromJourneyModelInstance
            delegate: StationEntry {
                text: model.station
                terminus: model.terminus
                previousConnectorType: model.previousConnectorType
                nextConnectorType: model.nextConnectorType
            }
            ScrollDecorator { flickableItem: parent }
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: StationsFromJourneyModelInstance.loading && page.visible
            running: StationsFromJourneyModelInstance.loading
            platformStyle: BusyIndicatorStyle {size: "large"}
        }
    }
}

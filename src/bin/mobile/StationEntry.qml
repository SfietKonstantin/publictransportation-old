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
import org.SfietKonstantin.publictransportation 1.0
import "UiConstants.js" as Ui

Item {
    id: container
    property bool terminus: false
    property int previousConnectorType: StationsFromJourneyModel.ConnectorInvisible
    property int nextConnectorType: StationsFromJourneyModel.ConnectorInvisible
    property color color: "#054700"
    property alias text: text.text

    height: Ui.LIST_ITEM_HEIGHT_DEFAULT
    width: parent.width

    Rectangle {
        id: previousConenctor
        anchors.horizontalCenter: dot.horizontalCenter
        anchors.bottom: dot.top; anchors.bottomMargin: - Ui.MARGIN_LARGE
        width: Ui.MARGIN_SMALL
        height: Ui.MARGIN_LARGE * 2
        color: container.color
        visible: container.previousConnectorType != StationsFromJourneyModel.ConnectorInvisible
    }

    Rectangle {
        id: dot
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        width: height
        height: parent.height - 2 * Ui.MARGIN_LARGE
        smooth: true
        radius: !container.terminus ? width / 2 : 0
        color: container.color
    }

    Rectangle {
        id: nextConenctor
        anchors.horizontalCenter: dot.horizontalCenter
        anchors.top: dot.bottom; anchors.topMargin: - Ui.MARGIN_LARGE
        width: Ui.MARGIN_SMALL
        height: Ui.MARGIN_LARGE * 2
        color: container.color
        visible: container.nextConnectorType != StationsFromJourneyModel.ConnectorInvisible
    }

    Label {
        id: text
        anchors.left: dot.right; anchors.leftMargin: Ui.MARGIN_LARGE
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        maximumLineCount: 1
    }

}

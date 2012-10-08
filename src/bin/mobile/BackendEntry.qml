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
import org.SfietKonstantin.publictransportation 1.0

Item
{
    id: container
    signal clicked
    signal pressAndHold
    signal checked(bool checked)
    property int status
    property alias text: mainText.text
    property alias subText: subText.text

    height: Ui.LIST_ITEM_HEIGHT_DEFAULT
    width: parent.width

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    Image {
        id: icon
        function imageSource() {
            switch(container.status) {
            case BackendModel.Stopped:
                return "image://theme/icon-m-common-presence-offline"
            case BackendModel.Launching:
                return "image://theme/icon-m-common-presence-away"
            case BackendModel.Launched:
                return "image://theme/icon-m-common-presence-online"
            case BackendModel.Stopping:
                return "image://theme/icon-m-common-presence-away"
            default:
                return "image://theme/icon-m-common-fault"
            }
        }

        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        width: Ui.ICON_SIZE_SMALL
        height: Ui.ICON_SIZE_SMALL
        source: imageSource()
        asynchronous: true
    }

    Item {
        id: textContainer
        anchors.left: icon.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: controlSwitch.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        height: subText.text != "" ? mainText.height + Ui.MARGIN_XSMALL + subText.height :
                                         mainText.height

        Label {
            id: mainText
            anchors.left: parent.left; anchors.right: parent.right
            platformStyle: LabelStyle {
                fontPixelSize: Ui.FONT_SIZE_MLARGE
            }
        }

        Label {
            id: subText
            anchors.top: mainText.bottom; anchors.topMargin: Ui.MARGIN_XSMALL
            anchors.left: parent.left; anchors.right: parent.right
            elide: Text.ElideRight
            platformStyle: LabelStyle {
                fontPixelSize: Ui.FONT_SIZE_SMALL
                textColor: theme.inverted ? Ui.FONT_COLOR_INVERTED_SECONDARY :
                                            Ui.FONT_COLOR_SECONDARY
            }
        }
    }


    MouseArea {
        id: mouseArea
        anchors.left: parent.left
        anchors.right: controlSwitch.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.top: parent.top; anchors.bottom: parent.bottom
        onClicked: container.clicked()
        onPressAndHold: container.pressAndHold()
    }

    Switch {
        id: controlSwitch
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        onCheckedChanged: container.checked(controlSwitch.checked)
    }
}

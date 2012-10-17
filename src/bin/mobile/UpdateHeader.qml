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

Item {
    id: updateHeader
    property Item view
    property bool needUpdate: false
    width: view.width
    height: updateHeaderContent.height + updateHeaderSeparator.height
    y: -view.contentY - height

    Item {
        id: updateHeaderContent
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: updateHeaderSeparator.top
        height: Ui.LIST_ITEM_HEIGHT_DEFAULT

        Item {
            id: updateHeaderIcon
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.verticalCenter: parent.verticalCenter
            width: 40; height: 40

            Image {
                anchors.fill: parent
                source: "image://theme/icon-m-toolbar-down"
                        + (theme.inverted ? "-white" : "")
                rotation: !updateHeader.needUpdate ? 0 : 180
                Behavior on rotation {
                    NumberAnimation {duration: Ui.ANIMATION_DURATION_XFAST}
                }
            }
        }

        Label {
            anchors.top: parent.top;
            anchors.bottom: parent.bottom
            anchors.left: updateHeaderIcon.right; anchors.leftMargin: Ui.MARGIN_LARGE
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            text: !updateHeader.needUpdate ? qsTr("Pull down to update")
                                           : qsTr("Release to update")
            verticalAlignment: Text.AlignVCenter
        }

    }

    HorizontalSeparator {
        id: updateHeaderSeparator
        anchors.bottom: parent.bottom
    }
    onYChanged: {
        if (y > Ui.LIST_ITEM_HEIGHT_DEFAULT / 2) {
            needUpdate = true
        }
    }
}

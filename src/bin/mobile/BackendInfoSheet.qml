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

Sheet {
    rejectButtonText: qsTr("Close")
    content: Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: width
        contentHeight: Ui.MARGIN_DEFAULT + copyrightGroup.height + Ui.MARGIN_DEFAULT
                       + copyright.height

        GroupIndicator {
            id: copyrightGroup
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            text: qsTr("Copyright")
        }

        Label {
            id: copyright
            anchors.top: copyrightGroup.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            text: BackendCopyrightManagerInstance.copyright
        }

        GroupIndicator {
            id: capabilitiesGroup
            anchors.top: copyright.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            text: qsTr("Provider capabilities")
        }

        Label {
            id: capabilities
            anchors.top: capabilitiesGroup.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            text: BackendCopyrightManagerInstance.capabilities
        }
    }
}

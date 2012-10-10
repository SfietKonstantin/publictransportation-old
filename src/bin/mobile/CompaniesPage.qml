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

AbstractPage {
    headerColor: "#006E29"
    headerLabelColor: "white"
    title: qsTr("Companies")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: window.pageStack.pop()
        }
    }
    content: Item {
        anchors.fill: parent

        ListView {
            id: view
            clip: true
            anchors.fill: parent
            model: CompaniesModelInstance
            delegate: ClickableEntry {
                text: model.name
                subText: model.description
                onClicked: {
                    window.pageStack.push(linesPage)
                    CompaniesModelInstance.requestLines(model.index)
                }
            }
        }

        ScrollDecorator {
            flickableItem: view
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: CompaniesModelInstance.updating
            platformStyle: BusyIndicatorStyle { size: "large" }
            running: visible
        }
    }

    LinesPage {id: linesPage}
}

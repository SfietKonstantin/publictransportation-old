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

AbstractNavigationPage {

    function showConfigureBackend() {
        window.pageStack.push(backendSelectorPage)
    }

    headerColor: "#006E29"
    headerLabelColor: "white"
    title: qsTr("Public transportation")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-view-menu"
            anchors.right: parent.right
            onClicked: mainMenu.open()
        }
    }
    onShow: {
        if(page == "showSearchStation") {
            window.pageStack.push(searchStationPage)
        }
    }
    translationContext: "MainPage"
    model: ListModel {
        ListElement {
            identifier: "showSearchStation"
            text: QT_TR_NOOP("Search station")
        }
    }

    SelectionDialog {}

    Menu {
        id: mainMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Manage information source")
                onClicked: {
                    window.pageStack.push(backendSelectorPage)
                    mainMenu.close()
                }
            }
            MenuItem {
                text: qsTr("Switch color theme")
                onClicked: theme.inverted = !theme.inverted
            }
            MenuItem {
                text: qsTr("About")
                onClicked: window.pageStack.push(aboutPage)
            }
        }
    }

    SearchStationPage {id: searchStationPage}
    BackendSelectorPage {id: backendSelectorPage}
    AboutPage {id: aboutPage}

}

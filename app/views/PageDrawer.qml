import QtQuick 2.15
import QtQuick.Controls 2.15

Drawer {
    id: rootDrawer

    ListView {
        id: listView
        anchors.fill: parent

        headerPositioning: ListView.OverlayHeader
        header: Pane {
            id: header
            z: 2
            width: parent.width

            contentHeight: logo.height

            Image {
                id: logo
                width: parent.width
                source: "qrc:/icons/icon_256x256.png"
                fillMode: implicitWidth > width ? Image.PreserveAspectFit : Image.Pad
            }

            MenuSeparator {
                parent: header
                width: parent.width
                anchors.verticalCenter: parent.bottom
                visible: !listView.atYBeginning
            }
        }

        model: ListModel {
            ListElement {title: "START"; icon: ""; submenu: false}
            ListElement {title: "LANGUAGE"; icon: ""; submenu: false}
            ListElement {title: "FRENCH"; icon: ""; submenu: true}
            ListElement {title: "ENGLISH"; icon: ""; submenu: true}
            ListElement {title: "QUIT"; icon: ""; submenu: false}
        }

        delegate: ItemDelegate {
            leftPadding: model.submenu ? 25 : 10
            text: model.title
            font.pixelSize: model.submenu ? 20 : 25
            font.family: "Verdana"
            width: listView.width

            onClicked: {
                switch (index) {
                case 0:
                    myGame.restart();
                    focusKbd.focus = true;
                    drawer.close();
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    Qt.quit();
                    break;
                default:
                    break;
                }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }
}

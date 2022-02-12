import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: 270
    height: 81
    property double rowSpacing: 2
    property double columnSpacing: 2
    property int widthButton: width/10-rowSpacing
    property int heightButton: height/3-columnSpacing


    Rectangle {
        id: recKeyboard
        width: parent.width
        height: parent.height
        anchors.bottom: parent.bottom
        color: "transparent"
        Column {
            spacing: columnSpacing
            Row {
                spacing: rowSpacing
                Repeater {
                    model: [
                        {text: 'A', width: widthButton},
                        {text: 'B', width: widthButton},
                        {text: 'C', width: widthButton},
                        {text: 'D', width: widthButton},
                        {text: 'E', width: widthButton},
                        {text: 'F', width: widthButton},
                        {text: 'G', width: widthButton},
                        {text: 'H', width: widthButton},
                        {text: 'I', width: widthButton},
                        {text: 'J', width: widthButton},
                    ]
                    Rectangle {
                        width: modelData.text.length === 1 ? widthButton : widthButton*2
                        height: 40
                        color: "#36597A"
                        radius: 5
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "white"
                            text: modelData.text
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: root.clicked(modelData.text)
                        }
                    }
                }
            }
            Row {
                spacing: rowSpacing
                Repeater {
                    model: [
                        {text: 'K', width: widthButton},
                        {text: 'L', width: widthButton},
                        {text: 'M', width: widthButton},
                        {text: 'N', width: widthButton},
                        {text: 'O', width: widthButton},
                        {text: 'P', width: widthButton},
                        {text: 'Q', width: widthButton},
                        {text: 'R', width: widthButton},
                        {text: 'S', width: widthButton},
                        {text: 'T', width: widthButton},
                    ]
                    Rectangle {
                        width: modelData.text.length === 1 ? widthButton : widthButton*2
                        height: 40
                        color: "#36597A"
                        radius: 5
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "white"
                            text: modelData.text
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: root.clicked(modelData.text)
                        }
                    }
                }
            }

            Row { //wxcv
                spacing: rowSpacing
                Repeater {
                    model: [
                        {text: 'U'},
                        {text: 'V'},
                        {text: 'W'},
                        {text: 'X'},
                        {text: 'Y'},
                        {text: 'Z'},
                        {text: 'BACK'},
                        {text: 'ENTER'},
                    ]
                    Rectangle {
                        width: modelData.text.length === 1 ? widthButton : widthButton*2
                        height: 40
                        color: "#36597A"
                        radius: 5
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "white"
                            text: modelData.text
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: root.clicked(modelData.text)
                        }
                    }

                }
            }
        }
    }
    signal clicked(string text)
        onClicked: function(text) { myGame.keyPressed(text); }
}

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import FindTheWord.Game 1.0

Window {
    width: 414
    height: 896
    visible: true
    id: mainWindow
    title: "FIND THE WORD"

    Game {
        id: myGame;
        property bool animeShakeUp: false
        onYouWin: {
            animeShakeUp = true;
            txtWarning.text = "You win";
            recResponse.visible = true;
        }

        onYoutLost: {
            txtWarning.text = "You lost";
            recResponse.visible = true;
        }

        onWordNotFound: {
//            animeShakeUp = true;
            txtWarning.text = "This word can't be found";
        }

        onRestartGame: {
            animeShakeUp = false;
            lblResponse.text= myGame.wordToFindString;
            recResponse.visible = false;
        }

        onChronoUpdated: {
            txtTitle.text = chronoHMS;
        }

    }


    Item {
        id: focusKbd
        focus: true
        Keys.onPressed: function(event) {
            if ((event.key >= 65) && (event.key <= 90)) {
                myGame.keyPressed(String.fromCharCode(event.key));
                txtWarning.text = "";
            } else {
                if (event.key === Qt.Key_Return) {
                    myGame.keyPressed("ENTER");
                } else {
                    if (event.key === Qt.Key_Backspace) {
                        txtWarning.text = "";
                        myGame.keyPressed("BACK");
                    }
                }
            }
        }
    }

    Item {
        id: column
        width: parent.width
        height: parent.height

        Item {
            id: rowTop
            width: column.width
            height: 50

            Rectangle {
                id: recTopLeft
                width: 50
                height: 50
                color: "#333E47"
                Text {
                    text: "\u2630"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 30
                    font.styleName: "Bold"
                    font.family: "Verdana"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { drawer.open()}
                }
            }

            Rectangle {
                id: recTopTitle
                height: 50
                color: "#333E47"
                anchors.left: recTopLeft.right
                anchors.right: recTopRight.left
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                Text {
                    id: txtTitle
                    color: "#ffffff"
                    text: ""
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 30
                    font.styleName: "Bold"
                    font.family: "Verdana"
                }
            }

            Rectangle {
                id: recTopRight
                width: 50
                height: 50
                color: "#333E47"
                anchors.right: parent.right
                Text {
                    textFormat: Text.RichText
                    text: "\&#x1F4CA;"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 30
                }

            }
        }

        PageDrawer {
            id: drawer

            y: recTopTitle.y + 50
            width: mainWindow.width / 2
            height: mainWindow.height
        }


        Rectangle {
            id: recContent
            color: "#384D61"
            width: parent.width
            anchors.bottom: rowBottom.top
            anchors.top: rowTop.bottom
            Image {
                id: imgbackground
                source: "qrc:/images/background.png"
                fillMode: Image.Tile
                horizontalAlignment: Image.AlignLeft
                verticalAlignment: Image.AlignTop
                anchors.fill: parent
            }


            Rectangle {
                id: recResponse
                width: parent.width
                height: 100
                color: "transparent"
                visible: false
                Rectangle {
                    color: "#6A8094"
                    width: lblResponse.implicitWidth
                    height: lblResponse.implicitHeight
                    radius: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        id: lblResponse
                        text: ""
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        padding: 10
                        font.pixelSize: 20
                        font.styleName: "Bold"
                        font.family: "Verdana"
                        font.letterSpacing: 5
                        color: "#ffffff"

                    }
                }
            }



            Grid {
                id: gridGame
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: recResponse.bottom
                spacing: 5
                columns: 6
                visible: true

                Repeater {
                    id: recLetters
                    model: myGame.lettersModel
                    Rectangle {
                        id: recLetter
                        width: 60
                        height: 60
                        border.color: "#36597A"
                        border.width: 3

                        color: {
                            if (model.inTheRightPlace) {
                                return "blue";
                            } else {
                                if (model.inTheWord) {
                                    return "red"
                                }
                                else {
                                    return "transparent"
                                }
                            }
                        }

                        SequentialAnimation {
                            id: seqAnimed
                            running: myGame.animeShakeUp
                            loops: 2
                            NumberAnimation {
                                target: recLetters.itemAt(index)
                                property: "x";
                                to: x-10
                                duration: 100
                            }
                            NumberAnimation {
                                target: recLetters.itemAt(index)
                                property: "x"
                                to: x+10
                                duration: 100
                            }
                            NumberAnimation {
                                target: recLetters.itemAt(index)
                                property: "x"
                                to: x
                                duration: 100
                            }
                        }

                        Text {
                            id: txtLetter
                            text: model.value
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pixelSize: 30
                            font.styleName: "Bold"
                            font.family: "Verdana"
                            color: "white" //"#A0C0DE"
                        }
                    }
                }
            }

            Rectangle {
                id: recWaring
                width: parent.width
                height: 50
                color: "transparent"
                visible: true
                anchors.bottom: kbdPlay.top
                Text {
                    id: txtWarning
                    text: ""
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 20
                    font.styleName: "Bold"
                    font.family: "Verdana"
                    font.letterSpacing: 5
                    color: "#ffffff"
                }
            }

            KeyboardLight {
                id: kbdPlay
                width: parent.width
                height: 150
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: recContent.bottom
                anchors.bottomMargin: 5
            }
        }

        Item {
            id: rowBottom
            width: column.width
            height: 50
            anchors.bottom: parent.bottom
            Rectangle {
                id: recBottomLeft
                width: 50
                height: 50
                color: "#333E47"
            }

            Rectangle {
                id: recBottomTitle
                height: 50
                color: "#333E47"
                anchors.left: recBottomLeft.right
                anchors.right: recBottomRight.left
                Text {
                    id: txtAuthor
                    color: "#ffffff"
                    text: qsTr("Lagui-dev  @2022")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 14
                    font.family: "Verdana"
                }
                anchors.leftMargin: 0
                anchors.rightMargin: 0
            }

            Rectangle {
                id: recBottomRight
                width: 50
                height: 50
                color: "#333E47"
                anchors.right: parent.right
            }
        }
    }
}

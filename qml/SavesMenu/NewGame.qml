import QtQuick 2.9

import "./SavesMenu"

Item {
    id: root

    SavesListDelegate {
        id: save

        x: 0.05 * root.width
        y: 50
        width: 0.9 * theoreticalWidth
        height: 0.9 * theoreticalHeight
    }

    Item {
        id: name

        x: 20
        y: save.y + save.height + 700

        Text {
            font.family: fontStencil.name
            font.pixelSize: 40
            color: "#94ef94"
            text: "Name:"
        }

        TextInput {
            y: 46

            property string enteredText

            font.family: fontStencil.name
            font.pixelSize: 40
            color: "#94ef94"
            maximumLength: 30

            onActiveFocusChanged: {
                if (activeFocus)
                {
                    text = enteredText;
                    opacity = 1;
                }
                else if (enteredText == "")
                {
                    text = "Enter name here";
                    opacity = 0.5;
                }
            }

            onTextEdited: {
                enteredText = text;
                save.setName(text);
            }
        }
    }

    Item {
        x: 20
        y: name.y + 100

        Text {
            font.family: fontStencil.name
            font.pixelSize: 40
            color: "#94ef94"
            text: "Image:"
        }

        Image {
            x: 3
            y: 3
            width: 256
            height: 256
        }
        Image {
            id: pict

            x: 0
            y: 0
            width: 262
            height: 262
            source: "qrc:/graphics/GUI/Task_Picture.png"
        }

        Text {
            id: left

            x: -50
            y: 0
            width: 20
            height: pict.height

            verticalAlignment: Text.AlignVCenter
            font.family: fontStencil.name
            font.pixelSize: 30
            color: "#94ef94"
            text: "<"
        }
        MouseArea {
            anchors.fill: left
            anchors.margins: -5
        }

        Text {
            id: right

            x: pict.width + 30
            y: 0
            width: 20
            height: pict.height

            verticalAlignment: Text.AlignVCenter
            font.family: fontStencil.name
            font.pixelSize: 30
            color: "#94ef94"
            text: ">"
        }
        MouseArea {
            anchors.fill: right
            anchors.margins: -5
        }

        Item {

        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

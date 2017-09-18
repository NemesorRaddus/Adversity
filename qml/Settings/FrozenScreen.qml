import QtQuick 2.9

Item {
    id: root

    width: 1080
    height: 1920

    signal returnClicked()

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"
    }

    Image {
        id: background2

        anchors.fill: parent

        opacity: 0.15

        source: "qrc:/graphics/splash.png"
    }

    Text {
        x: 0
        y: 250
        width: parent.width

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.pixelSize: 80
        font.family: fontStencil.name
        text: "The game\nis currently in\nfrozen mode.\n\nTime will not pass\nuntil you return\nto the game."
        wrapMode: Text.WordWrap
    }

    Item {
        id: back

        x: 0
        y: 1300
        width: parent.width

        Text {
            width: parent.width

            horizontalAlignment: Text.AlignHCenter

            color: "#94ef94"
            font.pixelSize: 100
            font.family: fontStencil.name
            text: "Back to game"
            wrapMode: Text.WordWrap
        }
        MouseArea {
            x: 143
            y: 0
            width: 796
            height: 119
        }
    }

    Item {
        id: exit

        x: 0
        y: 1500
        width: parent.width

        Text {
            width: parent.width

            horizontalAlignment: Text.AlignHCenter

            color: "#94ef94"
            font.pixelSize: 100
            font.family: fontStencil.name
            text: "Exit game"
            wrapMode: Text.WordWrap
        }
        MouseArea {
            x: 255
            y: 0
            width: 577
            height: 119
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

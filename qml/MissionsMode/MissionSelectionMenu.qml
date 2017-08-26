import QtQuick 2.0

Item {
    id: root

    function returnToDefault()
    {

    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"
    }

    HeroDelegate {
        id: delegate

        x: 0
        y: 0
        width: parent.width
        height: 280
    }

    Item {
        id: weapon1

        x: 4
        y: delegate.y + delegate.height + 4
        width: 130
        height: width

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture2.png"
        }
        Image {
            id: weapon1Art

            x: 1
            y: x
            width: 128
            height: width
        }
        MouseArea {
            id: weapon1MA

            anchors.fill: parent

            onClicked: {

            }
        }
    }
    Item {
        id: weapon2

        x: weapon1.x + weapon1.width + 4
        y: weapon1.y
        width: weapon1.width
        height: width

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture2.png"
        }
        Image {
            id: weapon2Art

            x: 1
            y: x
            width: 128
            height: width
        }
        MouseArea {
            id: weapon2MA

            anchors.fill: parent

            onClicked: {

            }
        }
    }
    Text {
        x: weapon2.x + weapon2.width + 10
        y: 50
        color: "#94ef94"
        text: "Weapons/Tools"
        font.pixelSize: 36
        font.family: fontStencil.name
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

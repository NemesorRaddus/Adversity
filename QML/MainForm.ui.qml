import QtQuick 2.7

Rectangle {
    id: mainRoot

    width: 315
    height: 501

    Image {
        id: background
        anchors.fill: parent
        source: "qrc:/graphics/Background.png"
    }

    Image {
        id: topAndBottomBar
        anchors.fill: parent
        source: "qrc:/graphics/GUI.png"

        MouseArea {
            id: missionsButton
            x: 57*parent.width/1080
            y: 1727*parent.height/1920
            width: 272*parent.width/1080
            height: 141*parent.height/1920
            visible: true
            antialiasing: false
        }
        MouseArea {
            id: baseButton
            x: 403*parent.width/1080
            y: 1727*parent.height/1920
            width: 272*parent.width/1080
            height: 141*parent.height/1920
            visible: true
            antialiasing: false
        }
        MouseArea {
            id: heroesButton
            x: 751*parent.width/1080
            y: 1727*parent.height/1920
            width: 272*parent.width/1080
            height: 141*parent.height/1920
            visible: true
            antialiasing: false
        }
    }
}

import QtQuick 2.9

import Game 1.0

Item {
    id: root

    width: 1080
    height: 1920

    state: "hidden"

    signal backClicked()

    function show()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        state = "";
        backButton.visible = true;
    }

    function hide()
    {
        state = "hidden";
        backButton.visible = false;
    }

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Text {
        id: designText

        y: 320
        width: parent.width

        color: "#94ef94"
        text: "Design"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 100
        font.family: fontStencil.name
    }

    Text {
        id: designName

        y: 500
        width: parent.width

        color: "#94ef94"
        text: "Krystian Duchnowski"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 80
        font.family: fontStencil.name
    }

    Text {
        id: codeText
        x: 0

        y: 700
        width: parent.width

        color: "#94ef94"
        text: "Code"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 100
        font.family: fontStencil.name
    }

    Text {
        id: codeName
        x: 0

        y: 880
        width: parent.width

        color: "#94ef94"
        text: "Piotr Juszczyk"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 80
        font.family: fontStencil.name
    }

    Image {
        id: taskBorderBottom

        x: 17
        y: 1334

        width: 1048
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        id: back

        x: 400
        y: 1344
        width: 260
        height: 120

        Text {
            id: backText

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            visible: false

            anchors.fill: parent

            onClicked: backClicked()
        }
    }

    states: State {
        name: "hidden"
        PropertyChanges { target: root; opacity: 0.0 }
    }

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "opacity"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 200 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

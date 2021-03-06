import QtQuick 2.9

import Game 1.0

Item {
    id: root

    width: 425
    height: 200

    property int displayTime: 3000

    signal clicked()

    function setAmount(amount)
    {
        if (amount>9)
            amountOfReports.text = "!";
        else
            amountOfReports.text = amount;
    }

    function show()
    {
        transitionRoot0.duration = transitionRoot0.baseDuration * GameApi.animMultiplier();
        transitionRoot1.duration = transitionRoot1.baseDuration * GameApi.animMultiplier();

        state = "";
        animTimer.start();
    }

    state: "hidden"

    MouseArea {
        anchors.fill: parent

        onClicked: root.clicked()
    }

    Rectangle {
        anchors.fill: parent

        border.color: "#94ef94"
        border.width: 5
        color: "#171717"
    }

    Text {
        id: amountOfReports
        x: 0
        y: 27
        width: 184
        height: parent.height

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.family: fontStencil.name
        text: "5"
        font.pixelSize: 200
        font.bold: true
    }

    Text {
        x: 184
        y: -5
        height: parent.height

        color: "#94ef94"
        font.family: fontWingdings.name
        text: "*"
        font.pixelSize: 200
        font.bold: true
    }

    Timer {
        id: animTimer

        interval: root.displayTime - 1500

        onRunningChanged: {
            if (!running)
                root.state = "hidden";
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; x: 1080+width }
        }
    ]

    transitions: [
        Transition {
            from: "hidden"; to: ""
            NumberAnimation { id: transitionRoot0; properties: "x"; easing.type: Easing.OutQuart; duration: baseDuration; property int baseDuration: 500 }
        },
        Transition {
            from: ""; to: "hidden"
            NumberAnimation { id: transitionRoot1; properties: "x"; easing.type: Easing.InQuart; duration: baseDuration; property int baseDuration: 1000 }
        }
    ]

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
    FontLoader {
        id: fontWingdings

        source: "qrc:/fonts/WINGDINGS.TTF"
    }
}

import QtQuick 2.9

Item {
    id: root

    width: 425
    height: 200

    property int displayTime: 3000

    function setAmount(amount)
    {
        if (amount>9)
            amountOfReports.text = "9+";
        else
            amountOfReports.text = amount;
    }

    function show()
    {
        state = "";
        animTimer.start();
    }

    state: "hidden"

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
            NumberAnimation { properties: "x"; easing.type: Easing.OutQuart; duration: 500 }
        },
        Transition {
            from: ""; to: "hidden"
            NumberAnimation { properties: "x"; easing.type: Easing.InQuart; duration: 1000 }
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

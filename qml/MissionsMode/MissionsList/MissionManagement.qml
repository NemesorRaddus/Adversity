import QtQuick 2.9
import QtGraphicalEffects 1.0

Item {
    id: root

    width: 1080
    height: 1440

    signal backClicked()

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Image {
        id: connectionBackground
        x: -60
        y: 120
        width: 1200
        height: 1200

        opacity: 0

        source: "qrc:/graphics/GUI/Connected.png"
    }
    GaussianBlur {
        anchors.fill: connectionBackground
        source: connectionBackground
        opacity: 0.4
        radius: 60
        samples: 120
        deviation: 30
    }

    Item {
        y: 1100
        width: parent.width
        height: 150

        Text {
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter

            color: "#680000"
            font.family: fontStencil.name
            font.pixelSize: 150
            text: "Abort"
        }
        MouseArea {
            anchors.fill: parent
        }
    }

    Text {
        id: connectionLostText

        x: 0
        y: 35
        width: parent.width

        horizontalAlignment: Text.AlignHCenter

        color: "#bf0000"
        font.family: fontStencil.name
        font.pixelSize: 100
        text: "Connection lost!"

        function startShowing()
        {
            if (isShowing == false)
            {
                connectionLostTextFadeOut.start();
                connectionLostTextBlinking.toRunOrNotToRun=true;
                connectionLostTextBlinking.start();
                isShowing=true;
            }
        }
        function stopShowing()
        {
            if (isShowing == true)
            {
                connectionLostTextFadeIn.start();
                connectionLostTextBlinking.toRunOrNotToRun=false;
                connectionLostTextBlinking.stop();
                isShowing=false;
            }
        }

        NumberAnimation {
            id: connectionLostTextFadeIn

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            targets: [
                connectionLostText
            ]
        }
        NumberAnimation {
            id: connectionLostTextFadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 0
            to: 1
            targets: [
                connectionLostText
            ]
        }
        NumberAnimation {
            id: connectionLostTextBlinking

            property bool toRunOrNotToRun: false

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 2000
            from: 1
            to: 0.5
            targets: [
                connectionLostText
            ]
            onRunningChanged: {
                if (running == false && toRunOrNotToRun == true)
                {
                    if (from == 1)
                    {
                        from = 0.5;
                        to = 1;
                    }
                    else
                    {
                        from = 1;
                        to = 0.5;
                    }

                    running = true;
                }
            }
        }

    }

    Text {
        id: noSignalAbortText
        x: 20
        y: 197
        width: 1040

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.family: fontStencil.name
        font.pixelSize: 50
        text: "We've lost track of Paul Luft. It means that something disrupts connection or connection module in the suit is damaged. In the worst case this mercenary is dead. Each day without a sign of living influences stress level of all mercenaries (including the lost one), especially with similar character type."
        wrapMode: Text.WordWrap
    }

    Text {
        id: abortText

        x: 20
        y: 793
        width: 1040

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.family: fontStencil.name
        font.pixelSize: 50
        text: "You can abort mission at any time, but be wary that you will sentence your mercenary to death. Aborting mission will affect other mercenaries stress condition."
        wrapMode: Text.WordWrap
    }

    Item {
        id: back

        x: 17
        y: 1396
        width: 1048
        height: 68

        Text {
            id: backText

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            anchors.rightMargin: 421
            anchors.leftMargin: 418

            anchors.fill: parent

            onClicked: backClicked()
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

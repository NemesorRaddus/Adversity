import QtQuick 2.9
import QtGraphicalEffects 1.0

import Game 1.0

import "../.."
import ".."

Item {
    id: root

    width: 1080
    height: 1440

    signal backClicked()
    signal reportsClicked()
    signal mercenaryClicked()
    signal missionManagementClicked()

    function setItem(name)
    {

    }

    state: "hiddenDown"

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Item {
        id: land
        width: root.width
        height: width

        opacity: 0.3

        Image {
            id: landArt

            anchors.fill: parent
            opacity: 0

            source: "qrc:/graphics/Missions/Lands/HegosPlains.png"
        }
        GaussianBlur {
            anchors.fill: landArt
            source: landArt
            radius: 60
            samples: 120
            deviation: 30
        }
    }
    Image {
        id: opMaskUp

        anchors.fill: land

        rotation: 180

        source: "qrc:/graphics/GUI/Mask.png"
    }
    Image {
        id: opMaskDown

        anchors.fill: land

        source: "qrc:/graphics/GUI/Mask.png"
    }

    Text {
        x: 0
        y: 0
        width: root.width

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.family: fontStencil.name
        font.pixelSize: 80
        text: "\nMercenary:\nPaul Luft\n\nLand:\nHegos Plains\n\nDays on mission:\n10\n"
    }

    Item {
        id: buttons

        x: 200
        y: 873
        width: 680
        height: 323

        Text {
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter

            color: "#94ef94"
            font.family: fontStencil.name
            font.pixelSize: 50
            text: "< Reports\n\nMercenary >\n\nMission management"
        }

        MouseArea {
            x: 117
            y: -23
            width: 452
            height: 100

            onClicked: reportsClicked()
        }

        MouseArea {
            x: 117
            y: 77
            width: 452
            height: 130

            onClicked: mercenaryClicked()
        }

        MouseArea {
            x: 0
            y: 208
            width: 680
            height: 115

            onClicked: missionManagementClicked()
        }
    }

    Image {
        x: 200
        y: 1113
        width: 50
        height: width

        source: "qrc:/graphics/GUI/Settings.png"
    }
    Image {
        x: 830
        y: 1113
        width: 50
        height: width
        source: "qrc:/graphics/GUI/Settings.png"
    }

    Item {
        id: missionIcons

        y: 1238

        Image {
            id: signalIcon

            x: missionLengthIcon.x-168
            width: 128
            height: width

            function update()
            {
                source = "qrc:/graphics/GUI/" + (root.signalOn_ ? "Connected" : "Disconnected") + ".png";
            }

            source: "qrc:/graphics/GUI/Connected.png"
        }
        Image {
            id: missionLengthIcon

            x: 444
            y: -64
            width: 192
            height: width

            function update()
            {
                var s1,s2;
                s1=GameApi.globalsCpp.alterNormalTextToInternal(land_);
                if (missionLength_ == "Short")
                    s2="1";
                else if (missionLength_ == "Medium")
                    s2="2";
                else if (missionLength_ == "Long")
                    s2="3";
                else if (missionLength_ == "Extreme")
                    s2="4";
                source = "qrc:/graphics/GUI/MissionLength/"+s1+s2+".png";
            }

            source: "qrc:/graphics/GUI/MissionLength/AuroraForest4.png"
        }
        Image {
            id: sbeActivationIcon

            x: missionLengthIcon.x+232
            width: 128
            height: width

            function update()
            {
                visible = root.sbeOn_;
            }

            source: "qrc:/graphics/GUI/Attributes/StressLimit.png"
        }
    }

    Image {
        id: taskBorder

        x: 17
        y: 1386
        width: 1046
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
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

    states: [
        State {
            name: "hiddenDown"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 300 }
        }
    ]

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

import QtQuick 2.9

Item {
    id: root

    width: 1080
    height: 1440

    signal backClicked()

    state: "hidden"

    function show()
    {
        state = "";

        leftArrow.visible = true;
        rightArrow.visible = true;
        fpsMA.visible = true;
        exitMA.visible = true;
        creditsMA.visible = true;
        backButton.visible = true;
    }

    function hide()
    {
        state = "hidden";

        leftArrow.visible = false;
        rightArrow.visible = false;
        fpsMA.visible = false;
        exitMA.visible = false;
        creditsMA.visible = false;
        backButton.visible = false;
    }

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Text {
        y: 8
        width: root.width

        horizontalAlignment: Text.AlignHCenter

        color: "#94ef94"
        font.pixelSize: 80
        font.family: fontStencil.name
        text: "Settings"
    }

    Image {
        id: taskBorderTitle

        x: 17
        y: 98

        width: 1048
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        x: 17
        y: 150

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Animations"
        }

        Text {
            id: arrows
            x: 590
            width: 460
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "<                           >"
        }
        Text {
            x: arrows.x
            width: arrows.width
            color: "#94ef94"
            font.pixelSize: arrows.font.pixelSize
            font.family: fontStencil.name
            text: "Normal"
            horizontalAlignment: Text.AlignHCenter
        }
        MouseArea {
            id: leftArrow

            x: arrows.x-10
            y: -10
            width: 65
            height: arrows.height-2*y

            visible: false

//            onClicked: ;
        }
        MouseArea {
            id: rightArrow
            x: arrows.x+arrows.width-width+10
            y: leftArrow.y
            width: leftArrow.width
            height: leftArrow.height

            visible: false

//            onClicked: ;
        }
    }

    Item {
        x: 17
        y: 240

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Show fps"
        }

        Image {
            id: showFpsIcon

            x: 940
            y: -10

            width: 80
            height: width

            source: "qrc:/graphics/GUI/Settings.png"

            state: "off"

            function setOn()
            {
                state = "";
                anim.restart();
            }

            function setOff()
            {
                state = "hidden";
                anim.stop();
            }

            MouseArea {
                id: fpsMA

                anchors.fill: parent

                visible: false

//                onClicked: ;
            }

            RotationAnimator on rotation {
                id: anim
                from: 0;
                to: 360;
                duration: 2500
                loops: RotationAnimation.Infinite
                running: false
            }

            states: State {
                name: "off"
                PropertyChanges { target: showFpsIcon; opacity: 0.5 }
            }

            transitions: Transition {
                NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 500 }
            }
        }
    }

    Item {
        x: 17
        y: 330

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Exit game"
        }

        Image {
            id: exitGame

            x: 950

            width: 60
            height: width

            source: "qrc:/graphics/GUI/Abort.png"

            MouseArea {
                id: exitMA

                anchors.fill: parent

                anchors.margins: -10

                visible: false

//                onClicked: ;
            }
        }
    }

    Item {
        x: 17
        y: 420

        Text {
            color: "#94ef94"
            font.pixelSize: 60
            font.family: fontStencil.name
            text: "Credits"
        }

        Image {
            id: credits

            x: 950

            width: 60
            height: width

            source: "qrc:/graphics/GUI/Profitability.png"

            MouseArea {
                id: creditsMA
                anchors.fill: parent

                anchors.margins: -10

                visible: false

//                onClicked: ;
            }
        }
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
            text: qsTr("Back")
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
        NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 200 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

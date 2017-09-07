import QtQuick 2.9

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 1920

    width: 1080
    height: 1920

    function show()
    {
        confirmBox.visible = true;
        backgroundHider.state = "hidingContent";
        backgroundClicksCatcher.visible = true;
    }

    function hide()
    {
        confirmBox.visible = false;
        backgroundHider.state = "";
        backgroundClicksCatcher.visible = false;
    }

    signal accepted()
    signal declined()

    transform: [
        Scale {
            id: someScale

            xScale: width/theoreticalWidth
            yScale: height/theoreticalHeight
        },
        Translate {
            x: (width-theoreticalWidth*someScale.xScale)/2
            y: (height-theoreticalHeight*someScale.yScale)/2
        }
    ]

    Image {
        id: backgroundHider

        anchors.fill: parent

        opacity: 0

        source: "qrc:/graphics/GUI/Background.png"

        states: [
            State {
                name: "hidingContent"
                PropertyChanges { target: backgroundHider; opacity: 0.75 }
            }
        ]

        transitions: Transition {
            NumberAnimation { properties: "opacity"; easing.type: Easing.InQuad; duration: 500 }
        }
    }

    MouseArea {
        id: backgroundClicksCatcher

        visible: false

        anchors.fill: parent
    }

    Item {
        id: confirmBox

        visible: false

        width: 700
        height: 400
        anchors.centerIn: parent

        Rectangle {
            id: confirmBoxRect

            anchors.fill: parent

            color: "#171717"

            border.color: "#94ef94"
            border.width: 5
        }

        Text {
            id: pleaseConfirmText

            x: 50
            y: 50
            width: parent.width - 2*x
            height: font.pixelSize+5

            color: "#94ef94"
            text: "Are you sure?"
            font.pixelSize: 80
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: yesText

            x: 60
            y: parent.height - height - 50
            width: parent.width/2 - 70
            height: font.pixelSize+4

            color: "#94ef94"
            text: "Yes"
            font.pixelSize: 60
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }
        MouseArea {
            id: yesMA

            anchors.fill: yesText

            onClicked: {
                root.hide();
                root.accepted();
            }
        }

        Text {
            id: noText

            x: parent.width/2 + 10
            y: parent.height - height - 50
            width: parent.width/2 - 70
            height: font.pixelSize+4

            color: "#94ef94"
            text: "No"
            font.pixelSize: 60
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter
        }
        MouseArea {
            id: noMA

            anchors.fill: noText

            onClicked: {
                root.hide();
                root.declined();
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

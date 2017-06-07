import QtQuick 2.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 566

    width: 1080
    height: 566

    function update()
    {

    }

    function returnToDefault()
    {

    }

    signal requestSwitchingToResourcesTab()

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

    Item {
        id: modeNameBar

        x: 0
        y: 0
        width: parent.theoreticalWidth
        height: bottomTaskBorder.y + bottomTaskBorder.height

        Text {
            id: modeName

            x: 0
            y: 0
            width: parent.width
            height: bottomTaskBorder.y

            color: "#94ef94"
            text: "< Equipment"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name

            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
        }
        MouseArea {
            id: modeChangerLeft

            x: 0
            y: 0
            width: modeName.width / 2
            height: modeName.height

            onClicked: requestSwitchingToResourcesTab()
        }

        Image {
            id: bottomTaskBorder

            x: 17
            y: modeName.font.pixelSize + 2
            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }
    }

    states: [
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        },
        State {
            name: "hiddenRight2"
            PropertyChanges { target: root; x: width * 2 }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}

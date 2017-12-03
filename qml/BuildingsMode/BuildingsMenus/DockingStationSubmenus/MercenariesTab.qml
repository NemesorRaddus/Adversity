import QtQuick 2.9

import Game 1.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 566

    width: 1080
    height: 566

    function update()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        mercenariesList.update();
    }

    function returnToDefault()
    {
        mercenariesList.returnToDefault();
    }

    signal requestSwitchingToResourcesTab()
    signal requestUpdate()

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
            text: "Recruits >"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name

            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
        }
        MouseArea {
            id: modeChangerRight

            x: modeName.width / 2
            y: 0
            width: x
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

    MercenariesList {
        id: mercenariesList

        x: 0
        y: modeNameBar.height
        width: parent.theoreticalWidth
        height: parent.theoreticalHeight - y

        onMercenaryClicked: {
            GameApi.base.buildings.dockingStation.hireMercenary(mercenaryName,GameApi.base.buildings.dockingStation.waitingTime());
            update();
            root.requestUpdate();
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -1 * width }
        },
        State {
            name: "hiddenLeft2"
            PropertyChanges { target: root; x: -2 * width }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 250 }
    }
}

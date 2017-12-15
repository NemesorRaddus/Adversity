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

        equipmentsList.update();
    }

    function returnToDefault()
    {
        equipmentsList.returnToDefault();
    }

    signal requestSwitchingToResourcesTab()
    signal requestResourcesUpdate()

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

    EquipmentsList {
        id: equipmentsList

        x: 0
        y: modeNameBar.height
        width: parent.theoreticalWidth
        height: parent.theoreticalHeight - y

        onBuyClicked: {
            GameApi.base.buildings.dockingStation.prepareEquipmentForQML(index);
            if (GameApi.base.buildings.dockingStation.equipmentPreparedForQML.buyingAetheriteCost() <= GameApi.base.resources.currentAetheriteAmount())
            {
                GameApi.base.buildings.dockingStation.buyEquipment(index,GameApi.base.buildings.dockingStation.waitingTime());
                update();
                root.requestResourcesUpdate();
            }
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
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 250 }
    }
}

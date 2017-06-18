import QtQuick 2.0

import Game 1.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 566

    width: 1080
    height: 566

    signal requestSwitchingToHeroesTab()
    signal requestSwitchingToEquipmentTab()
    signal requestResourcesUpdate()

    function update()
    {
        tradingTable.update();
    }

    function returnToDefault()
    {
        tradingTable.returnToDefault();
    }

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
            text: "< Trade >"
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

            onClicked: requestSwitchingToHeroesTab()
        }
        MouseArea {
            id: modeChangerRight

            x: modeName.width / 2
            y: 0
            width: x
            height: modeName.height

            onClicked: requestSwitchingToEquipmentTab()
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

    TradingTable {
        id: tradingTable

        x: 0
        y: modeNameBar.height
        width: parent.theoreticalWidth
        height: parent.theoreticalHeight - y

        onTransactionAccepted: {
            GameApi.base.dockingStation.startTransaction(sourceRes, targetRes, targetValue);
            requestResourcesUpdate()
        }
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -1 *width }
        },
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}

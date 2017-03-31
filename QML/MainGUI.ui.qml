import QtQuick 2.7

Rectangle {
    id: mainRoot

    property alias missionsButton: missionsButton
    property alias baseButton: baseButton
    property alias heroesButton: heroesButton
    property alias energyValue: energyText
    property alias energyValue2: energyText2
    property alias buildingMaterialsValue: buildingMaterialsText
    property alias buildingMaterialsValue2: buildingMaterialsText2
    property alias foodSuppliesValue: foodSuppliesText
    property alias foodSuppliesValue2: foodSuppliesText2
    property alias aetheriteValue: aetheriteText
    property alias aetheriteValue2: aetheriteText2
    property alias hourValue: hour
    property alias dayValue: day
    property alias settingsButton: settingsMA
    property alias buildingsGUI: buildingsMode

    width: 450
    height: 800

    Image {
        id: background

        anchors.fill: parent

        source: "qrc:/graphics/GUI/Background.png"
    }

    Image {
        id: topAndBottomBar

        anchors.fill: parent

        source: "qrc:/graphics/GUI/GUI.png"

        MouseArea {
            id: missionsButton

            x: 57 * parent.width / 1080
            y: 1727 * parent.height / 1920
            width: 272 * parent.width / 1080
            height: 141 * parent.height / 1920

            visible: true
        }
        MouseArea {
            id: baseButton

            x: 403 * parent.width / 1080
            y: 1727 * parent.height / 1920
            width: 272 * parent.width / 1080
            height: 141 * parent.height / 1920

            visible: true
        }
        MouseArea {
            id: heroesButton

            x: 751 * parent.width / 1080
            y: 1727 * parent.height / 1920
            width: 272 * parent.width / 1080
            height: 141 * parent.height / 1920

            visible: true
        }

        Image {
            id: energyIcon

            x: -3 * parent.width / 1080
            y: 22 * parent.height / 1920
            width: 72 * parent.width / 1080
            height: 72 * parent.height / 1920

            source: "qrc:/graphics/GUI/Energy.png"
        }
        Text {
            id: energyText

            x: 64 * parent.width / 1080
            y: 22 * parent.height / 1920
            width: 53

            color: "#94ef94"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }
        Text {
            id: energyText2

            x: 70 * parent.width / 1080
            y: 64 * parent.height / 1920
            width: 47

            color: "#94ef94"
            text: qsTr("10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }

        Image {
            id: buildingMaterialsIcon

            x: 190 * parent.width / 1080
            y: 15 * parent.height / 1920
            width: 88 * parent.width / 1080
            height: 88 * parent.height / 1920

            source: "qrc:/graphics/GUI/Buildingmaterials.png"
        }
        Text {
            id: buildingMaterialsText

            x: 276 * parent.width / 1080
            y: 22 * parent.height / 1920
            width: 53

            color: "#94ef94"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }
        Text {
            id: buildingMaterialsText2

            x: 282 * parent.width / 1080
            y: 64 * parent.height / 1920
            width: 47

            color: "#94ef94"
            text: qsTr("10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }

        Image {
            id: foodSuppliesIcon

            x: 420 * parent.width / 1080
            y: 23 * parent.height / 1920
            width: 72 * parent.width / 1080
            height: 72 * parent.height / 1920

            source: "qrc:/graphics/GUI/Foodsupplies.png"
        }
        Text {
            id: foodSuppliesText

            x: 504 * parent.width / 1080
            y: 22 * parent.height / 1920
            width: 53

            color: "#94ef94"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }
        Text {
            id: foodSuppliesText2

            x: 510 * parent.width / 1080
            y: 64 * parent.height / 1920
            width: 47

            color: "#94ef94"
            text: qsTr("10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }

        Image {
            id: aetheriteIcon

            x: 638 * parent.width / 1080
            y: 23 * parent.height / 1920
            width: 72 * parent.width / 1080
            height: 72 * parent.height / 1920

            source: "qrc:/graphics/GUI/Aetherite.png"
        }
        Text {
            id: aetheriteText

            x: 714 * parent.width / 1080
            y: 22 * parent.height / 1920
            width: 53

            color: "#94ef94"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }
        Text {
            id: aetheriteText2

            x: 720 * parent.width / 1080
            y: 64 * parent.height / 1920
            width: 47

            color: "#94ef94"
            text: qsTr("10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            font.family: fontStencil.name
        }

        Text {
            id: hour

            x: 870 * parent.width / 1080
            y: 8 * parent.height / 1920
            width: 52

            color: "#94ef94"
            text: qsTr("12:00")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
            font.family: fontStencil.name
        }
        Text {
            id: day

            x: 873 * parent.width / 1080
            y: 64 * parent.height / 1920

            color: "#94ef94"
            text: qsTr("DAY 1380")
            font.pixelSize: 18
            font.family: fontStencil.name
        }
        Item {
            id: settingsItem

            x: 1005 * parent.width / 1080
            y: 3 * parent.height / 1920
            width: 70 * parent.width / 1080
            height: 70 * parent.height / 1920

            property alias mouseArea: settingsMA

            Image {
                id: settingsImage

                anchors.fill: parent

                source: "qrc:/graphics/GUI/Settings.png"
            }
            MouseArea {
                id: settingsMA

                anchors.fill: parent
            }
        }
    }

    BuildingsModeGUI {
        id: buildingsMode

        x: 0
        y: 189 * parent.height / 1920
        width: parent.width
        height: 1464 * parent.height / 1920
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

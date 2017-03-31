import QtQuick 2.0

import Game 1.0

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1920

    function setDescription(desc)
    {
        description.text = desc;
    }
    function setLevel(lvlnr)
    {
        level.text = "Level: "+lvlnr;
    }
    function setEnergyCons(amount)
    {
        energyConsAmount.text = amount;
    }
    function setUpgEnergyCost(amount)
    {
        upgradeEnergyCostAmount.text = amount;
    }
    function setUpgBMCost(amount)
    {
        upgradeBMCostAmount.text = amount;
    }
    function setUpgTime(amount)
    {
        upgradeTimeAmount.text = amount;
    }
    function setUpgEnergyCons(amount)
    {
        upgradeEnergyConsAmount.text = amount;
    }

    signal backClicked()
    signal upgradeRequested()

    width: 1080
    height: 1920

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
        id: itemBorder
        x: 17
        y: 265
        width: 1048
        height: 3
        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Image {
        id: art
        x: 20
        y: 3
        width: 256
        height: 256
        source: "qrc:/graphics/Buildings/Barracks.png"
    }

    Image {
        id: frame
        x: 17
        y: 0
        width: 262
        height: 262
        source: "qrc:/graphics/GUI/Task_Picture.png"
    }

    Text {
        id: name
        x: 280
        y: 10
        color: "#94ef94"
        text: qsTr("Barracks")
        font.pixelSize: 60
        font.family: fontStencil.name
    }

    Text {
        id: level
        x: 280
        y: 70
        color: "#94ef94"
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Text {
        id: description
        x: 280
        y: 123
        width: 785
        height: 136
        color: "#568b56"
        wrapMode: Text.WordWrap
        font.pixelSize: 30
        font.family: fontStencil.name
    }

    Text {
        id: energyConsText
        x: 20
        y: 274
        width: 435
        height: 47
        color: "#94ef94"
        text: qsTr("Energy consumption:")
        font.pixelSize: 40
        font.family: fontStencil.name
    }
    Image {
        id: energyConsIcon
        x: 471
        y: 274
        width: 47
        height: 47
        source: "qrc:/graphics/GUI/Energy.png"
    }
    Text {
        id: energyConsAmount
        x: 524
        y: 274
        width: 56
        height: 47
        color: "#94ef94"
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Text {
        id: upgradeText
        x: 20
        y: 327
        width: 199
        height: 47
        color: "#94ef94"
        text: qsTr("Upgrade:")
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Image {
        id: upgradeEnergyCostIcon
        x: 225
        y: 327
        width: 47
        height: 47
        source: "qrc:/graphics/GUI/Energy.png"
    }
    Text {
        id: upgradeEnergyCostAmount
        x: 278
        y: 327
        width: 90
        height: 47
        color: "#94ef94"
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Image {
        id: upgradeBMCostIcon
        x: 374
        y: 327
        width: 47
        height: 47
        source: "qrc:/graphics/GUI/Buildingmaterials.png"
    }
    Text {
        id: upgradeBMCostAmount
        x: 427
        y: 327
        width: 90
        height: 47
        color: "#94ef94"
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Image {
        id: upgradeTimeIcon
        x: 523
        y: 327
        width: 47
        height: 47
        source: "qrc:/graphics/GUI/Time.png"
    }
    Text {
        id: upgradeTimeAmount
        x: 576
        y: 327
        width: 90
        height: 47
        color: "#94ef94"
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Image {
        id: upgradeEnergyConsIcon
        x: 672
        y: 327
        width: 47
        height: 47
        source: "qrc:/graphics/GUI/Energy.png"
    }
    Text {
        id: upgradeEnergyConsAmount
        x: 725
        y: 327
        width: 90
        height: 47
        color: "#94ef94"
        font.pixelSize: 40
        font.family: fontStencil.name
    }

    Image {
        id: upgradeIcon
        x: 1013
        y: 327
        width: 47
        height: 47
        source: "qrc:/graphics/GUI/Settings.png"
    }
    MouseArea {
        id: upgradeButton
        x: 1013
        y: 327
        width: 47
        height: 47

        onClicked: upgradeRequested()
    }

    Image {
        id: itemBorder1
        x: 17
        y: 386
        width: 1048
        height: 3
        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Text {
        id: backText

        x: 422
        y: 1800
        width: 216
        height: 47
        color: "#94ef94"
        text: qsTr("Back")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 50
        font.family: fontStencil.name
    }
    MouseArea {
        id: backButton

        x: 402
        y: 1780
        width: 256
        height: 87

        onClicked: backClicked()
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

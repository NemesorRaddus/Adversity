import QtQuick 2.0

Item {
    id: root

    signal backClicked()
    signal exploreClicked()

    function returnToDefault()
    {

    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    Rectangle {
        id: background

        anchors.fill: parent

        color: "#171717"

    }

    Text {
        x: 4
        y: 0

        color: "#94ef94"
        text: "Mercenary:"
        font.pixelSize: 50
        font.family: fontStencil.name
    }

    HeroDelegate {
        id: delegate

        x: 0
        y: 50
        width: parent.width
        height: 271
    }

    Text {
        x: 520
        y: 322

        color: "#94ef94"
        text: "Equipment:"
        font.pixelSize: 50
        font.family: fontStencil.name
    }

    Item {
        id: armour

        x: 4
        y: delegate.y + delegate.height + 4
        width: 260
        height: width

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
        Image {
            id: armourArt

            x: 3
            y: x
            width: 256
            height: width

            source: "qrc:/graphics/GUI/ArmourSlot.png"
        }
        MouseArea {
            id: armourMA

            anchors.fill: parent

            onClicked: {

            }
        }
    }
    Item {
        id: weapon1

        x: armour.x
        y: armour.y + armour.height + 4
        width: 260
        height: width

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
        Image {
            id: weapon1Art

            x: 3
            y: x
            width: 256
            height: width

            source: "qrc:/graphics/GUI/ToolSlot.png"
        }
        MouseArea {
            id: weapon1MA

            anchors.fill: parent

            onClicked: {

            }
        }
    }
    Item {
        id: weapon2

        x: weapon1.x
        y: weapon1.y + weapon1.height + 4
        width: weapon1.width
        height: width

        Image {
            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"
        }
        Image {
            id: weapon2Art

            x: 3
            y: x
            width: 256
            height: width

            source: "qrc:/graphics/GUI/ToolSlot.png"
        }
        MouseArea {
            id: weapon2MA

            anchors.fill: parent

            onClicked: {

            }
        }
    }

    Item {
        id: energy

        x: armour.x + armour.width + 4
        y: armour.y + armour.height/2 - 45

        Image {
            id: energyIcon

            x: 0
            y: 0
            width: 100
            height: width

            source: "qrc:/graphics/GUI/Energy.png"
        }
        Text {
            id: warningEnergyText

            property bool isShowing: false

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            text: "Tip: at least 10 energy recommended."
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            function startShowing()
            {
                if (isShowing == false)
                {
                    warningEnergyFadeOut.start();
                    warningEnergyBlinking.toRunOrNotToRun=true;
                    warningEnergyBlinking.start();
                    isShowing=true;
                }
            }
            function stopShowing()
            {
                if (isShowing == true)
                {
                    warningEnergyFadeIn.start();
                    warningEnergyBlinking.toRunOrNotToRun=false;
                    warningEnergyBlinking.stop();
                    isShowing=false;
                }
            }

            NumberAnimation {
                id: warningEnergyFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                targets: [
                    warningEnergyText
                ]
            }
            NumberAnimation {
                id: warningEnergyFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                targets: [
                    warningEnergyText
                ]
            }
            NumberAnimation {
                id: warningEnergyBlinking

                property bool toRunOrNotToRun: false

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 2000
                from: 1
                to: 0.5
                targets: [
                    warningEnergyText
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
        TextInput {
            id: energySetter

            x: 90
            y: 10
            width: 300
            height: 100

            color: "#94ef94"
            font.pixelSize: 100
            font.family: fontStencil.name
        }

        Component.onCompleted: {
            warningEnergyText.startShowing();
        }
    }
    Item {
        id: buildingMaterials

        x: armour.x + armour.width + 4
        y: weapon1.y + weapon1.height/2 - 45

        Image {
            id: buildingMaterialsIcon

            x: -10
            y: -10
            width: 120
            height: width

            source: "qrc:/graphics/GUI/Buildingmaterials.png"
        }
        Text {
            id: warningBuildingMaterialsText

            property bool isShowing: false

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            text: "Tip: at least 10 materials recommended."
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            function startShowing()
            {
                if (isShowing == false)
                {
                    warningBuildingMaterialsFadeOut.start();
                    warningBuildingMaterialsBlinking.toRunOrNotToRun=true;
                    warningBuildingMaterialsBlinking.start();
                    isShowing=true;
                }
            }
            function stopShowing()
            {
                if (isShowing == true)
                {
                    warningBuildingMaterialsFadeIn.start();
                    warningBuildingMaterialsBlinking.toRunOrNotToRun=false;
                    warningBuildingMaterialsBlinking.stop();
                    isShowing=false;
                }
            }

            NumberAnimation {
                id: warningBuildingMaterialsFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                targets: [
                    warningBuildingMaterialsText
                ]
            }
            NumberAnimation {
                id: warningBuildingMaterialsFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                targets: [
                    warningBuildingMaterialsText
                ]
            }
            NumberAnimation {
                id: warningBuildingMaterialsBlinking

                property bool toRunOrNotToRun: false

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 2000
                from: 1
                to: 0.5
                targets: [
                    warningBuildingMaterialsText
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
        TextInput {
            id: buildingMaterialsSetter

            x: 90
            y: 10
            width: 300
            height: 100

            color: "#94ef94"
            font.pixelSize: 100
            font.family: fontStencil.name
        }

        Component.onCompleted: {
            warningBuildingMaterialsText.startShowing();
        }
    }
    Item {
        id: foodSupplies

        x: armour.x + armour.width + 4
        y: weapon2.y + weapon2.height/2 - 45

        Image {
            id: foodSuppliesIcon

            x: 0
            y: -5
            width: 110
            height: width

            source: "qrc:/graphics/GUI/Foodsupplies.png"
        }
        Text {
            id: warningFoodSuppliesText

            property bool isShowing: false

            x: 280
            y: -40
            width: 540

            opacity: 0

            color: "#9f1e1e"
            text: "Tip: at least 10 food recommended."
            wrapMode: Text.WordWrap
            font.pixelSize: 55
            font.family: fontStencil.name
            horizontalAlignment: Text.AlignHCenter

            function startShowing()
            {
                if (isShowing == false)
                {
                    warningFoodSuppliesFadeOut.start();
                    warningFoodSuppliesBlinking.toRunOrNotToRun=true;
                    warningFoodSuppliesBlinking.start();
                    isShowing=true;
                }
            }
            function stopShowing()
            {
                if (isShowing == true)
                {
                    warningFoodSuppliesFadeIn.start();
                    warningFoodSuppliesBlinking.toRunOrNotToRun=false;
                    warningFoodSuppliesBlinking.stop();
                    isShowing=false;
                }
            }

            NumberAnimation {
                id: warningFoodSuppliesFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                targets: [
                    warningFoodSuppliesText
                ]
            }
            NumberAnimation {
                id: warningFoodSuppliesFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                targets: [
                    warningFoodSuppliesText
                ]
            }
            NumberAnimation {
                id: warningFoodSuppliesBlinking

                property bool toRunOrNotToRun: false

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 2000
                from: 1
                to: 0.5
                targets: [
                    warningFoodSuppliesText
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
        TextInput {
            id: foodSuppliesSetter

            x: 90
            y: 10
            width: 300
            height: 100

            color: "#94ef94"
            font.pixelSize: 100
            font.family: fontStencil.name
        }

        Component.onCompleted: {
            warningFoodSuppliesText.startShowing();
        }
    }

    Item {
        id: back

        x: 150
        y: parent.height - height
        width: 330
        height: backText.height

        Text {
            id: backText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "< Back"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backMA

            x: -20
            y: -20
            width: parent.width - 2*x
            height: parent.height - 2*y

            onClicked: {
                root.returnToDefault();
                root.backClicked();
            }
        }
    }

    Item {
        id: explore

        x: 560
        y: back.y - 10
        width: 330
        height: exploreText.height

        visible: true

        Text {
            id: exploreText

            height: font.pixelSize+8

            anchors.fill: parent
            color: "#94ef94"
            text: "Explore"
            font.pixelSize: 110
            font.family: fontStencil.name
        }
        MouseArea {
            id: exploreMA

            x: -20
            y: -20
            width: parent.width - 2*x
            height: parent.height - 2*y

            onClicked: root.exploreClicked();
        }
    }

    states: [
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        },
        State {
            name: "hiddenRight2"
            PropertyChanges { target: root; x: 2*width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

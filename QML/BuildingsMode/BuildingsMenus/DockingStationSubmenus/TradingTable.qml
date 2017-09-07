import QtQuick 2.9

import Game 1.0

Item {
    id: root

    width: 1080
    height: 491

    function reset()
    {
        buyAmount.value = 0;
        buyAmount.text = "0";

        forAmount.value = 0;
        forAmount.text = "0";

        warningText1.stopShowing();
        warningText2.stopShowing();
    }
    function update()
    {
        forAmount.calculate();

        if (buyRes.mode == 0)
        {
            if (buyAmount.value > GameApi.base.currentEnergyLimit() - GameApi.base.currentEnergyAmount())
                warningText1.startShowing();
            else
                warningText1.stopShowing();
        }
        else if (buyRes.mode == 1)
        {
            if (buyAmount.value > GameApi.base.currentFoodSuppliesLimit() - GameApi.base.currentFoodSuppliesAmount())
                warningText1.startShowing();
            else
                warningText1.stopShowing();
        }
        else if (buyRes.mode == 2)
        {
            if (buyAmount.value > GameApi.base.currentBuildingMaterialsLimit() - GameApi.base.currentBuildingMaterialsAmount())
                warningText1.startShowing();
            else
                warningText1.stopShowing();
        }
        else
        {
            if (buyAmount.value > GameApi.base.currentAetheriteLimit() - GameApi.base.currentAetheriteAmount())
                warningText1.startShowing();
            else
                warningText1.stopShowing();
        }

        if (forRes.mode == 0)
        {
            if (forAmount.value > GameApi.base.currentEnergyAmount())
                warningText2.startShowing();
            else
                warningText2.stopShowing();
        }
        else if (forRes.mode == 1)
        {
            if (forAmount.value > GameApi.base.currentFoodSuppliesAmount())
                warningText2.startShowing();
            else
                warningText2.stopShowing();
        }
        else if (forRes.mode == 2)
        {
            if (forAmount.value > GameApi.base.currentBuildingMaterialsAmount())
                warningText2.startShowing();
            else
                warningText2.stopShowing();
        }
        else
        {
            if (forAmount.value > GameApi.base.currentAetheriteAmount())
                warningText2.startShowing();
            else
                warningText2.stopShowing();
        }
    }
    function returnToDefault()
    {
        buyRes.mode = 0;
        forRes.mode = 0;
        reset();
    }

    signal transactionAccepted(int sourceRes, int targetRes, int targetValue)//vals for res like mode (buyRes member) and enum

    Item {
        id: buyLine

        x: 0
        y: 0
        width: parent.width
        height: buyText.y + buyText.height + 10

        Text {
            id: buyText

            x: 200
            y: 10
            height: font.pixelSize

            color: "#94ef94"
            text: "Buy"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Text {
            id: buyAmount

            property int value: 0

            function add(amount)
            {
                value += amount;
                text = value;
                root.update();
            }
            function subtract(amount)
            {
                value = value-amount<0 ? 0 : value-amount;
                text = value;
                root.update();
            }

            x: 430
            y: 10
            height: font.pixelSize

            color: "#94ef94"
            text: "0"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Item {
            id: buySwitchL

            x: 600
            y: 10
            width: 30
            height: 80

            Text {
                id: buySwitchLText

                anchors.fill: parent

                color: "#94ef94"
                text: "<"
                wrapMode: Text.WordWrap
                font.pixelSize: 80
                font.family: fontStencil.name
            }
            MouseArea {
                id: buySwitchLMA

                x: -30
                width: 120
                height: 80

                onClicked: {
                    buyRes.mode = buyRes.mode-1<0 ? 3 : buyRes.mode-1;
                }
            }
        }
        Image {
            id: buyRes

            property int mode: 0

            x: buySwitchL.x + buySwitchL.width + 20
            y: 0
            width: buySwitchR.x - x - 20
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

            onModeChanged: {
                fadeIn.start();
            }

            NumberAnimation {
                id: fadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                target: buyRes
                onRunningChanged: {
                    if (running == false)
                    {
                        if (buyRes.mode == 0)
                            buyRes.source = "qrc:/graphics/GUI/Resources/Energy.png";
                        else if (buyRes.mode == 1)
                            buyRes.source = "qrc:/graphics/GUI/Resources/Foodsupplies.png";
                        else if (buyRes.mode == 2)
                            buyRes.source = "qrc:/graphics/GUI/Resources/Buildingmaterials.png";
                        else if (buyRes.mode == 3)
                            buyRes.source = "qrc:/graphics/GUI/Resources/Aetherite.png";

                        root.update();

                        fadeOut.start();
                    }
                }
            }
            NumberAnimation {
                id: fadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                target: buyRes
            }
        }
        Item {
            id: buySwitchR

            x: 750
            y: 10
            width: 30
            height: 80

            Text {
                id: buySwitchRText

                anchors.fill: parent

                color: "#94ef94"
                text: ">"
                wrapMode: Text.WordWrap
                font.pixelSize: 80
                font.family: fontStencil.name
            }
            MouseArea {
                id: buySwitchRMA

                x: -60
                y: 0
                width: 120
                height: 80

                onClicked: {
                    buyRes.mode = (buyRes.mode+1)%4;
                }
            }
        }
        Text {
            id: exclamationMark1

            x: 1040
            y: 0

            opacity: 0

            color: "#a00000"
            text: "!"
            wrapMode: Text.WordWrap
            font.pixelSize: 100
            font.family: fontStencil.name
        }
    }
    Text {
        id: warningText1

        property bool isShowing: false

        x: 50
        y: 80
        height: font.pixelSize + 4

        opacity: 0

        color: "#a00000"
        text: "Warning: Your capacity isn't big enough"
        wrapMode: Text.WordWrap
        font.pixelSize: 46
        font.family: fontStencil.name

        function startShowing()
        {
            if (isShowing == false)
            {
                warning1FadeOut.start();
                warning1Blinking.toRunOrNotToRun=true;
                warning1Blinking.start();
                isShowing=true;
            }
        }
        function stopShowing()
        {
            if (isShowing == true)
            {
                warning1FadeIn.start();
                warning1Blinking.toRunOrNotToRun=false;
                warning1Blinking.stop();
                isShowing=false;
            }
        }

        NumberAnimation {
            id: warning1FadeIn

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            targets: [
                warningText1,
                exclamationMark1
            ]
        }
        NumberAnimation {
            id: warning1FadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 0
            to: 1
            targets: [
                warningText1,
                exclamationMark1
            ]
        }
        NumberAnimation {
            id: warning1Blinking

            property bool toRunOrNotToRun: false

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 500
            from: 1
            to: 0.5
            targets: [
                warningText1,
                exclamationMark1
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
    Item {
        id: amountLine

        x: 10
        y: warningText1.y + warningText1.height
        height: 84

        Item {
            id: minus100

            x: 25
            width: 163
            height: 84

            Text {
                color: "#a00000"
                text: "-100"
                wrapMode: Text.WordWrap
                font.pixelSize: 74
                font.family: fontStencil.name
            }
            MouseArea {
                anchors.fill: parent

                onClicked: buyAmount.subtract(100)
            }
        }
        Item {
            id: minus10

            x: 250
            width: 107
            height: 84

            Text {
                color: "#a00000"
                text: "-10"
                wrapMode: Text.WordWrap
                font.pixelSize: 74
                font.family: fontStencil.name
            }
            MouseArea {
                anchors.fill: parent

                onClicked: buyAmount.subtract(10)
            }
        }
        Item {
            id: minus1

            x: 419
            width: 66
            height: 84

            Text {
                color: "#a00000"
                text: "-1"
                wrapMode: Text.WordWrap
                font.pixelSize: 74
                font.family: fontStencil.name
            }
            MouseArea {
                anchors.fill: parent

                onClicked: buyAmount.subtract(1)
            }
        }
        Item {
            id: plus1

            x: 547
            width: 66
            height: 84

            Text {
                color: "#94ef94"
                text: "+1"
                wrapMode: Text.WordWrap
                font.pixelSize: 74
                font.family: fontStencil.name
            }
            MouseArea {
                anchors.fill: parent

                onClicked: buyAmount.add(1)
            }
        }
        Item {
            id: plus10

            x: 685
            width: 107
            height: 84

            Text {
                color: "#94ef94"
                text: "+10"
                wrapMode: Text.WordWrap
                font.pixelSize: 74
                font.family: fontStencil.name
            }
            MouseArea {
                anchors.fill: parent

                onClicked: buyAmount.add(10)
            }
        }
        Item {
            id: plus100

            x: 864
            width: 163
            height: 84

            Text {
                color: "#94ef94"
                text: "+100"
                wrapMode: Text.WordWrap
                font.pixelSize: 74
                font.family: fontStencil.name
            }
            MouseArea {
                anchors.fill: parent

                onClicked: buyAmount.add(100)
            }
        }
    }
    Text {
        id: warningText2

        property bool isShowing: false

        x: 270
        y: amountLine.y + amountLine.height + 4
        height: font.pixelSize + 4

        opacity: 0

        color: "#a00000"
        text: "You cannot afford this"
        wrapMode: Text.WordWrap
        font.pixelSize: 46
        font.family: fontStencil.name

        function startShowing()
        {
            if (isShowing == false)
            {
                warning2FadeOut.start();
                warning2Blinking.toRunOrNotToRun=true;
                warning2Blinking.start();
                isShowing=true;
            }
        }
        function stopShowing()
        {
            if (isShowing == true)
            {
                warning2FadeIn.start();
                warning2Blinking.toRunOrNotToRun=false;
                warning2Blinking.stop();
                isShowing=false;
            }
        }

        NumberAnimation {
            id: warning2FadeIn

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 1
            to: 0
            targets: [
                warningText2,
                exclamationMark2
            ]
        }
        NumberAnimation {
            id: warning2FadeOut

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 300
            from: 0
            to: 1
            targets: [
                warningText2,
                exclamationMark2
            ]
        }
        NumberAnimation {
            id: warning2Blinking

            property bool toRunOrNotToRun: false

            properties: "opacity"
            easing.type: Easing.InQuad
            duration: 500
            from: 1
            to: 0.5
            targets: [
                warningText2,
                exclamationMark2
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
    Item {
        id: forLine

        x: 0
        y: warningText2.y + warningText2.height
        width: parent.width
        height: forText.y + forText.height + 10

        Text {
            id: forText

            x: 200
            y: 10
            height: font.pixelSize

            color: "#94ef94"
            text: "For"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Text {
            id: forAmount

            property int value: 0

            function calculate()
            {
                value = GameApi.base.dockingStation.calculateTransaction(forRes.mode, buyRes.mode, buyAmount.value);
                text = value;
            }

            x: 430
            y: 10
            height: font.pixelSize

            color: "#94ef94"
            text: "0"
            wrapMode: Text.WordWrap
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Item {
            id: forSwitchL

            x: 600
            y: 10
            width: 30
            height: 80

            Text {
                id: forSwitchLText

                anchors.fill: parent

                color: "#94ef94"
                text: "<"
                wrapMode: Text.WordWrap
                font.pixelSize: 80
                font.family: fontStencil.name
            }
            MouseArea {
                id: forSwitchLMA

                x: -30
                width: 120
                height: 80

                onClicked: {
                    forRes.mode = forRes.mode-1<0 ? 3 : forRes.mode-1;
                }
            }
        }
        Image {
            id: forRes

            property int mode: 0

            x: forSwitchL.x + forSwitchL.width + 20
            y: 0
            width: forSwitchR.x - x - 20
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

            onModeChanged: {
                forFadeIn.start();
            }

            NumberAnimation {
                id: forFadeIn

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 1
                to: 0
                target: forRes
                onRunningChanged: {
                    if (running == false)
                    {
                        if (forRes.mode == 0)
                            forRes.source = "qrc:/graphics/GUI/Resources/Energy.png";
                        else if (forRes.mode == 1)
                            forRes.source = "qrc:/graphics/GUI/Resources/Foodsupplies.png";
                        else if (forRes.mode == 2)
                            forRes.source = "qrc:/graphics/GUI/Resources/Buildingmaterials.png";
                        else if (forRes.mode == 3)
                            forRes.source = "qrc:/graphics/GUI/Resources/Aetherite.png";

                        root.update();

                        forFadeOut.start();
                    }
                }
            }
            NumberAnimation {
                id: forFadeOut

                properties: "opacity"
                easing.type: Easing.InQuad
                duration: 300
                from: 0
                to: 1
                target: forRes
            }
        }
        Item {
            id: forSwitchR

            x: 750
            y: 10
            width: 30
            height: 80

            Text {
                id: forSwitchRText

                anchors.fill: parent

                color: "#94ef94"
                text: ">"
                wrapMode: Text.WordWrap
                font.pixelSize: 80
                font.family: fontStencil.name
            }
            MouseArea {
                id: forSwitchRMA

                x: -60
                y: 0
                width: 120
                height: 80

                onClicked: {
                    forRes.mode = (forRes.mode+1)%4;
                }
            }
        }
        Text {
            id: exclamationMark2

            x: 1040
            y: 0

            opacity: 0

            color: "#a00000"
            text: "!"
            wrapMode: Text.WordWrap
            font.pixelSize: 100
            font.family: fontStencil.name
        }
    }
    Item {
        id: buttonsLine

        y: forLine.y + forLine.height

        Item {
            id: acceptButton

            x: 290
            y: -10
            width: 120
            height: width

            Image {
                id: acceptImage

                anchors.fill: parent

                source: "qrc:/graphics/GUI/Settings.png"
            }
            MouseArea {
                id: acceptMA

                anchors.fill: parent

                onClicked: {
                    if (!warningText2.isShowing)
                    {
                        transactionAccepted(forRes.mode, buyRes.mode, buyAmount.value);
                        reset();
                    }
                }
            }
        }
        Item {
            id: abortButton

            x: 680
            width: 100
            height: width

            Image {
                id: abortImage

                anchors.fill: parent

                source: "qrc:/graphics/GUI/Abort.png"
            }
            MouseArea {
                id: abortMA

                anchors.fill: parent

                onClicked: reset();
            }
        }
    }
    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

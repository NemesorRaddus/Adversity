import QtQuick 2.9

import Game 1.0
import ".."

Item {
    id: root

    readonly property int theoreticalWidth: 1080
    readonly property int theoreticalHeight: 1464

    signal backClicked()
    signal upgradeRequested()
    signal mercenariesModeUpdateRequested()

    function updateEverything()
    {
        topBar.setDescription(GameApi.base.buildings.gym.description());
        topBar.setLevel("Level: "+GameApi.base.buildings.gym.currentLevel());
        table.update();
        upgradeInfo.update();
        mercenarySelectionList.updateEverything("pr");
        var amountOfSlotsAvailable = GameApi.base.buildings.gym.amountOfSlots();
        if (amountOfSlotsAvailable>=1)
        {
            if (GameApi.base.buildings.gym.mercenaryNameInSlot(0)!="")
            {
                slotView1.mercenaryName=GameApi.base.buildings.gym.mercenaryNameInSlot(0);
                slotView1.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.gym.mercenaryProfessionInSlot(0))+"/"+GameApi.base.buildings.gym.mercenaryNameInSlot(0)+".png",GameApi.base.buildings.gym.useCostInEnergySingle(), GameApi.base.buildings.gym.remainingDaysOfTraining(GameApi.base.buildings.gym.mercenaryNameInSlot(0))+1);
                slotView1.forceAbortIcon();
            }
            else
                slotView1.removeMercenary();
            slotView1.visible=true;
            if (amountOfSlotsAvailable>=2)
            {
                if (GameApi.base.buildings.gym.mercenaryNameInSlot(1)!="")
                {
                    slotView2.mercenaryName=GameApi.base.buildings.gym.mercenaryNameInSlot(1);
                    slotView2.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.gym.mercenaryProfessionInSlot(1))+"/"+GameApi.base.buildings.gym.mercenaryNameInSlot(1)+".png",GameApi.base.buildings.gym.useCostInEnergySingle(), GameApi.base.buildings.gym.remainingDaysOfTraining(GameApi.base.buildings.gym.mercenaryNameInSlot(1))+1);
                    slotView2.forceAbortIcon();
                }
                else
                    slotView2.removeMercenary();
                slotView2.visible=true;
                if (amountOfSlotsAvailable>=3)
                {
                    if (GameApi.base.buildings.gym.mercenaryNameInSlot(2)!="")
                    {
                        slotView3.mercenaryName=GameApi.base.buildings.gym.mercenaryNameInSlot(2);
                        slotView3.setMercenaryTwoVals("qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.buildings.gym.mercenaryProfessionInSlot(2))+"/"+GameApi.base.buildings.gym.mercenaryNameInSlot(2)+".png",GameApi.base.buildings.gym.useCostInEnergySingle(), GameApi.base.buildings.gym.remainingDaysOfTraining(GameApi.base.buildings.gym.mercenaryNameInSlot(2))+1);
                        slotView3.forceAbortIcon();
                    }
                    else
                        slotView3.removeMercenary();
                    slotView3.visible=true;
                }
                else
                    slotView3.visible=false;
            }
            else
            {
                slotView2.visible=false;
                slotView3.visible=false;
            }
        }
        else
        {
            slotView1.visible=false;
            slotView2.visible=false;
            slotView3.visible=false;
        }
    }

    function reactToBackOnToolbar()
    {
        if (mercenarySelectionList.state == "")
        {
            mercenarySelectionList.state = "hidden";
            return true;
        }
        else
        {
            if (!slotView1.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView1.mercenaryName);
                slotView1.removeMercenary();
            }
            if (!slotView2.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView2.mercenaryName);
                slotView2.removeMercenary();
            }
            if (!slotView3.isConfirmed)
            {
                mercenarySelectionList.unbanMercenary(slotView3.mercenaryName);
                slotView3.removeMercenary();
            }
            return false;
        }
    }

    function returnToDefault()
    {
        if (!slotView1.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView1.mercenaryName);
            slotView1.removeMercenary();
        }
        if (!slotView2.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView2.mercenaryName);
            slotView2.removeMercenary();
        }
        if (!slotView3.isConfirmed)
        {
            mercenarySelectionList.unbanMercenary(slotView3.mercenaryName);
            slotView3.removeMercenary();
        }
        mercenarySelectionList.state = "hidden";
    }

    function requestUnban(mercenaryName)
    {
        mercenarySelectionList.unbanMercenary(mercenaryName);
    }

    width: 1080
    height: 1464

//    transform: [
//        Scale {
//            id: someScale

//            xScale: width/theoreticalWidth
//            yScale: height/theoreticalHeight
//        },
//        Translate {
//            x: (width-theoreticalWidth*someScale.xScale)/2
//            y: (height-theoreticalHeight*someScale.yScale)/2
//        }
//    ]

    Rectangle {
        id: darkness

        anchors.fill: parent

        color: "#171717"
    }

    Image {
        id: background

        anchors.fill: parent

        source: "qrc:/graphics/GUI/Upgrade/Upgrade.png"
    }

    Text {

        y: 10
        width: parent.width-10
        color: "#94ef94"
        text: "info & upgrades"
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 120
        font.family: fontStencil.name

    }

    Item {

        id: currentLevel

        y: 160
        width: parent.width

        Text {

            width: parent.width - 10
            color: "#94ef94"
            text: "Current level"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 100
            font.family: fontStencil.name

        }

        Image {

            x: 17
            y: 110

            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Text {

            x:20
            y: 116
            color: "#94ef94"
            text: "Daily Power usage:\nDaily Training Power Usage:\nTraining effect:\nTraining duration:"
            font.pixelSize: 50
            font.family: fontStencil.name
        }

        Image {

            x:778
            y:119
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

        }

        Image {

            x:778
            y:179
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

        }

        Image {

            x:778
            y:239
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Attributes/CE.png"

        }

        Image {

            x:778
            y:299
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Time.png"

        }

        Text {

            id: energyCostC

            x: 830
            y: 116
            width: parent.width - x
            color: "#94ef94"
            text: "X/day"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

            id: energyCostTrainingC

            x: 830
            y: 176
            width: parent.width - x
            color: "#94ef94"
            text: "X/day"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

           //ten text nie potrzebuje id bo i tak nigdy sie nie zmienia

            x: 830
            y: 236
            width: parent.width - x
            color: "#94ef94"
            text: "+1 CE"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

            id: timeTrainingC

            x: 830
            y: 296
            width: parent.width - x
            color: "#94ef94"
            text: "X"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }
    }

    Item {

        id: nextLevel

        y: 530
        width: parent.width

        Text {

            width: parent.width - 10
            color: "#94ef94"
            text: "Next level"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 100
            font.family: fontStencil.name

        }

        Image {

            x: 17
            y: 110

            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Text {

            x:20
            y: 116
            color: "#94ef94"
            text: "Daily Power usage:\nDaily Training Power Usage:\nTraining effect:\nTraining duration:"
            font.pixelSize: 50
            font.family: fontStencil.name
        }

        Image {

            x:778
            y:119
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

        }

        Image {

            x:778
            y:179
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

        }

        Image {

            x:778
            y:239
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Attributes/CE.png"

        }

        Image {

            x:778
            y:299
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Time.png"

        }

        Text {

            id: energyCostU

            x: 830
            y: 116
            width: parent.width - x
            color: "#94ef94"
            text: "X/day"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

            id: energyCostTrainingU

            x: 830
            y: 176
            width: parent.width - x
            color: "#94ef94"
            text: "X/day"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

           //ten text nie potrzebuje id bo i tak nigdy sie nie zmienia

            x: 830
            y: 236
            width: parent.width - x
            color: "#94ef94"
            text: "+1 CE"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

            id: timeTrainingU

            x: 830
            y: 296
            width: parent.width - x
            color: "#94ef94"
            text: "X"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }
    }

    Item {

        id: upgrade

        y: 900
        width: parent.width

        Text {

            width: parent.width - 10
            color: "#94ef94"
            text: "Upgrade"
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 100
            font.family: fontStencil.name

        }

        Image {

            x: 17
            y: 110

            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        Text {

            id: upgradeText

            x:20
            y: 116
            color: "#94ef94"
            text: "Energy cost:\nBuilding Materials Cost:\nUpgrade Duration:"
            font.pixelSize: 50
            font.family: fontStencil.name
        }

        Image {

            x:778
            y:119
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

        }

        Image {

            x:778
            y:179
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Resources/Buildingmaterials.png"

        }

        Image {

            x:778
            y:239
            width: 50
            height: width

            source: "qrc:/graphics/GUI/Time.png"

        }

        Text {

            id: energyCostUp

            x: 830
            y: 116
            width: parent.width - x
            color: "#94ef94"
            text: "X"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

            id: meterialsCostUp

            x: 830
            y: 176
            width: parent.width - x
            color: "#94ef94"
            text: "X"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Text {

            id: timeUp

            x: 830
            y: 236
            width: parent.width - x
            color: "#94ef94"
            text: "X"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 50
            font.family: fontStencil.name

        }

        Item {

            //do tego Itemu ma być przypisana standarowa animacja obrotu tak jak w innych zebatkach po kliknieciu.
            //natomiast nowoscia jest to, ze gdy trwa ulepszanie zawartosc textu "upgradeText" zmienia swoj fragment "Upgrade Duration:"
            //na "Days left:" a liczba dni staje sie licznikiem. Zaoszczedzi nam to sporo miejsca i zwiekszy czytelnosc :D

            id: upgradeButton

            x: (parent.width - width)/2
            y: 300
            width: 150
            height: 150

            Image {

                id: upgradeImage

                anchors.fill: parent

                source: "qrc:/graphics/MainMenu/Settings.png"

            }

            MouseArea {

                id: upgradeMA

                anchors.fill: parent
                anchors.margins: -20

            }
        }
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

            anchors.fill: parent

            onClicked: {
                if (mercenarySelectionList.state == "hidden")
                {
                    if (!slotView1.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView1.mercenaryName);
                        slotView1.removeMercenary();
                    }
                    if (!slotView2.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView2.mercenaryName);
                        slotView2.removeMercenary();
                    }
                    if (!slotView3.isConfirmed)
                    {
                        mercenarySelectionList.unbanMercenary(slotView3.mercenaryName);
                        slotView3.removeMercenary();
                    }
                    backClicked();
                }
                else
                {
                    if (slotsView.indexOfChangingSlot==0)
                        mercenarySelectionList.banMercenary(slotView1.mercenaryName);
                    else if (slotsView.indexOfChangingSlot==1)
                        mercenarySelectionList.banMercenary(slotView2.mercenaryName);
                    else if (slotsView.indexOfChangingSlot==2)
                        mercenarySelectionList.banMercenary(slotView3.mercenaryName);
                    mercenarySelectionList.state = "hidden";
                }
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

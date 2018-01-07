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

    Rectangle {
        id: darkness

        anchors.fill: parent

        color: "#171717"
    }

    Image {
        id: background

        anchors.fill: parent

        source: "qrc:/graphics/GUI/TrainingGround/TrainingGround_Background.png"
    }

    Text {

        y: 10
        width: parent.width-10
        color: "#94ef94"
        text: "Training"
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 140
        font.family: fontStencil.name

    }

    Text {

        x: parent.width - 810
        y: 170
        width: 800
        color: "#94ef94"
        text: "Practice on the Training Ground\nincreases mercenary's\nreaction times and\ncombatskills.\n\nNoticable performance\nimprovements appear\nafter X days of\ntraining."
        // X ma być podmieniony przez obecna wartosc czasu treningu
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 55
        font.family: fontStencil.name

    }

    Text {

        id: mercenaryPick

        x: 320
        y: 756
        width: 700
        color: "#94ef94"
        text: "Choose a mercenary\nto train"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 55
        font.family: fontStencil.name

    }

    Item{

        id: mercenarySlot

        x: 539
        y: 901
        width: 262
        height: width

        Image{

            id: mercenaryArt

            x: 3
            y: 3
            width: 256
            height: width

            source: "qrc:/graphics/Mercs/Gunzerker/PaulLuft.png"
        }

        Image{

            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture.png"

        }

        MouseArea{

            anchors.fill: parent
        }
    }

    Item{
        //Ten item ma sie pokazywac wylacznie gdy w slocie jest jakis najemnik, i ma sie pojawiac fade'em trwajacym 200ms
        id: resources

        x: 235
        y: 950
        width: 298
        height: 164

        Image{

            width: 70
            height: width

            source: "qrc:/graphics/GUI/Resources/Energy.png"

        }

        Image{

            y: 90
            width: 70
            height: width

            source: "qrc:/graphics/GUI/Time.png"
        }

        Text{

            id: energy

            x: 85
            y: 8
            width: 207
            height: 65
            color: "#94ef94"
            text: "X/day"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 55
            font.family: fontStencil.name
        }

        Text{

            id: time

            x: 85
            y: 93
            width: 207
            height: 65
            color: "#94ef94"
            text: "X"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 55
            font.family: fontStencil.name

        }
    }

    Item{

        // Gdy trening zostaje rozpoczety, to ten item znika. Pojawia sie i znika i ma sie pojawiac fade'em trwajacym 200ms. Obraz nizej jest "nemezis" tego napisu. Gdy znika napis, pojawia sie obraz z animacja.
        id: begin

        x: 551
        y: 1191
        width: 240
        height: 95

        Text{

            id: beginText


            width: parent
            color: "#94ef94"
            text: "Begin"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 80
            font.family: fontStencil.name

        }

        MouseArea{

            anchors.fill: parent

            anchors.margins: -10
        }
    }

    Image{
        id: usedAnimation
        x: 615
        y: 1183
        width: 111
        height: width

        source: "qrc:/graphics/GUI/TrainingGround/Animation0.png"

        //Tu ma byc animacja operujaca na stanach. Stanow jest 5 i stosunek ich dlugosci to:
        // 10:1:1:1:1
        // jednostka przez ktora bedziemy mnozyli jest do ustalenia ale poczatkowo mozemy wziac 50 ms.
        // obrazki ida rosnaco numerami obrazow. Czyli: 0:1:2:3:4:
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

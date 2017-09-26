import QtQuick 2.9

import "qrc:/qml/MissionsMode/MissionsList/MissionsListScripts.js" as Scripts
import "../.."
import ".."
import Game 1.0

Item {
    id: root

    function update()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();
        fade.duration = fade.baseDuration * GameApi.animMultiplier();

        var am=GameApi.base.amountOfMissions();
        Scripts.setupList(am,width,height);
        for (var i=0;i<am;++i)
        {
            GameApi.base.prepareMission(i);
            var n=GameApi.base.preparedMission.hero.name();
            var p=GameApi.base.preparedMission.hero.professionString();

            Scripts.createItem(GameApi.tr(n),p,
                               "qrc:/graphics/Mercs/"+GameApi.globalsCpp.alterNormalTextToInternal(p)+"/"+n+".png",
                               GameApi.base.preparedMission.land.name(),
                               GameApi.base.preparedMission.difficultyString(),
                               GameApi.base.preparedMission.fullDuration()-GameApi.base.preparedMission.remainingDays(),
                               GameApi.base.preparedMission.hero.isCommunicationAvailable(),
                               GameApi.base.preparedMission.hero.isStressBorderEffectActive(),
                               GameApi.base.preparedMission.hero.health(),
                               GameApi.base.preparedMission.hero.healthLimit(),
                               GameApi.base.preparedMission.hero.stress(),
                               GameApi.base.preparedMission.hero.stressLimit());
        }
    }

    function returnToDefault()
    {
        Scripts.scrollList(999999);
    }

    function show()
    {
        update();
        state = "";
        mouseArea.visible = true;
        backMA.visible = true;
    }

    function hide()
    {
        state = "hidden";
        mouseArea.visible = false;
        backMA.visible = false;
    }

    function doFading()
    {
        fade.start();
    }

    width: 1080
    height: 1440

    state: "hidden"

    property int startY

    clip: true

    signal selected(string name)
    signal backClicked()

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Item {
        id: listHandler

        x: 0
        y: 0
        width: parent.width
        height: taskBorder.y

        clip: true

        NumberAnimation {
            id: fade

            properties: "opacity"
            easing.type: Easing.InQuad
            property int baseDuration: 300
            duration: baseDuration
            from: 1
            to: 0
            target: listHandler
            running: false
            onRunningChanged: {
                if (running == false)
                {
                    if (from == 1)
                    {
                        root.update();
                        from = 0;
                        to = 1;
                        start();
                    }
                    else
                    {
                        from = 1;
                        to = 0;
                    }
                }
            }
        }
    }

    MouseArea {
        id: mouseArea

        readonly property int yChangedThresholdForScrolling: 1 // percent; <0;100>; after moving mouse up or down by this percent of screen height, scrolling mode will be activated and mouse release will no longer cause click - instead after each y change list will be scrolled

        property int y0: -1
        property bool isScrollingActive: false

        x: 0
        y: 0
        width: parent.width
        height: parent.height

        visible: false

        onPressed: {
            y0 = mouseY;
            movementCheckTimer.start();
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
            else
            {
                var e=Scripts.getClickedItemName(y0);
                if (e != "")
                    selected(e);
            }
            y0 = -1;
            movementCheckTimer.stop();
        }

        Timer {
            id: movementCheckTimer

            interval: 16
            repeat: true
            running: false

            onTriggered: {
                if (mouseArea.isScrollingActive == true)
                {
                    Scripts.scrollList(Math.ceil(mouseArea.mouseY) - mouseArea.y0);

                    mouseArea.y0 = Math.ceil(mouseArea.mouseY);
                }
                else
                {
                    if (Math.abs(mouseArea.mouseY - mouseArea.y0) >= Globals.windowHeight * mouseArea.yChangedThresholdForScrolling / 100)
                    {
                        mouseArea.isScrollingActive = true;
                        Scripts.scrollList(mouseArea.mouseY - mouseArea.y0);
                        mouseArea.y0 = mouseArea.mouseY;
                    }
                }
            }
        }
    }

    Image {
        id: taskBorder

        x: 14
        y: back.y - 8
        width: 1046
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        id: back

        x: 0
        y: root.height - height + 15
        width: root.width
        height: backText.font.pixelSize + 6

        Text {
            id: backText

            anchors.fill: parent

            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backMA

            visible: false

            anchors.rightMargin: 383
            anchors.bottomMargin: 0
            anchors.leftMargin: 383
            anchors.topMargin: 0

            anchors.fill: parent

            onClicked: root.backClicked()
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; opacity: 0 }
        },
        State {
            name: "hiddenUp"
            PropertyChanges { target: root; y: -height }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "opacity,y"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 300 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

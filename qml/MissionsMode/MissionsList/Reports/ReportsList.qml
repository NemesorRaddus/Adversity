import QtQuick 2.9

import "qrc:/qml/MissionsMode/MissionsList/Reports/ReportsListScripts.js" as Scripts
import "../../.."

import Game 1.0

Item {
    id: root

    width: 1080
    height: 1440

    property string name_

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        var am=GameApi.base.mercenaries.mercenaries.amountOfMercenaries();
        var intName = GameApi.globalsCpp.alterNormalTextToInternal(name_);
        for (var i=0;i<am;++i)
        {
            GameApi.base.mercenaries.mercenaries.prepareMercenaryAt(i);
            if (GameApi.base.mercenaries.mercenaries.preparedMercenary.name() == intName)
            {
                var am2=GameApi.base.mercenaries.mercenaries.preparedMercenary.assignedMission.amountOfReports();
                Scripts.setupList(am2, width, height);
                for (var j=am2-1;j>=0;--j)
                {
                    GameApi.base.mercenaries.mercenaries.preparedMercenary.assignedMission.prepareReport(j);
                    Scripts.createItem(GameApi.base.mercenaries.mercenaries.preparedMercenary.assignedMission.preparedReport.timestamp(), GameApi.base.mercenaries.mercenaries.preparedMercenary.assignedMission.preparedReport.msg(), GameApi.base.mercenaries.mercenaries.preparedMercenary.assignedMission.preparedReport.artSource());
                }
            }
        }
    }

    function returnToDefault()
    {
        Scripts.scrollList(999999);
    }

    function setMercenary(name)
    {
        name_=name;
        updateEverything();
    }

    property int startY

    clip: true

    MouseArea {
        id: mouseArea

        readonly property int yChangedThresholdForScrolling: 1 // percent; <0;100>; after moving mouse up or down by this percent of screen height, scrolling mode will be activated and mouse release will no longer cause click - instead after each y change list will be scrolled

        property int y0: -1
        property bool isScrollingActive: false

        anchors.fill: parent

        onPressed: {
            y0 = mouseY;
            movementCheckTimer.start();
        }

        onReleased: {
            if (isScrollingActive == true)
                isScrollingActive = false;
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

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -width }
        },
        State {
            name: "hiddenLeft2"
            PropertyChanges { target: root; x: -2*width }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "x"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

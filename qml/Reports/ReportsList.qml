import QtQuick 2.9

import "qrc:/qml/Reports/ReportsListScripts.js" as Scripts
import ".."
import Game 1.0

Item {
    id: root

    width: 1080
    height: 1440

    signal backClicked()

    function updateEverything()
    {
        var am=GameApi.base.amountOfReports();
        Scripts.setupList(am, width, back.y);
        for (var i=am-1;i>=0;--i)
        {
            GameApi.base.prepareReport(i);
            Scripts.createItem(GameApi.base.preparedReport.timestamp(), GameApi.base.preparedReport.msg(), GameApi.base.preparedReport.artSource());
        }
    }

    function reactToBackOnToolbar()
    {
        return false;
    }

    function returnToDefault()
    {
        Scripts.scrollList(999999);
    }

    property int startY

    state: "hidden"

    Rectangle {
        anchors.fill: parent
        color: "#171717"
    }

    Item {
        id: reportsHandler

        x: 0
        y: 0
        width: parent.width
        height: back.y

        clip: true
    }

    MouseArea {
        id: mouseArea

        anchors.fill: reportsHandler

        readonly property int yChangedThresholdForScrolling: 1 // percent; <0;100>; after moving mouse up or down by this percent of screen height, scrolling mode will be activated and mouse release will no longer cause click - instead after each y change list will be scrolled

        property int y0: -1
        property bool isScrollingActive: false

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

    Image {
        id: taskBorder

        x: 17
        y: back.y
        width: 1046
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        id: back

        x: 0
        y: parent.height - height
        width: parent.width
        height: backText.height

        Text {
            id: backText

            height: font.pixelSize+8

            horizontalAlignment: Text.AlignHCenter

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            font.pixelSize: 100
            font.family: fontStencil.name
        }
        MouseArea {
            id: backMA
            anchors.rightMargin: 375
            anchors.leftMargin: 375

            anchors.fill: parent

            onClicked: {
                root.returnToDefault();
                root.backClicked();
            }
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; y: -1 * height }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 500 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

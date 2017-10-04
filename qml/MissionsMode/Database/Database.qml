import QtQuick 2.9

import "qrc:/qml/MissionsMode/Database/DatabaseScripts.js" as Scripts
import "../.."
import ".."
import Game 1.0

Item {
    id: root

    property string category: ""

    function update()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        Scripts.scrollList(9999);
        if (category == "")
        {
            Scripts.setupList(4, width, taskBorder.y);

            GameApi.base.database.prepareCategory("Animals");
            if (GameApi.base.database.amountOfEntriesInCurrentCategory()>0)
                Scripts.createItem("Animals", "qrc:/graphics/Database/Animals/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.database.nameOfEntry(GameApi.randomize(0,GameApi.base.database.amountOfEntriesInCurrentCategory()-1)))+".png");
            else
                Scripts.createItem("Animals","qrc:/graphics/GUI/Background.png");

            GameApi.base.database.prepareCategory("Plants");
            if (GameApi.base.database.amountOfEntriesInCurrentCategory()>0)
                Scripts.createItem("Plants", "qrc:/graphics/Database/Plants/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.database.nameOfEntry(GameApi.randomize(0,GameApi.base.database.amountOfEntriesInCurrentCategory()-1)))+".png");
            else
                Scripts.createItem("Plants","qrc:/graphics/GUI/Background.png");

            GameApi.base.database.prepareCategory("Fungi");
            if (GameApi.base.database.amountOfEntriesInCurrentCategory()>0)
                Scripts.createItem("Fungi", "qrc:/graphics/Database/Fungi/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.database.nameOfEntry(GameApi.randomize(0,GameApi.base.database.amountOfEntriesInCurrentCategory()-1)))+".png");
            else
                Scripts.createItem("Fungi","qrc:/graphics/GUI/Background.png");

            GameApi.base.database.prepareCategory("Lands");
            if (GameApi.base.database.amountOfEntriesInCurrentCategory()>0)
                Scripts.createItem("Lands", "qrc:/graphics/Database/Lands/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.database.nameOfEntry(GameApi.randomize(0,GameApi.base.database.amountOfEntriesInCurrentCategory()-1)))+".png");
            else
                Scripts.createItem("Lands","qrc:/graphics/GUI/Background.png");
        }
        else
            changeCategory(category);
    }

    function returnToDefault()
    {
        Scripts.scrollList(3000);
        category = "";
        update();
    }

    function reactToBackOnToolbar()
    {
        backClicked();
        return true;
    }

    function changeCategory(catName)
    {
        GameApi.base.database.prepareCategory(catName);
        Scripts.setupList(GameApi.base.database.amountOfEntriesInCurrentCategory(), width, taskBorder.y);
        for (var i=0;i<GameApi.base.database.amountOfEntriesInCurrentCategory();++i)
            Scripts.createItem(GameApi.base.database.nameOfEntry(i), "qrc:/graphics/Database/"+GameApi.globalsCpp.alterNormalTextToInternal(catName)+"/"+GameApi.globalsCpp.alterNormalTextToInternal(GameApi.base.database.nameOfEntry(i))+".png");
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

    state: "hidden"

    property int startY

    clip: true

    signal selected(string name, string type)
    signal backClicked()

    width: 1080
    height: 1440

    Image {
        id: additionalBackground

        anchors.fill: parent

        source: "qrc:/graphics/GUI/Background.png"
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
            duration: 300
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
                var e=Scripts.getClickedItemName(mouseX,y0);
                if (e != "")
                {
                    if (root.category == "")
                    {
                        root.category = e;
                        root.doFading();
                    }
                    else
                        root.selected(e, root.category);
                }
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

    transitions: [
        Transition {
            NumberAnimation { id: transitionRoot; properties: "opacity,y"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 300 }
        }
    ]

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

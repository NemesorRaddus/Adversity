import QtQuick 2.9

import "qrc:/qml/BuildingsMode/BuildingCategoriesCategoriesScripts.js" as CategoriesScripts
import "qrc:/qml/BuildingsMode/BuildingsListScripts.js" as BuildingsScripts
import "../.."
import ".."
import Game 1.0

Item {
    id: root

    property string category: ""

    function update()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        CategoriesScripts.scrollList(9999);
        if (category == "")
        {
            CategoriesScripts.setupList(4, width, taskBorder.y);

            CategoriesScripts.createItem("General", "qrc:/graphics/Buildings/CentralUnit.png");
            CategoriesScripts.createItem("Industrial sector", "qrc:/graphics/Buildings/Powerplant.png");
            CategoriesScripts.createItem("Mercenaries care", "qrc:/graphics/Buildings/Hospital.png");
            CategoriesScripts.createItem("Mercenaries training", "qrc:/graphics/Buildings/Laboratory.png");
        }
        else
            changeCategory(category);
    }

    function returnToDefault()
    {
        CategoriesScripts.scrollList(3000);
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
        if (catName === "General")
        {
            BuildingsScripts.setupList(3, width, taskBorder.y);
            BuildingsScripts.createItem("Central Unit", "qrc:/graphics/Buildings/CentralUnit.png",GameApi.base.buildings.centralUnit.currentLevel(), GameApi.base.buildings.centralUnit.description());
            BuildingsScripts.createItem("Docking Station", "qrc:/graphics/Buildings/DockingStation.png",GameApi.base.buildings.dockingStation.currentLevel(), GameApi.base.buildings.dockingStation.description());
            BuildingsScripts.createItem("Barracks", "qrc:/graphics/Buildings/Barracks.png");
        }
        else if (catName === "Industrial sector")
        {
            BuildingsScripts.setupList(5, width, taskBorder.y);
            BuildingsScripts.createItem("Powerplant", "qrc:/graphics/Buildings/Powerplant.png");
            BuildingsScripts.createItem("Factory", "qrc:/graphics/Buildings/Factory.png");
            BuildingsScripts.createItem("Aetherite Silo", "qrc:/graphics/Buildings/AetheriteSilo.png");
            BuildingsScripts.createItem("Cool Room", "qrc:/graphics/Buildings/CoolRoom.png");
            BuildingsScripts.createItem("Storage Room", "qrc:/graphics/Buildings/StorageRoom.png");
        }
        else if (catName === "Mercenaries care")
        {
            BuildingsScripts.setupList(5, width, taskBorder.y);
            BuildingsScripts.createItem("Hospital", "qrc:/graphics/Buildings/Hospital.png");
            BuildingsScripts.createItem("Bar", "qrc:/graphics/Buildings/Bar.png");
            BuildingsScripts.createItem("Playing Field", "qrc:/graphics/Buildings/PlayingField.png");
            BuildingsScripts.createItem("Seclusion", "qrc:/graphics/Buildings/Seclusion.png");
            BuildingsScripts.createItem("Shrine", "qrc:/graphics/Buildings/Shrine.png");
        }
        else
        {
            BuildingsScripts.setupList(3, width, taskBorder.y);
            BuildingsScripts.createItem("Gym", "qrc:/graphics/Buildings/Gym.png");
            BuildingsScripts.createItem("Laboratory", "qrc:/graphics/Buildings/Laboratory.png");
            BuildingsScripts.createItem("Training Ground", "qrc:/graphics/Buildings/TrainingGround.png");
        }
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

    signal selected(string name)
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
                if (root.category == "")
                {
                    var e=CategoriesScripts.getClickedItemName(mouseX,y0);
                    if (e != "")
                    {
                        root.category = e;
                        root.doFading();
                    }
                }
                else
                {
                    var e=BuildingsScripts.getClickedItemName(mouseX,y0);
                    if (e != "")
                        root.selected(e);
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
                    if (root.category == "")
                        CategoriesScripts.scrollList(Math.ceil(mouseArea.mouseY) - mouseArea.y0);
                    else
                        BuildingsScripts.scrollList(Math.ceil(mouseArea.mouseY) - mouseArea.y0);

                    mouseArea.y0 = Math.ceil(mouseArea.mouseY);
                }
                else
                {
                    if (Math.abs(mouseArea.mouseY - mouseArea.y0) >= Globals.windowHeight * mouseArea.yChangedThresholdForScrolling / 100)
                    {
                        mouseArea.isScrollingActive = true;
                        if (root.category == "")
                            CategoriesScripts.scrollList(mouseArea.mouseY - mouseArea.y0);
                        else
                            BuildingsScripts.scrollList(mouseArea.mouseY - mouseArea.y0);
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

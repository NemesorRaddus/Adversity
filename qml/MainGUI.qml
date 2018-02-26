import QtQuick 2.9
import FPSComponent 1.0

Rectangle {
    id: mainRoot

    property alias mainMenu: mainMenu
    property alias mainContent: mainContent

    property alias enableFPSCounter: fpsCnt.visible

    property alias gameOn: mainContent.visible // or !mainMenu.visible

    width: 1080
    height: 1920

    function updateMenu()
    {
        mainMenu.update();
    }

    function updateContent(minimal)
    {
        if (minimal)
            mainContent.updateClock();
        else
            mainContent.updateEverything();
    }

    function updateEverything()
    {
        if (gameOn)
            updateContent(0);
        else
            updateMenu();
    }

    function reactToExit()
    {
        return gameOn ? mainContent.reactToExit() : mainMenu.reactToExit();
    }

    onEnableFPSCounterChanged: mainContent.settings.acknowledgeFPSToggle(enableFPSCounter);

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    MainMenu {
        id: mainMenu

        x: 0
        y: 0
        width: parent.width
        height: parent.height
    }

    MainContent {
        id: mainContent

        x: 0
        y: 0
        width: parent.width
        height: parent.height

        visible: false
    }

    FPSCounter {
        id: fpsCnt

        visible: false

        x: 0
        anchors.bottom: parent.bottom
        width: 200
        height: 125

        Text {
            x: 0
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter

            font.family: "Comic Sans"
            font.pixelSize: parent.height
            color: "white"
            text: fpsCnt.fps
        }
    }
}

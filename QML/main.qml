import QtQuick 2.7
import QtQuick.Window 2.2

import Game 1.0
import "."

Window {
    id: win

    property int currentMode: 0

    function changeMode(mode)
    {
        if (mode == 0)
        {
            currentMode = 0;
            mainGUI.buildingsList.state = "hiddenRight"
        }
        else if (mode == 1)
        {
            currentMode = 1;
            mainGUI.buildingsList.state = "";
        }
        else if (mode == 2)
        {
            currentMode = 2;
            mainGUI.buildingsList.state = "hiddenLeft";
        }
    }

    visible: true
    width: 450
    height: 800
    title: "Game"

    onWidthChanged: Globals.windowWidth = width;
    onHeightChanged: Globals.windowHeight = height;

    MainGUI {
        id: mainGUI

        transform: [
            Scale {
                id: scale

                xScale: win.width/mainGUI.width
                yScale: win.height/mainGUI.height
            },
            Translate {
                x: (win.width-mainGUI.width*scale.xScale)/2
                y: (win.height-mainGUI.height*scale.yScale)/2
            }
        ]

        missionsButton.onClicked: changeMode(0);
        baseButton.onClicked: changeMode(1);
        heroesButton.onClicked: changeMode(2);
    }

    Component.onCompleted: {
        Globals.windowWidth = width;
        Globals.windowHeight = height;
        Globals.dpcm = Screen.pixelDensity*10;
        changeMode(0);
    }
}

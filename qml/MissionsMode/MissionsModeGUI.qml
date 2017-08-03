import QtQuick 2.0

Item {
    id: root

    clip: true

    signal updateRequestedFromBuildingsModeGUI()
    signal showSpecial()

    function returnToDefault()
    {
        map.returnToDefault();//TODO state changes,etc.
    }

    function updateEverything()
    {
        map.updateEverything();
    }

    function reactToBackOnToolbar()//returns true if intervention was successful and nothing else is needed to be done
    {
//        if (menu.state == "")
//        {
//            if (!menu.reactToBackOnToolbar())
//            {
//                list.state = "";
//                menu.state = "hidden";
//            }
//            return true;
//        }
//        else
//        {
            return false;
//        }
    }

    Map {
        id: map

        x: 0
        y: 0
        width: root.width
        height: root.height

        onExploreClicked: {
            //TODO
        }
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -width }
        },
        State {
            name: "hiddenLeft2"
            PropertyChanges { target: root; x: -2 * width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}

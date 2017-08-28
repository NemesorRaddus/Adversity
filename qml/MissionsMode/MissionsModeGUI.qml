import QtQuick 2.0

Item {
    id: root

    clip: true

    signal updateRequestedFromBuildingsModeGUI()
    signal showSpecial()

    function returnToDefault()
    {
        map.returnToDefault();
        missionStartMenu.returnToDefault();
        missionSelectionMenu.returnToDefault();

        missionSelectionMenu.state = "hiddenRight2";
        missionStartMenu.state = "hiddenRight";
        map.state = "";
    }

    function updateEverything()
    {
        map.updateEverything();
    }

    function reactToBackOnToolbar()//returns true if intervention was successful and nothing else is needed to be done
    {
        if (missionSelectionMenu.state == "")
        {
            if (!missionSelectionMenu.reactToBackOnToolbar())
            {
                missionSelectionMenu.state = "hiddenRight";
                missionSelectionMenu.returnToDefault();

                missionStartMenu.state = ""

                map.state = "hiddenLeft";
            }
            return true;
        }
        else if (missionStartMenu.state == "")
        {
            if (!missionStartMenu.reactToBackOnToolbar())
            {
                missionStartMenu.state = "hiddenRight";
                missionStartMenu.returnToDefault();

                missionSelectionMenu.state = "hiddenRight2";

                map.state = ""
            }
            return true;
        }
        else
            return false;
    }

    Map {
        id: map

        x: 0
        y: 0
        width: root.width
        height: root.height

        onExploreClicked: {
            missionStartMenu.show(intLandName, landName, landDesc);
            missionStartMenu.state = "";
            missionSelectionMenu.state = "hiddenRight";
            state = "hiddenLeft";
        }
    }

    MissionStartMenu {
        id: missionStartMenu

        x: 0
        y: 0
        width: root.width
        height: root.height

        state: "hiddenRight"

        onBackClicked: {
            state = "hiddenRight";
            missionSelectionMenu.state = "hiddenRight2";
            map.state = "";
        }

        onNextClicked: {
            missionSelectionMenu.state = "";
            state = "hiddenLeft";
            map.state = "hiddenLeft2";
        }
    }

    MissionSelectionMenu {
        id: missionSelectionMenu

        x: 0
        y: 0
        width: root.width
        height: root.height

        state: "hiddenRight2"

        onBackClicked: {
            state = "hiddenRight";
            missionStartMenu.state = "";
            map.state = "hiddenLeft";
        }

        onExploreClicked: {
            root.returnToDefault();
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

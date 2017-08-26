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

        missionSelectionMenu.visible = false;
        missionStartMenu.visible = false;
    }

    function updateEverything()
    {
        map.updateEverything();
    }

    function reactToBackOnToolbar()//returns true if intervention was successful and nothing else is needed to be done
    {
        if (missionSelectionMenu.visible)
        {
            if (!missionSelectionMenu.reactToBackOnToolbar())
                missionSelectionMenu.hide();
            return true;
        }
        else if (missionStartMenu.visible)
        {
            if (!missionStartMenu.reactToBackOnToolbar())
                missionStartMenu.hide();
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
            missionStartMenu.visible=true;
        }
    }

    MissionStartMenu {
        id: missionStartMenu

        x: 0
        y: 0
        width: root.width
        height: root.height

        visible: false

        function hide()
        {
            visible = false;
            returnToDefault();
        }

        onBackClicked: {
            visible = false;
        }

        onNextClicked: {
            missionSelectionMenu.visible=true;
        }
    }

    MissionSelectionMenu {
        id: missionSelectionMenu

        x: 0
        y: 0
        width: root.width
        height: root.height

        visible: false

        function hide()
        {
            visible = false;
            returnToDefault();
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

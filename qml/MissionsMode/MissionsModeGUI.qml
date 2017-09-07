import QtQuick 2.9

import "./Database"
import "./MissionsList"

Item {
    id: root

    clip: true

    signal updateRequestedFromBuildingsModeGUI()
    signal showSpecial()

    property bool ready: false

    function returnToDefault()
    {
        map.returnToDefault();
        missionStartMenu.returnToDefault();
        missionSelectionMenu.returnToDefault();

        if (ready)
        {
            database.returnToDefault();
            database.hide();
            databaseEntryView.state = "hiddenDown";
        }
        else
            ready=true;

        missionSelectionMenu.state = "hiddenRight2";
        missionStartMenu.state = "hiddenRight";
        map.state = "";
    }

    function updateEverything()
    {
        map.updateEverything();
        database.update();
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
        else if (databaseEntryView.state == "")
        {
            if (!databaseEntryView.reactToBackOnToolbar())
            {
                databaseEntryView.state = "hiddenDown";
                database.state = "";
            }
            return true;
        }
        else if (database.state == "")
        {
            if (!database.reactToBackOnToolbar())
                database.hide();
            return true;
        }
        else
            return false;
    }

    onStateChanged: {
        map.acknowledgeModeStateChange(state);
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

        onDatabaseClicked: {
            database.show();
        }

        onMissionsClicked: {
            missionsList.show();
        }
    }

    Database {
        id: database

        x: 0
        y: 0
        width: root.width
        height: root.height

        onSelected: {
            databaseEntryView.setItem(name, type);
            state = "hiddenUp";
            databaseEntryView.state = "";
        }

        onBackClicked: {
            if (category == "")
                hide();
            else
            {
                category = "";
                doFading();
            }
        }
    }
    DatabaseEntryView {
        id: databaseEntryView

        x: 0
        y: 0
        width: root.width
        height: root.height

        onBackClicked: {
            state = "hiddenDown";
            database.state = "";
        }
    }

    MissionsList {
        id: missionsList

        x: 0
        y: 0
        width: root.width
        height: root.height

        onSelected: {
            missionView.setItem(name);
            state = "hiddenUp";
            missionView.state = "";
        }

        onBackClicked: {
            hide();
        }
    }
    MissionView {
        id: missionView

        x: 0
        y: 0
        width: root.width
        height: root.height

        onBackClicked: {
            state = "hiddenDown";
            missionsList.state = "";
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

    MissionView {
        anchors.fill: parent
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

import QtQuick 2.0

Item {
    id: root

    clip: true

    function returnToDefault()
    {
        list.state = "";
        menu.state = "hidden";
        list.returnToDefault();
    }

    function updateEverything()
    {
        list.updateEverything();
        menu.updateEverything();
    }

    BuildingsList {
        id: list

        x: 0
        y: 0
        width: root.width
        height: root.height

        onBuildingClicked: {
            if (buildingName == "centralUnit")
                menu.changeToCentralUnit();
            //TODO
            state = "hidden";
            menu.state = "";
        }
    }

    BuildingMenu {
        id: menu

        x: 0
        y: 0
        width: root.width
        height: root.height

        onBackClicked: {
            list.state = "";
            state = "hidden";
        }

        Component.onCompleted: state = "hidden";
    }

    states: [
        State {
            name: "hiddenLeft"
            PropertyChanges { target: root; x: -1 * width }
        },
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}

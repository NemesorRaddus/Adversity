import QtQuick 2.9

import "./Reports"

Item {
    id: root

    width: 1080
    height: 1440

    property string name_

    signal backClicked()
    signal heroesModeUpdateRequested()
    signal missionsListUpdateRequested()

    function returnToDefault()
    {
        reportsList.returnToDefault();

        reportsList.state = "hiddenLeft";
        missionView.state = "";
        heroView.state = "hiddenRight";
        missionManagement.hide();
    }

    function reactToBackOnToolbar()
    {
        if (missionManagement.state == "")
        {
            if (!missionManagement.reactToBackOnToolbar())
                missionManagement.hide();
            return true;
        }
        if (reportsList.state == "" || heroView.state == "")
        {
            returnToDefault();
            return true;
        }
        return false;
    }

    function updateEverything()
    {
        reportsList.updateEverything();
        missionView.update();
        heroView.updateEverything();
        missionManagement.updateEverything();
    }

    function setHero(heroName)
    {
        returnToDefault();

        reportsList.setHero(heroName);
        missionView.setHero(heroName);
        heroView.setHero(heroName);
        missionManagement.setHero(heroName);
    }

    Rectangle {
        anchors.fill: parent

        color: "#171717"
    }

    Item {
        id: content

        x: 0
        y: 0
        width: parent.width
        height: taskBorder.y

        ReportsList {
            id: reportsList

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            state: "hiddenLeft"
        }

        MissionView {
            id: missionView

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            state: ""

            onReportsClicked: {
                reportsList.updateEverything();

                state = "hiddenRight";
                reportsList.state = "";
                heroView.state = "hiddenRight2";
            }
            onMercenaryClicked: {
                heroView.updateEverything();

                state = "hiddenLeft";
                reportsList.state = "hiddenLeft2";
                heroView.state = "";
            }
            onMissionManagementClicked: {
                missionManagement.updateEverything();

                missionManagement.show();
            }
        }

        HeroView {
            id: heroView

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            state: "hiddenRight"
        }

        MissionManagement {
            id: missionManagement

            x: 0
            y: 0
            width: parent.width
            height: parent.height

            state: "hidden"

            onAbortClicked: {
                hide();
                root.returnToDefault();
                root.backClicked();
                root.heroesModeUpdateRequested();
                root.missionsListUpdateRequested();
            }
        }
    }

    Image {
        id: taskBorder

        x: 17
        y: 1386
        width: 1046
        height: 3

        source: "qrc:/graphics/GUI/Task_Border.png"
    }

    Item {
        id: back

        x: 17
        y: 1396
        width: 1048
        height: 68

        Text {
            id: backText

            anchors.fill: parent
            color: "#94ef94"
            text: "Back"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 60
            font.family: fontStencil.name
        }
        MouseArea {
            id: backButton

            anchors.rightMargin: 421
            anchors.leftMargin: 418

            anchors.fill: parent

            onClicked: {
                if (!reactToBackOnToolbar())
                    backClicked();
            }
        }
    }

    states: [
        State {
            name: "hiddenDown"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: [
        Transition {
            NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 300 }
        }
    ]

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

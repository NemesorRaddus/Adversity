import QtQuick 2.9

import "./Reports"

Item {
    id: root

    width: 1080
    height: 1440

    property string name_

    signal backClicked()
    signal mercenariesModeUpdateRequested()
    signal missionsListUpdateRequested()

    function returnToDefault()
    {
        reportsList.returnToDefault();

        reportsList.state = "hiddenLeft";
        missionView.state = "";
        mercenaryView.state = "hiddenRight";
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
        if (reportsList.state == "" || mercenaryView.state == "")
        {
            returnToDefault();
            return true;
        }
        return false;
    }

    function updateEverything()
    {
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

        reportsList.updateEverything();
        missionView.update();
        mercenaryView.updateEverything();
        missionManagement.updateEverything();
    }

    function setMercenary(mercenaryName)
    {
        returnToDefault();

        reportsList.setMercenary(mercenaryName);
        missionView.setMercenary(mercenaryName);
        mercenaryView.setMercenary(mercenaryName);
        missionManagement.setMercenary(mercenaryName);
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
                mercenaryView.state = "hiddenRight2";
            }
            onMercenaryClicked: {
                mercenaryView.updateEverything();

                state = "hiddenLeft";
                reportsList.state = "hiddenLeft2";
                mercenaryView.state = "";
            }
            onMissionManagementClicked: {
                missionManagement.updateEverything();

                missionManagement.show();
            }
        }

        MercenaryView {
            id: mercenaryView

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
                root.mercenariesModeUpdateRequested();
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

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "y"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 300 }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

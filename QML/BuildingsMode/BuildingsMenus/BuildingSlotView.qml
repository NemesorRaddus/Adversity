import QtQuick 2.5

Item {
    id: root

    property int theoreticalWidth: 180
    property int theoreticalHeight: 437

    property bool isVacant: true
    property bool isConfirmed: false

    property int mode: 0//0-stress, 1-training, 2-hospital

    width: theoreticalWidth
    height: theoreticalHeight

    function setHeroOneVal(pathToArt, val1)
    {
        artImage.source = pathToArt;
        artImage.visible = true;

        cost1Amount.text = val1;
        cost1.visible = true;

        cost2.visible = false;

        startAbortIcon.visible = true;

        startAbortMA.enabled = true;

        isVacant = false;
    }

    function setHeroTwoVals(pathToArt, val1, val2)
    {
        artImage.source = pathToArt;
        artImage.visible = true;

        cost1Amount.text = val1;
        cost1.visible = true;

        cost2Amount.text = val2;
        cost2.visible = true;

        startAbortIcon.visible = true;

        startAbortMA.enabled = true;

        isVacant = false;
    }

    function removeHero()
    {
        artImage.visible = false;
        artMA.enabled = true;
        cost1.visible = false;
        cost2.visible = false;
        startAbortIcon.visible = false;
        startAbortMA.enabled = false;
        isVacant = true;
    }

    signal artClicked()
    signal startClicked()
    signal abortClicked()
    signal requestUnban()

    onModeChanged: {
        if (mode == 0)
        {
            cost2.visible = false;

            cost1Icon.source = "qrc:/graphics/GUI/Energy.png"
        }
        else if (mode == 1)
        {
            if (cost1.visible)
                cost2.visible = true;

            cost1Icon.source = "qrc:/graphics/GUI/Energy.png"
            cost2Icon.source = "qrc:/graphics/GUI/Time.png"
        }
        else if (mode == 2)
        {
            if (cost1.visible)
                cost2.visible = true;

            cost1Icon.source = "qrc:/graphics/GUI/Energy.png"
            cost2Icon.source = "qrc:/graphics/GUI/Foodsupplies.png"
        }
    }

    Item {
        id: art

        x: 25
        y: 10
        width: 130
        height: 130

        Image {
            id: artImage

            x: 1;
            y: 1;
            width: 128;
            height: 128;

            visible: false
        }

        Image {
            id: artBorder

            anchors.fill: parent

            source: "qrc:/graphics/GUI/Task_Picture2.png"
        }

        MouseArea {
            id: artMA

            anchors.fill: parent

            onClicked: {
                if (isVacant)
                    artClicked();
                else if (!isConfirmed)
                {
                    requestUnban();
                    artClicked();
                }
            }
        }
    }

    Item {
        id: costs

        x: 0
        y: art.y + art.height + 8
        width: parent.width
        height: cost2.y + cost2.height

        Item {
            id: cost1

            x: 0
            y: 0
            width: parent.width
            height: 70

            visible: false

            Image {
                id: cost1Icon

                x: 8
                y: 0
                width: 70
                height: 70

                source: "qrc:/graphics/GUI/Energy.png";
            }
            Text {
                id: cost1Amount

                x: cost1Icon.x + cost1Icon.width + 4
                y: 0
                width: parent.width - x
                height: parent.height

                color: "#94ef94"
                font.pixelSize: 60
                font.family: fontStencil.name

                horizontalAlignment: Text.AlignHCenter
            }
        }

        Item {
            id: cost2

            x: 0
            y: cost1.y + cost1.height + 4
            width: parent.width
            height: 70

            visible: false

            Image {
                id: cost2Icon

                x: 8
                y: 0
                width: 70
                height: 70

                source: "qrc:/graphics/GUI/Energy.png";
            }
            Text {
                id: cost2Amount

                x: cost2Icon.x + cost2Icon.width + 4
                y: 0
                width: parent.width - x
                height: parent.height

                color: "#94ef94"
                font.pixelSize: 60
                font.family: fontStencil.name

                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Item {
        id: startAbort

        x: 23
        y: costs.y + costs.height + 4
        width: 134
        height: 134

        Image {
            id: startAbortIcon

            anchors.fill: parent

            visible: false

            source: "qrc:/graphics/GUI/Settings.png"
        }

        MouseArea {
            id: startAbortMA

            anchors.fill: parent

            enabled: false

            onClicked: {
                if (isConfirmed)
                {
                    startAbortIcon.source = "qrc:/graphics/GUI/Settings.png"
                    isConfirmed = false;
                    removeHero();
                    abortClicked();
                }
                else
                {
                    isConfirmed = true;
                    startAbortIcon.source = "qrc:/graphics/GUI/Abort.png";
                    startClicked();
                }
            }
        }
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

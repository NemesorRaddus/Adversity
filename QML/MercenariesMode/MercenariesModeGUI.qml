import QtQuick 2.0

import Game 1.0

Item {
    id: root

    property int theoreticalWidth: 1080
    property int theoreticalHeight: 1464

    width: 1080
    height: 1464

    clip: false

    transform: [
        Scale {
            id: someScale

            xScale: width/theoreticalWidth
            yScale: height/theoreticalHeight
        },
        Translate {
            x: (width-theoreticalWidth*someScale.xScale)/2
            y: (height-theoreticalHeight*someScale.yScale)/2
        }
    ]

    signal updateRequestedFromMercenariesModeGUI()
    signal buildingMenuRequested(string buildingName)
    signal dismissClickedFwd()
    signal dismissDialogHidingRequested()
    signal artPreviewRequested(string artSource)
    signal artPreviewHidingRequested()

    function returnToDefault()
    {
        list.state = "";
        heroesAmountItem.state = "";
        view.state = "hidden";
        list.returnToDefault();
        view.returnToDefault();
    }

    function updateEverything()
    {
        list.returnToDefault();
        list.updateEverything();
        view.updateEverything();
        heroesAmountItem.update();
    }

    function reactToBackOnToolbar()//returns true if intervention was successful and nothing else is needed to be done
    {
        if (view.state == "")
        {
            if (view.dismissConfirmDialogVisible)
            {
                dismissDialogHidingRequested();
                view.dismissConfirmDialogVisible=false;
                return true;
            }
            if (view.artPreviewVisible)
            {
                artPreviewHidingRequested();
                view.artPreviewVisible=false;
                return true;
            }

            if (!view.reactToBackOnToolbar())
            {
                list.state = "";
                view.state = "hidden";
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    function dismissMercenaryFwd()
    {
        view.dismissMercenary();
    }

    function acknowledgeConfirmDialogClosing()
    {
        view.dismissConfirmDialogVisible = false;
    }

    function acknowledgeArtPreviewClosing()
    {
        view.artPreviewVisible = false;
    }

    Item {
        id: heroesAmountItem

        x: 0
        y: 12
        width: parent.theoreticalWidth
        height: heroesAmountTaskBorder.y + heroesAmountTaskBorder.height - 4

        function update()
        {
            heroesAmountAmount.text = GameApi.base.heroes.amountOfHeroes() + '/' + GameApi.base.heroes.amountOfSlots();
        }

        Text {
            id: heroesAmountText

            x: 240
            y: -6

            text: "Mercenaries:"
            color: "#94ef94"
            font.pixelSize: 70
            font.family: fontStencil.name
        }
        Text {
            id: heroesAmountAmount

            x: 740
            y: heroesAmountText.y

            color: "#94ef94"
            font.pixelSize: 70
            font.family: fontStencil.name
        }

        Image {
            id: heroesAmountTaskBorder

            x: 17
            y: 68
            width: 1048
            height: 3

            source: "qrc:/graphics/GUI/Task_Border.png"
        }

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: heroesAmountItem; y: -height-10 }
            }
        ]

        transitions: Transition {
            NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 500 }
        }
    }

    HeroesList {
        id: list

        x: 0
        y: heroesAmountItem.y+heroesAmountItem.height
        width: root.theoreticalWidth
        height: root.theoreticalHeight - heroesAmountItem.height

        onHeroClicked: {
            view.setMercenary(GameApi.globalsCpp.alterNormalTextToInternal(heroName));

            state = "hidden";
            heroesAmountItem.state = "hidden";
            view.state = "";
        }
    }

    HeroView {
        id: view

        x: 0
        y: 0
        width: root.width
        height: root.height

        onBackClicked: {
            state = "hidden";
            list.state = "";
            heroesAmountItem.state = "";
        }

        onBuildingMenuRequested: root.buildingMenuRequested(buildingName);

        onDismissClicked: root.dismissClickedFwd();

        onGuiUpdateRequested: {
            root.returnToDefault();
            root.updateEverything();
            updateRequestedFromMercenariesModeGUI();
        }

        onArtPreviewRequested: root.artPreviewRequested(artSource);

        Component.onCompleted: state = "hidden";
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }

    states: [
        State {
            name: "hiddenRight"
            PropertyChanges { target: root; x: width }
        },
        State {
            name: "hiddenRight2"
            PropertyChanges { target: root; x: width * 2 }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InQuad; duration: 250 }
    }
}

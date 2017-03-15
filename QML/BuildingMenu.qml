import QtQuick 2.0

import Game 1.0

Item {
    id: root

    signal backClicked()

    function changeToCentralUnit()
    {
        centralUnit.visible = true;
    }

    function changeToHospital()
    {
        centralUnit.visible = false;
    }

    function changeToTrainingGround()
    {
        centralUnit.visible = false;
    }

    function changeToGym()
    {
        centralUnit.visible = false;
    }

    function changeToLaboratory()
    {
        centralUnit.visible = false;
    }

    function changeToPlayingField()
    {
        centralUnit.visible = false;
    }

    function changeToBar()
    {
        centralUnit.visible = false;
    }

    function changeToShrine()
    {
        centralUnit.visible = false;
    }

    function changeToSeclusion()
    {
        centralUnit.visible = false;
    }

    function changeToPowerplant()
    {
        centralUnit.visible = false;
    }

    function changeToFactory()
    {
        centralUnit.visible = false;
    }

    function changeToCoolRoom()
    {
        centralUnit.visible = false;
    }

    function changeToStorageRoom()
    {
        centralUnit.visible = false;
    }

    function changeToAetheriteSilo()
    {
        centralUnit.visible = false;
    }

    function changeToBarracks()
    {
        centralUnit.visible = false;
    }

    function changeToDockingStation()
    {
        centralUnit.visible = false;
    }

    function updateEverything()
    {
        centralUnit.setDescription(GameApi.base.centralUnit.description());
        centralUnit.setLevel(GameApi.base.centralUnit.currentLevel());
        centralUnit.setEnergyCons(GameApi.base.centralUnit.basicCostInEnergy());
        centralUnit.setUpgEnergyCons(GameApi.base.centralUnit.basicCostInEnergyAfterUpgrade());
        centralUnit.setUpgEnergyCost(GameApi.base.centralUnit.requirementsForNextLevelEnergy());
        centralUnit.setUpgBMCost(GameApi.base.centralUnit.requirementsForNextLevelBM());
        centralUnit.setUpgTime(GameApi.base.centralUnit.requirementsForNextLevelTime());
        //TODO more
    }

    CentralUnitMenu {
        id: centralUnit

        anchors.fill: parent

        onBackClickedd: backClicked()
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "y"; easing.type: Easing.InQuad; duration: 500 }
    }

    Component.onCompleted: {
        changeToCentralUnit();
    }
}

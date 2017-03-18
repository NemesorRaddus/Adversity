import QtQuick 2.0

import Game 1.0

import "./BuildingsMenus"

Item {
    id: root

    signal backClickedFwd()
    signal upgradeRequestedFwd(string buildingName)//upper camel case, but with spaces (e.g. Central Unit)

    function changeToCentralUnit()
    {
        centralUnit.visible = true;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToHospital()
    {
        centralUnit.visible = false;
        hospital.visible = true;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToTrainingGround()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = true;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToGym()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = true;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToLaboratory()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = true;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToPlayingField()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = true;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToBar()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = true;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToShrine()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = true;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToSeclusion()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = true;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToPowerplant()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = true;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToFactory()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = true;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToCoolRoom()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = true;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToStorageRoom()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = true;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToAetheriteSilo()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = true;
        barracks.visible = false;
        dockingStation.visible = false;
    }

    function changeToBarracks()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = true;
        dockingStation.visible = false;
    }

    function changeToDockingStation()
    {
        centralUnit.visible = false;
        hospital.visible = false;
        trainingGround.visible = false;
        gym.visible = false;
        laboratory.visible = false;
        playingField.visible = false;
        bar.visible = false;
        shrine.visible = false;
        seclusion.visible = false;
        powerplant.visible = false;
        factory.visible = false;
        coolRoom.visible = false;
        storageRoom.visible = false;
        aetheriteSilo.visible = false;
        barracks.visible = false;
        dockingStation.visible = true;
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

        hospital.setDescription(GameApi.base.hospital.description());
        hospital.setLevel(GameApi.base.hospital.currentLevel());
        hospital.setEnergyCons(GameApi.base.hospital.basicCostInEnergy());
        hospital.setUpgEnergyCons(GameApi.base.hospital.basicCostInEnergyAfterUpgrade());
        hospital.setUpgEnergyCost(GameApi.base.hospital.requirementsForNextLevelEnergy());
        hospital.setUpgBMCost(GameApi.base.hospital.requirementsForNextLevelBM());
        hospital.setUpgTime(GameApi.base.hospital.requirementsForNextLevelTime());

        trainingGround.setDescription(GameApi.base.trainingGround.description());
        trainingGround.setLevel(GameApi.base.trainingGround.currentLevel());
        trainingGround.setEnergyCons(GameApi.base.trainingGround.basicCostInEnergy());
        trainingGround.setUpgEnergyCons(GameApi.base.trainingGround.basicCostInEnergyAfterUpgrade());
        trainingGround.setUpgEnergyCost(GameApi.base.trainingGround.requirementsForNextLevelEnergy());
        trainingGround.setUpgBMCost(GameApi.base.trainingGround.requirementsForNextLevelBM());
        trainingGround.setUpgTime(GameApi.base.trainingGround.requirementsForNextLevelTime());

        gym.setDescription(GameApi.base.gym.description());
        gym.setLevel(GameApi.base.gym.currentLevel());
        gym.setEnergyCons(GameApi.base.gym.basicCostInEnergy());
        gym.setUpgEnergyCons(GameApi.base.gym.basicCostInEnergyAfterUpgrade());
        gym.setUpgEnergyCost(GameApi.base.gym.requirementsForNextLevelEnergy());
        gym.setUpgBMCost(GameApi.base.gym.requirementsForNextLevelBM());
        gym.setUpgTime(GameApi.base.gym.requirementsForNextLevelTime());

        laboratory.setDescription(GameApi.base.laboratory.description());
        laboratory.setLevel(GameApi.base.laboratory.currentLevel());
        laboratory.setEnergyCons(GameApi.base.laboratory.basicCostInEnergy());
        laboratory.setUpgEnergyCons(GameApi.base.laboratory.basicCostInEnergyAfterUpgrade());
        laboratory.setUpgEnergyCost(GameApi.base.laboratory.requirementsForNextLevelEnergy());
        laboratory.setUpgBMCost(GameApi.base.laboratory.requirementsForNextLevelBM());
        laboratory.setUpgTime(GameApi.base.laboratory.requirementsForNextLevelTime());

        playingField.setDescription(GameApi.base.playingField.description());
        playingField.setLevel(GameApi.base.playingField.currentLevel());
        playingField.setEnergyCons(GameApi.base.playingField.basicCostInEnergy());
        playingField.setUpgEnergyCons(GameApi.base.playingField.basicCostInEnergyAfterUpgrade());
        playingField.setUpgEnergyCost(GameApi.base.playingField.requirementsForNextLevelEnergy());
        playingField.setUpgBMCost(GameApi.base.playingField.requirementsForNextLevelBM());
        playingField.setUpgTime(GameApi.base.playingField.requirementsForNextLevelTime());

        bar.setDescription(GameApi.base.bar.description());
        bar.setLevel(GameApi.base.bar.currentLevel());
        bar.setEnergyCons(GameApi.base.bar.basicCostInEnergy());
        bar.setUpgEnergyCons(GameApi.base.bar.basicCostInEnergyAfterUpgrade());
        bar.setUpgEnergyCost(GameApi.base.bar.requirementsForNextLevelEnergy());
        bar.setUpgBMCost(GameApi.base.bar.requirementsForNextLevelBM());
        bar.setUpgTime(GameApi.base.bar.requirementsForNextLevelTime());

        shrine.setDescription(GameApi.base.shrine.description());
        shrine.setLevel(GameApi.base.shrine.currentLevel());
        shrine.setEnergyCons(GameApi.base.shrine.basicCostInEnergy());
        shrine.setUpgEnergyCons(GameApi.base.shrine.basicCostInEnergyAfterUpgrade());
        shrine.setUpgEnergyCost(GameApi.base.shrine.requirementsForNextLevelEnergy());
        shrine.setUpgBMCost(GameApi.base.shrine.requirementsForNextLevelBM());
        shrine.setUpgTime(GameApi.base.shrine.requirementsForNextLevelTime());

        seclusion.setDescription(GameApi.base.seclusion.description());
        seclusion.setLevel(GameApi.base.seclusion.currentLevel());
        seclusion.setEnergyCons(GameApi.base.seclusion.basicCostInEnergy());
        seclusion.setUpgEnergyCons(GameApi.base.seclusion.basicCostInEnergyAfterUpgrade());
        seclusion.setUpgEnergyCost(GameApi.base.seclusion.requirementsForNextLevelEnergy());
        seclusion.setUpgBMCost(GameApi.base.seclusion.requirementsForNextLevelBM());
        seclusion.setUpgTime(GameApi.base.seclusion.requirementsForNextLevelTime());

        powerplant.setDescription(GameApi.base.powerplant.description());
        powerplant.setLevel(GameApi.base.powerplant.currentLevel());
        powerplant.setEnergyCons(GameApi.base.powerplant.basicCostInEnergy());
        powerplant.setUpgEnergyCons(GameApi.base.powerplant.basicCostInEnergyAfterUpgrade());
        powerplant.setUpgEnergyCost(GameApi.base.powerplant.requirementsForNextLevelEnergy());
        powerplant.setUpgBMCost(GameApi.base.powerplant.requirementsForNextLevelBM());
        powerplant.setUpgTime(GameApi.base.powerplant.requirementsForNextLevelTime());

        factory.setDescription(GameApi.base.factory.description());
        factory.setLevel(GameApi.base.factory.currentLevel());
        factory.setEnergyCons(GameApi.base.factory.basicCostInEnergy());
        factory.setUpgEnergyCons(GameApi.base.factory.basicCostInEnergyAfterUpgrade());
        factory.setUpgEnergyCost(GameApi.base.factory.requirementsForNextLevelEnergy());
        factory.setUpgBMCost(GameApi.base.factory.requirementsForNextLevelBM());
        factory.setUpgTime(GameApi.base.factory.requirementsForNextLevelTime());

        coolRoom.setDescription(GameApi.base.coolRoom.description());
        coolRoom.setLevel(GameApi.base.coolRoom.currentLevel());
        coolRoom.setEnergyCons(GameApi.base.coolRoom.basicCostInEnergy());
        coolRoom.setUpgEnergyCons(GameApi.base.coolRoom.basicCostInEnergyAfterUpgrade());
        coolRoom.setUpgEnergyCost(GameApi.base.coolRoom.requirementsForNextLevelEnergy());
        coolRoom.setUpgBMCost(GameApi.base.coolRoom.requirementsForNextLevelBM());
        coolRoom.setUpgTime(GameApi.base.coolRoom.requirementsForNextLevelTime());

        storageRoom.setDescription(GameApi.base.storageRoom.description());
        storageRoom.setLevel(GameApi.base.storageRoom.currentLevel());
        storageRoom.setEnergyCons(GameApi.base.storageRoom.basicCostInEnergy());
        storageRoom.setUpgEnergyCons(GameApi.base.storageRoom.basicCostInEnergyAfterUpgrade());
        storageRoom.setUpgEnergyCost(GameApi.base.storageRoom.requirementsForNextLevelEnergy());
        storageRoom.setUpgBMCost(GameApi.base.storageRoom.requirementsForNextLevelBM());
        storageRoom.setUpgTime(GameApi.base.storageRoom.requirementsForNextLevelTime());

        aetheriteSilo.setDescription(GameApi.base.aetheriteSilo.description());
        aetheriteSilo.setLevel(GameApi.base.aetheriteSilo.currentLevel());
        aetheriteSilo.setEnergyCons(GameApi.base.aetheriteSilo.basicCostInEnergy());
        aetheriteSilo.setUpgEnergyCons(GameApi.base.aetheriteSilo.basicCostInEnergyAfterUpgrade());
        aetheriteSilo.setUpgEnergyCost(GameApi.base.aetheriteSilo.requirementsForNextLevelEnergy());
        aetheriteSilo.setUpgBMCost(GameApi.base.aetheriteSilo.requirementsForNextLevelBM());
        aetheriteSilo.setUpgTime(GameApi.base.aetheriteSilo.requirementsForNextLevelTime());

        barracks.setDescription(GameApi.base.barracks.description());
        barracks.setLevel(GameApi.base.barracks.currentLevel());
        barracks.setEnergyCons(GameApi.base.barracks.basicCostInEnergy());
        barracks.setUpgEnergyCons(GameApi.base.barracks.basicCostInEnergyAfterUpgrade());
        barracks.setUpgEnergyCost(GameApi.base.barracks.requirementsForNextLevelEnergy());
        barracks.setUpgBMCost(GameApi.base.barracks.requirementsForNextLevelBM());
        barracks.setUpgTime(GameApi.base.barracks.requirementsForNextLevelTime());

        dockingStation.setDescription(GameApi.base.dockingStation.description());
        dockingStation.setLevel(GameApi.base.dockingStation.currentLevel());
        dockingStation.setEnergyCons(GameApi.base.dockingStation.basicCostInEnergy());
        dockingStation.setUpgEnergyCons(GameApi.base.dockingStation.basicCostInEnergyAfterUpgrade());
        dockingStation.setUpgEnergyCost(GameApi.base.dockingStation.requirementsForNextLevelEnergy());
        dockingStation.setUpgBMCost(GameApi.base.dockingStation.requirementsForNextLevelBM());
        dockingStation.setUpgTime(GameApi.base.dockingStation.requirementsForNextLevelTime());
    }

    CentralUnitMenu {
        id: centralUnit

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Central Unit")
    }
    HospitalMenu {
        id: hospital

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Hospital")
    }
    TrainingGroundMenu {
        id: trainingGround

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Training Ground")
    }
    GymMenu {
        id: gym

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Gym")
    }
    LaboratoryMenu {
        id: laboratory

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Laboratory")
    }
    PlayingFieldMenu {
        id: playingField

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Playing Field")
    }
    BarMenu {
        id: bar

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Bar")
    }
    ShrineMenu {
        id: shrine

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Shrine")
    }
    SeclusionMenu {
        id: seclusion

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Seclusion")
    }
    PowerplantMenu {
        id: powerplant

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Powerplant")
    }
    FactoryMenu {
        id: factory

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Factory")
    }
    CoolRoomMenu {
        id: coolRoom

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Cool Room")
    }
    StorageRoomMenu {
        id: storageRoom

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Storage Room")
    }
    AetheriteSiloMenu {
        id: aetheriteSilo

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Aetherite Silo")
    }
    BarracksMenu {
        id: barracks

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Barracks")
    }
    DockingStationMenu {
        id: dockingStation

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: upgradeRequestedFwd("Docking Station")
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

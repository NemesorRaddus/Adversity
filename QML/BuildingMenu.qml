import QtQuick 2.0

import Game 1.0

import "./BuildingsMenus"

Item {
    id: root

    signal backClickedFwd()
    signal updateRequestedFromBuildingMenu()
    signal markAsUpgradedSignal(var buildingName)

    function requestUpgrade(buildingName)//upper camel case, but with spaces (e.g. Central Unit)
    {
        if (buildingName === "Central Unit")
        {
            if (GameApi.base.centralUnit.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Central Unit");
            }
            else
            {

            }
        }
        else if (buildingName === "Hospital")
        {
            if (GameApi.base.hospital.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Hospital");
            }
            else
            {

            }
        }
        else if (buildingName === "Training Ground")
        {
            if (GameApi.base.trainingGround.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Training Ground");
            }
            else
            {

            }
        }
        else if (buildingName === "Gym")
        {
            if (GameApi.base.gym.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Gym");
            }
            else
            {

            }
        }
        else if (buildingName === "Laboratory")
        {
            if (GameApi.base.laboratory.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Laboratory");
            }
            else
            {

            }
        }
        else if (buildingName === "Playing Field")
        {
            if (GameApi.base.playingField.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Playing Field");
            }
            else
            {

            }
        }
        else if (buildingName === "Bar")
        {
            if (GameApi.base.bar.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Bar");
            }
            else
            {

            }
        }
        else if (buildingName === "Shrine")
        {
            if (GameApi.base.shrine.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Shrine");
            }
            else
            {

            }
        }
        else if (buildingName === "Seclusion")
        {
            if (GameApi.base.seclusion.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Seclusion");
            }
            else
            {

            }
        }
        else if (buildingName === "Powerplant")
        {
            if (GameApi.base.powerplant.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Powerplant");
            }
            else
            {

            }
        }
        else if (buildingName === "Factory")
        {
            if (GameApi.base.factory.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Factory");
            }
            else
            {

            }
        }
        else if (buildingName === "Cool Room")
        {
            if (GameApi.base.coolRoom.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Cool Room");
            }
            else
            {

            }
        }
        else if (buildingName === "Storage Room")
        {
            if (GameApi.base.storageRoom.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Storage Room");
            }
            else
            {

            }
        }
        else if (buildingName === "Aetherite Silo")
        {
            if (GameApi.base.aetheriteSilo.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Aetherite Silo");
            }
            else
            {

            }
        }
        else if (buildingName === "Barracks")
        {
            if (GameApi.base.barracks.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Barracks");
            }
            else
            {

            }
        }
        else if (buildingName === "Docking Station")
        {
            if (GameApi.base.dockingStation.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Docking Station");
            }
            else
            {

            }
        }
    }

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
        centralUnit.updateEverything();
        hospital.updateEverything();
        trainingGround.updateEverything();
        gym.updateEverything();
        laboratory.updateEverything();
        playingField.updateEverything();
        bar.updateEverything();
        shrine.updateEverything();
        seclusion.updateEverything();
        powerplant.updateEverything();
        factory.updateEverything();
        coolRoom.updateEverything();
        storageRoom.updateEverything();
        aetheriteSilo.updateEverything();
        barracks.updateEverything();
        dockingStation.updateEverything();
    }

    CentralUnitMenu {
        id: centralUnit

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Central Unit")
    }
    HospitalMenu {
        id: hospital

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Hospital")
    }
    TrainingGroundMenu {
        id: trainingGround

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Training Ground")
    }
    GymMenu {
        id: gym

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Gym")
    }
    LaboratoryMenu {
        id: laboratory

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Laboratory")
    }
    PlayingFieldMenu {
        id: playingField

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Playing Field")
    }
    BarMenu {
        id: bar

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Bar")
    }
    ShrineMenu {
        id: shrine

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Shrine")
    }
    SeclusionMenu {
        id: seclusion

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Seclusion")
    }
    PowerplantMenu {
        id: powerplant

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Powerplant")
    }
    FactoryMenu {
        id: factory

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Factory")
    }
    CoolRoomMenu {
        id: coolRoom

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Cool Room")
    }
    StorageRoomMenu {
        id: storageRoom

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Storage Room")
    }
    AetheriteSiloMenu {
        id: aetheriteSilo

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Aetherite Silo")
    }
    BarracksMenu {
        id: barracks

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Barracks")
    }
    DockingStationMenu {
        id: dockingStation

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Docking Station")
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

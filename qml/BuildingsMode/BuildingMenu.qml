import QtQuick 2.9

import Game 1.0

import "./BuildingsMenus"

Item {
    id: root

    signal backClickedFwd()
    signal updateRequestedFromBuildingMenu()
    signal mercenariesModeUpdateRequested()
    signal markAsUpgradedSignal(var buildingName)
    signal showSpecial()

    function requestUpgrade(buildingName)//upper camel case, but with spaces (e.g. Central Unit)
    {
        if (buildingName === "Central Unit")
        {
            if (GameApi.base.buildings.centralUnit.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Central Unit");
            }
        }
        else if (buildingName === "Hospital")
        {
            if (GameApi.base.buildings.hospital.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Hospital");
            }
        }
        else if (buildingName === "Training Ground")
        {
            if (GameApi.base.buildings.trainingGround.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Training Ground");
            }
        }
        else if (buildingName === "Gym")
        {
            if (GameApi.base.buildings.gym.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Gym");
            }
        }
        else if (buildingName === "Laboratory")
        {
            if (GameApi.base.buildings.laboratory.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Laboratory");
            }
        }
        else if (buildingName === "Playing Field")
        {
            if (GameApi.base.buildings.playingField.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Playing Field");
            }
        }
        else if (buildingName === "Bar")
        {
            if (GameApi.base.buildings.bar.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Bar");
            }
        }
        else if (buildingName === "Shrine")
        {
            if (GameApi.base.buildings.shrine.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Shrine");
            }
        }
        else if (buildingName === "Seclusion")
        {
            if (GameApi.base.buildings.seclusion.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Seclusion");
            }
        }
        else if (buildingName === "Powerplant")
        {
            if (GameApi.base.buildings.powerplant.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Powerplant");
            }
        }
        else if (buildingName === "Factory")
        {
            if (GameApi.base.buildings.factory.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Factory");
            }
        }
        else if (buildingName === "Cool Room")
        {
            if (GameApi.base.buildings.coolRoom.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Cool Room");
            }
        }
        else if (buildingName === "Storage Room")
        {
            if (GameApi.base.buildings.storageRoom.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Storage Room");
            }
        }
        else if (buildingName === "Aetherite Silo")
        {
            if (GameApi.base.buildings.aetheriteSilo.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Aetherite Silo");
            }
        }
        else if (buildingName === "Barracks")
        {
            if (GameApi.base.buildings.barracks.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Barracks");
            }
        }
        else if (buildingName === "Docking Station")
        {
            if (GameApi.base.buildings.dockingStation.tryUpgrading())
            {
                updateRequestedFromBuildingMenu();
                markAsUpgradedSignal("Docking Station");
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
        transitionRoot.duration = transitionRoot.baseDuration * GameApi.animMultiplier();

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

    function reactToBackOnToolbar()
    {
        if (centralUnit.visible)
            return centralUnit.reactToBackOnToolbar();
        if (hospital.visible)
            return hospital.reactToBackOnToolbar();
        if (trainingGround.visible)
            return trainingGround.reactToBackOnToolbar();
        if (gym.visible)
            return gym.reactToBackOnToolbar();
        if (laboratory.visible)
            return laboratory.reactToBackOnToolbar();
        if (playingField.visible)
            return playingField.reactToBackOnToolbar();
        if (bar.visible)
            return bar.reactToBackOnToolbar();
        if (shrine.visible)
            return shrine.reactToBackOnToolbar();
        if (seclusion.visible)
            return seclusion.reactToBackOnToolbar();
        if (powerplant.visible)
            return powerplant.reactToBackOnToolbar();
        if (factory.visible)
            return factory.reactToBackOnToolbar();
        if (coolRoom.visible)
            return coolRoom.reactToBackOnToolbar();
        if (storageRoom.visible)
            return storageRoom.reactToBackOnToolbar();
        if (aetheriteSilo.visible)
            return aetheriteSilo.reactToBackOnToolbar();
        if (barracks.visible)
            return barracks.reactToBackOnToolbar();
        if (dockingStation.visible)
            return dockingStation.reactToBackOnToolbar();
    }

    function returnToDefault()
    {
        if (centralUnit.visible)
            centralUnit.returnToDefault();
        else if (hospital.visible)
            hospital.returnToDefault();
        else if (trainingGround.visible)
            trainingGround.returnToDefault();
        else if (gym.visible)
            gym.returnToDefault();
        else if (laboratory.visible)
            laboratory.returnToDefault();
        else if (playingField.visible)
            playingField.returnToDefault();
        else if (bar.visible)
            bar.returnToDefault();
        else if (shrine.visible)
            shrine.returnToDefault();
        else if (seclusion.visible)
            seclusion.returnToDefault();
        else if (powerplant.visible)
            powerplant.returnToDefault();
        else if (factory.visible)
            factory.returnToDefault();
        else if (coolRoom.visible)
            coolRoom.returnToDefault();
        else if (storageRoom.visible)
            storageRoom.returnToDefault();
        else if (aetheriteSilo.visible)
            aetheriteSilo.returnToDefault();
        else if (barracks.visible)
            barracks.returnToDefault();
        else if (dockingStation.visible)
            dockingStation.returnToDefault();
    }

    function requestUnban(mercenaryName, buildingName)
    {
        if (buildingName == "Hospital")
            hospital.requestUnban(mercenaryName);
        else if (buildingName == "Training Ground")
            trainingGround.requestUnban(mercenaryName);
        else if (buildingName == "Gym")
            gym.requestUnban(mercenaryName);
        else if (buildingName == "Laboratory")
            laboratory.requestUnban(mercenaryName);
        else if (buildingName == "Playing Field")
            playingField.requestUnban(mercenaryName);
        else if (buildingName == "Bar")
            bar.requestUnban(mercenaryName);
        else if (buildingName == "Shrine")
            shrine.requestUnban(mercenaryName);
        else if (buildingName == "Seclusion")
            seclusion.requestUnban(mercenaryName);
    }

    function acknowledgeConsoleHiding()
    {
        laboratory.acknowledgeConsoleHiding();
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
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    TrainingGroundMenu {
        id: trainingGround

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Training Ground")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    GymMenu {
        id: gym

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Gym")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    LaboratoryMenu {
        id: laboratory

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Laboratory")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
        onShowSpecial: parent.showSpecial()
    }
    PlayingFieldMenu {
        id: playingField

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Playing Field")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    BarMenu {
        id: bar

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Bar")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    ShrineMenu {
        id: shrine

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Shrine")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    SeclusionMenu {
        id: seclusion

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Seclusion")
        onMercenariesModeUpdateRequested: root.mercenariesModeUpdateRequested()
    }
    PowerplantMenu {
        id: powerplant

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Powerplant")
        onResourcesUpdateRequested: updateRequestedFromBuildingMenu()
    }
    FactoryMenu {
        id: factory

        anchors.fill: parent

        onBackClicked: backClickedFwd()
        onUpgradeRequested: requestUpgrade("Factory")
        onResourcesUpdateRequested: updateRequestedFromBuildingMenu()
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
        onResourcesUpdateRequested: updateRequestedFromBuildingMenu()
        onMercenariesModeUpdateRequested: updateRequestedFromBuildingMenu()
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: root; y: height }
        }
    ]

    transitions: Transition {
        NumberAnimation { id: transitionRoot; properties: "y"; easing.type: Easing.InQuad; duration: baseDuration; property int baseDuration: 500 }
    }

    Component.onCompleted: {
        changeToCentralUnit();
    }
}

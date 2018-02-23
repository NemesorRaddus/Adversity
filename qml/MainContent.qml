import QtQuick 2.9
import "./BuildingsMode"
import "./MercenariesMode"
import "./MissionsMode"
import "./Reports"
import "./Settings"
import Game 1.0

Item {
    id: root

    property alias energyValue: energyText
    property alias energyValue2: energyText2
    property alias buildingMaterialsValue: buildingMaterialsText
    property alias buildingMaterialsValue2: buildingMaterialsText2
    property alias foodSuppliesValue: foodSuppliesText
    property alias foodSuppliesValue2: foodSuppliesText2
    property alias aetheriteValue: aetheriteText
    property alias aetheriteValue2: aetheriteText2

    property alias hourValue: hour
    property alias dayValue: day

    property int currentMode: 0

    function changeMode(mode)
    {
        reportsList.state = "hidden";
        settings.hide();

        if (currentMode == 0)
            missionsGUI.returnToDefault();
        else if (currentMode == 1)
            buildingsGUI.returnToDefault();
        else if (currentMode == 2)
            mercenariesGUI.returnToDefault();

        currentMode = mode;

        if (mode == 0)
        {
            missionsGUI.state = "";
            buildingsGUI.state = "hiddenRight";
            mercenariesGUI.state = "hiddenRight2";
        }
        else if (mode == 1)
        {
            missionsGUI.state = "hiddenLeft";
            buildingsGUI.state = "";
            mercenariesGUI.state = "hiddenRight";
        }
        else if (mode == 2)
        {
            missionsGUI.state = "hiddenLeft2";
            buildingsGUI.state = "hiddenLeft";
            mercenariesGUI.state = "";
        }
    }

    function updateResources()
    {
        energyValue.text = GameApi.base.resources.currentEnergyAmount() + '/' + GameApi.base.buildings.powerplant.energyLimit();
        if (GameApi.base.resources.currentEnergyAmount() === 0)
            energyValue.color = "#b30000";
        else if (GameApi.base.resources.currentEnergyAmount() === GameApi.base.buildings.powerplant.energyLimit())
            energyValue.color = "#ffd480";
        else
            energyValue.color = "#c0efc0";

        foodSuppliesValue.text = GameApi.base.resources.currentFoodSuppliesAmount() + '/' + GameApi.base.buildings.coolRoom.foodSuppliesLimit();
        if (GameApi.base.resources.currentFoodSuppliesAmount() === 0)
            foodSuppliesValue.color = "#b30000";
        else if (GameApi.base.resources.currentFoodSuppliesAmount() === GameApi.base.buildings.coolRoom.foodSuppliesLimit())
            foodSuppliesValue.color = "#ffd480";
        else
            foodSuppliesValue.color = "#c0efc0";

        buildingMaterialsValue.text = GameApi.base.resources.currentBuildingMaterialsAmount() + '/' + GameApi.base.buildings.storageRoom.buildingMaterialsLimit();
        if (GameApi.base.resources.currentBuildingMaterialsAmount() === 0)
            buildingMaterialsValue.color = "#b30000";
        else if (GameApi.base.resources.currentBuildingMaterialsAmount() === GameApi.base.buildings.storageRoom.buildingMaterialsLimit())
            buildingMaterialsValue.color = "#ffd480";
        else
            buildingMaterialsValue.color = "#c0efc0";

        aetheriteValue.text = GameApi.base.resources.currentAetheriteAmount() + '/' + GameApi.base.buildings.aetheriteSilo.aetheriteLimit();
        if (GameApi.base.resources.currentAetheriteAmount() === 0)
            aetheriteValue.color = "#b30000";
        else if (GameApi.base.resources.currentAetheriteAmount() === GameApi.base.buildings.aetheriteSilo.aetheriteLimit())
            aetheriteValue.color = "#ffd480";
        else
            aetheriteValue.color = "#c0efc0";

        energyValue2.text = GameApi.base.resources.currentEnergyIncome() + '/' + "day";
        foodSuppliesValue2.text = GameApi.base.resources.currentFoodSuppliesIncome() + '/' + "day";
        buildingMaterialsValue2.text = GameApi.base.resources.currentBuildingMaterialsIncome() + '/' + "day";
        aetheriteValue2.text = GameApi.base.resources.currentAetheriteIncome() + '/' + "day";
    }

    function updateClock()
    {
        dayValue.text = "Day " + GameApi.base.gameClock.currentDay();

        hourValue.text = (GameApi.base.gameClock.currentHour() < 10 ?
                              '0' + GameApi.base.gameClock.currentHour() :
                              GameApi.base.gameClock.currentHour())
                + ':' +
                (GameApi.base.gameClock.currentMin() < 10 ?
                     '0' + GameApi.base.gameClock.currentMin() :
                     GameApi.base.gameClock.currentMin());
    }

    function updateMainContent()
    {
        buildingsGUI.updateEverything();
        buildingsGUI.updateEverything();
        buildingsGUI.updateEverything();
    }

    function updateEverything()
    {
        updateResources();
        updateClock();
        updateMainContent();
        reportsList.updateEverything();
        settings.update();
    }

    function showReportNotification()
    {
        reportsNotification.setAmount(GameApi.base.reports.amountOfNewReports());
        reportsNotification.show();
    }

    BuildingsModeGUI {
        id: buildingsGUI

        x: 0
        y: 189
        width: parent.width
        height: 1464

        onUpdateRequestedFromBuildingsModeGUI: root.updateEverything();

        onMercenariesModeUpdateRequested: mercenariesGUI.updateEverything();

        onShowSpecial: h4xScreen.visible = true;
    }

    MercenariesModeGUI {
        id: mercenariesGUI

        x: 0
        y: 189
        width: parent.width
        height: 1464

        onUpdateRequestedFromMercenariesModeGUI: root.updateEverything();

        onBuildingMenuRequested: {
            changeMode(1);
            buildingsGUI.changeBuilding(buildingName);
        }

        onDismissClickedFwd: mercenaryDismissConfirmDialog.show();
        onDismissDialogHidingRequested: mercenaryDismissConfirmDialog.hide();

        onUnbanRequested: buildingsGUI.requestUnban(mercenaryName, buildingName);

        onArtPreviewRequested: mercenaryArtPreview.show(artSource);
        onArtPreviewHidingRequested: mercenaryArtPreview.hide();
    }

    MissionsModeGUI {
        id: missionsGUI

        x: 0
        y: 189
        width: parent.width
        height: 1464

        onMercenariesModeUpdateRequested: mercenariesGUI.updateEverything();

        onResourcesUpdateRequested: root.updateResources();
    }

    ReportsNotification {
        id: reportsNotification

        x: 1080 - width
        y: 1400
        width: 425
        height: 200

        onClicked: {
            reportsList.updateEverything();
            reportsList.state = "";
        }
    }

    ReportsList {
        id: reportsList

        x: 0
        y: 189
        width: parent.width
        height: 1464

        onBackClicked: state = "hidden";
    }

    Image {
        id: topAndBottomBar

        anchors.fill: parent

        source: "qrc:/graphics/GUI/GUI.png"

        MouseArea {
            id: missionsButton

            x: 57
            y: 1727
            width: 272
            height: 141

            visible: true

            onClicked: root.changeMode(0);
        }
        ModeButtonLight {
            id: missionsButtonLight

            x: missionsButton.x + 2
            y: missionsButton.y - 63.5
            width: 268
            height: 268
        }

        MouseArea {
            id: baseButton

            x: 403
            y: 1727
            width: 272
            height: 141

            visible: true

            onClicked: root.changeMode(1);
        }
        ModeButtonLight {
            id: baseButtonLight

            x: baseButton.x + 2
            y: baseButton.y - 63.5
            width: 268
            height: 268
        }

        MouseArea {
            id: mercenariesButton

            x: 751
            y: 1727
            width: 272
            height: 141

            visible: true

            onClicked: root.changeMode(2);
        }
        ModeButtonLight {
            id: mercenariesButtonLight

            x: mercenariesButton.x + 2
            y: mercenariesButton.y - 63.5
            width: 268
            height: 268
        }

        MouseArea {
            id: reportsOpener

            x: 0
            y: 0
            width: parent.width
            height: 125

            onClicked: {
                reportsList.updateEverything();
                reportsList.state = "";
            }
        }

        Image {
            id: energyIcon

            x: -12
            y: 20
            width: 90
            height: 90

            source: "qrc:/graphics/GUI/Resources/Energy.png"
        }
        Text {
            id: energyText

            x: 53
            y: 18
            width: 166
            height: 39

            color: "#c0efc0"
            text: qsTr("1000/1000")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }
        Text {
            id: energyText2

            x: 72
            y: 64
            width: 132
            height: 39

            color: "#c0efc0"
            text: qsTr("100/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }

        Image {
            id: buildingMaterialsIcon

            x: 200
            y: 15
            width: 98
            height: 98

            source: "qrc:/graphics/GUI/Resources/Buildingmaterials.png"
        }
        Text {
            id: buildingMaterialsText

            x: 286
            y: 18
            width: 128
            height: 39

            color: "#c0efc0"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }
        Text {
            id: buildingMaterialsText2

            x: 292
            y: 64
            width: 115
            height: 39

            color: "#c0efc0"
            text: qsTr("10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }

        Image {
            id: foodSuppliesIcon

            x: 420
            y: 18
            width: 88
            height: 88

            source: "qrc:/graphics/GUI/Resources/Foodsupplies.png"
        }
        Text {
            id: foodSuppliesText

            x: 504
            y: 18
            width: 137
            height: 39

            color: "#c0efc0"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }
        Text {
            id: foodSuppliesText2

            x: 510
            y: 64
            width: 121
            height: 39

            color: "#c0efc0"
            text: qsTr("-10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }

        Image {
            id: aetheriteIcon

            x: 628
            y: 18
            width: 90
            height: 90

            source: "qrc:/graphics/GUI/Resources/Aetherite.png"
        }
        Text {
            id: aetheriteText

            x: 714
            y: 18
            width: 137
            height: 39

            color: "#c0efc0"
            text: qsTr("100/100")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }
        Text {
            id: aetheriteText2

            x: 714
            y: 64
            width: 131
            height: 39

            color: "#c0efc0"
            text: qsTr("-10/DAY")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 34
            font.family: fontStencil.name
        }

        Text {
            id: hour

            x: 870
            y: 8
            width: 129
            height: 55

            color: "#c0efc0"
            text: qsTr("12:00")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 48
            font.family: fontStencil.name
        }
        Text {
            id: day

            x: 873
            y: 64

            color: "#c0efc0"
            text: qsTr("DAY 1380")
            font.pixelSize: 43
            font.family: fontStencil.name
        }
        Item {
            id: settingsItem

            x: 1005
            y: 3
            width: 70
            height: 70

            property alias mouseArea: settingsMA

            Image {
                id: settingsImage

                anchors.fill: parent

                source: "qrc:/graphics/GUI/Settings.png"
            }
            MouseArea {
                id: settingsMA

                x: -132
                y: -3
                width: 217
                height: 129

                onClicked: settings.show();
            }
        }
    }

    Settings {
        id: settings

        x: 0
        y: 189
        width: parent.width
        height: 1464

        onBackClicked: hide();
    }

    H4XScreen {
        id: h4xScreen

        anchors.fill: parent

        visible: false

        onHiding: buildingsGUI.acknowledgeConsoleHiding();
    }

    MercenaryArtPreview {
        id: mercenaryArtPreview

        anchors.fill: parent

        onClosing: mercenariesGUI.acknowledgeArtPreviewClosing();
    }

    ConfirmDialog {
        id: mercenaryDismissConfirmDialog

        anchors.fill: parent

        onAccepted: mercenariesGUI.dismissMercenaryFwd();
        onDeclined: mercenariesGUI.acknowledgeConfirmDialogClosing();
    }

    FontLoader {
        id: fontStencil

        source: "qrc:/fonts/STENCIL.TTF"
    }
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJSValue>

#include "base/base.h"
#include "base/buildings/specific/storage/aetheritesilo.h"
#include "base/buildings/specific/destressing/bar.h"
#include "base/buildings/specific/other/barracks.h"
#include "base/buildings/specific/other/centralunit.h"
#include "base/buildings/specific/storage/coolroom.h"
#include "base/buildings/specific/other/dockingstation.h"
#include "base/buildings/specific/production/factory.h"
#include "base/buildings/specific/training/gym.h"
#include "base/buildings/specific/other/hospital.h"
#include "base/buildings/specific/training/laboratory.h"
#include "base/buildings/specific/destressing/playingfield.h"
#include "base/buildings/specific/production/powerplant.h"
#include "base/buildings/specific/destressing/seclusion.h"
#include "base/buildings/specific/destressing/shrine.h"
#include "base/buildings/specific/storage/storageroom.h"
#include "base/buildings/specific/training/trainingground.h"
#include "base/managers/buildingsmanager.h"
#include "base/managers/equipmentmanager.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/missionsmanager.h"
#include "base/managers/reportsmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "database/database.h"
#include "general/appbuildinfo.h"
#include "general/game.h"
#include "general/globalutilities.h"
#include "general/randomizer.h"
#include "general/savesmanager.h"
#include "h4x/h4x.h"
#include "logging/loggershandler.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/land.h"
#include "missions/mission.h"
#include "qml_components/fpscounter.h"
#include "qml_components/signaltransmitter.h"
#include "reports/unifiedreport.h"

void setUpAppMainData(int argc, char *argv[]) noexcept
{
	QGuiApplication app(argc, argv);
	QGuiApplication::setApplicationDisplayName("Adversity");
	QGuiApplication::setApplicationName("Adversity");
	QGuiApplication::setOrganizationName("Raddos Games");
	QGuiApplication::setApplicationVersion("1.0.2-beta");
}

void initializeRandomizer() noexcept
{
	Randomizer::initialize();
}

void registerQMLComponents() noexcept
{
	qmlRegisterType<FPSText> ("FPSComponent",1,0,"FPSCounter");
	qmlRegisterType<SignalTransmitter> ("SignalTransmitter",1,0,"SignalTransmitter");
}

void registerExposedCppClassesInQML() noexcept
{
	qmlRegisterInterface<Base> ("Base");
	qmlRegisterInterface<BuildingsManager> ("BuildingsManager");
	qmlRegisterInterface<EquipmentManager> ("EquipmentManager");
	qmlRegisterInterface<MercenariesManager> ("MercenariesManager");
	qmlRegisterInterface<MissionsManager> ("MissionsManager");
	qmlRegisterInterface<ReportsManager> ("ReportsManager");
	qmlRegisterInterface<ResourcesManager> ("ResourcesManager");
	qmlRegisterInterface<CentralUnit> ("CentralUnit");
	qmlRegisterInterface<Hospital> ("Hospital");
	qmlRegisterInterface<TrainingGround> ("TrainingGround");
	qmlRegisterInterface<Gym> ("Gym");
	qmlRegisterInterface<Laboratory> ("Laboratory");
	qmlRegisterInterface<PlayingField> ("PlayingField");
	qmlRegisterInterface<Bar> ("Bar");
	qmlRegisterInterface<Shrine> ("Shrine");
	qmlRegisterInterface<Seclusion> ("Seclusion");
	qmlRegisterInterface<Powerplant> ("Powerplant");
	qmlRegisterInterface<Factory> ("Factory");
	qmlRegisterInterface<CoolRoom> ("CoolRoom");
	qmlRegisterInterface<StorageRoom> ("StorageRoom");
	qmlRegisterInterface<AetheriteSilo> ("AetheriteSilo");
	qmlRegisterInterface<Barracks> ("Barracks");
	qmlRegisterInterface<DockingStation> ("DockingStation");
	qmlRegisterInterface<AppBuildInfo> ("AppBuildInfo");
	qmlRegisterInterface<Database> ("Database");
	qmlRegisterInterface<Equipment> ("Equipment");
	qmlRegisterInterface<GameClock> ("GameClock");
	qmlRegisterInterface<GlobalUtilities> ("GlobalUtilities");
	qmlRegisterInterface<H4X> ("H4X");
	qmlRegisterInterface<Land> ("Land");
	qmlRegisterInterface<LandsInfo> ("LandsInfo");
	qmlRegisterInterface<LoggersHandler> ("LoggersHandler");
	qmlRegisterInterface<MercenariesContainer> ("MercenariesContainer");
	qmlRegisterInterface<Mercenary> ("Mercenary");
	qmlRegisterInterface<Mission> ("Mission");
	qmlRegisterInterface<MissionInitializer> ("MissionInitializer");
	qmlRegisterInterface<SavesManager> ("SavesManager");
	qmlRegisterInterface<UnifiedReport> ("UnifiedReport");
}

void createGameObject() noexcept
{
	qmlRegisterSingletonType<Game> ("Game", 1, 0, "GameApi", gameQObjectSingletonTypeProvider);
}

void prepareH4XEngine(QQmlApplicationEngine &engine) noexcept
{
	H4X{&engine};
}

void registerQMLEngineInGame(QQmlApplicationEngine &engine) noexcept
{
	Game::setQMLEnginePtr(&engine);
}

void registerExposedCppClassesInJS(QQmlApplicationEngine &engine) noexcept
{
	QJSValue globalsObj = engine.newQObject(new GlobalUtilities);
	engine.globalObject().setProperty("GlobalsCpp", globalsObj);
}

void startQMLEngine(QQmlApplicationEngine &engine) noexcept
{
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
}

void setUpConsoleWindow(QQmlApplicationEngine &engine) noexcept
{
#ifdef ENABLE_CONSOLE_WINDOW
	engine.load("../GameBase/qml/H4XWindow.qml");
	bool *eventFiltersLocker = new bool(0);
	MainWindowEventFilter mwef{engine.rootObjects()[1], eventFiltersLocker};
	ConsoleWindowEventFilter cwef{engine.rootObjects()[0], eventFiltersLocker};
	engine.rootObjects()[0]->installEventFilter(&mwef);
	engine.rootObjects()[1]->installEventFilter(&cwef);
#endif
}

int main(int argc, char *argv[])
{
	setUpAppMainData(argc, argv);

	initializeRandomizer();

	registerQMLComponents();

	registerExposedCppClassesInQML();

	createGameObject();

    QQmlApplicationEngine engine;

	prepareH4XEngine(engine);

	registerQMLEngineInGame(engine);

	registerExposedCppClassesInJS(engine);

	startQMLEngine(engine);

#ifdef ENABLE_CONSOLE_WINDOW
	setUpConsoleWindow(engine);
#endif

	return QGuiApplication::instance()->exec();
}

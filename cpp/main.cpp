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
#include "h4x/h4x.h"
#include "logging/loggershandler.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/land.h"
#include "missions/mission.h"
#include "qml_components/fpscounter.h"
#include "reports/unifiedreport.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName("Adversity");
    QGuiApplication::setApplicationName("Adversity");
    QGuiApplication::setOrganizationName("Raddos Games");
    QGuiApplication::setApplicationVersion("1.0.2-beta");

    Randomizer::initialize();

    qmlRegisterType<FPSText>("FPSComponent",1,0,"FPSCounter");

    qmlRegisterInterface<Base>("Base");
    qmlRegisterInterface<BuildingsManager>("BuildingsManager");
    qmlRegisterInterface<EquipmentManager>("EquipmentManager");
    qmlRegisterInterface<MercenariesManager>("MercenariesManager");
    qmlRegisterInterface<MissionsManager>("MissionsManager");
    qmlRegisterInterface<ReportsManager>("ReportsManager");
    qmlRegisterInterface<ResourcesManager>("ResourcesManager");
    qmlRegisterInterface<CentralUnit>("CentralUnit");
    qmlRegisterInterface<Hospital>("Hospital");
    qmlRegisterInterface<TrainingGround>("TrainingGround");
    qmlRegisterInterface<Gym>("Gym");
    qmlRegisterInterface<Laboratory>("Laboratory");
    qmlRegisterInterface<PlayingField>("PlayingField");
    qmlRegisterInterface<Bar>("Bar");
    qmlRegisterInterface<Shrine>("Shrine");
    qmlRegisterInterface<Seclusion>("Seclusion");
    qmlRegisterInterface<Powerplant>("Powerplant");
    qmlRegisterInterface<Factory>("Factory");
    qmlRegisterInterface<CoolRoom>("CoolRoom");
    qmlRegisterInterface<StorageRoom>("StorageRoom");
    qmlRegisterInterface<AetheriteSilo>("AetheriteSilo");
    qmlRegisterInterface<Barracks>("Barracks");
    qmlRegisterInterface<DockingStation>("DockingStation");
    qmlRegisterInterface<GameClock>("GameClock");
    qmlRegisterInterface<Mercenary>("Mercenary");
    qmlRegisterInterface<MercenariesContainer>("MercenariesContainer");
    qmlRegisterInterface<Equipment>("Equipment");
    qmlRegisterInterface<Mission>("Mission");
    qmlRegisterInterface<MissionInitializer>("MissionInitializer");
    qmlRegisterInterface<Land>("Land");
    qmlRegisterInterface<LandsInfo>("LandsInfo");
    qmlRegisterInterface<Database>("Database");
    qmlRegisterInterface<AppBuildInfo>("AppBuildInfo");
    qmlRegisterInterface<GlobalUtilities>("GlobalUtilities");
    qmlRegisterInterface<UnifiedReport>("UnifiedReport");
    qmlRegisterInterface<LoggersHandler>("LoggersHandler");

    qmlRegisterSingletonType<Game>("Game", 1, 0, "GameApi", gameQObjectSingletontypeProvider);

    QQmlApplicationEngine engine;

    H4X{&engine};

    Game::setQMLEnginePtr(&engine);

    QJSValue globalsObj = engine.newQObject(new GlobalUtilities);
    engine.globalObject().setProperty("GlobalsCpp", globalsObj);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

#ifdef ENABLE_CONSOLE_WINDOW
    engine.load("../GameBase/qml/H4XWindow.qml");
    bool *eventFiltersLocker=new bool(0);
    MainWindowEventFilter mwef{engine.rootObjects()[1], eventFiltersLocker};
    ConsoleWindowEventFilter cwef{engine.rootObjects()[0], eventFiltersLocker};
    engine.rootObjects()[0]->installEventFilter(&mwef);
    engine.rootObjects()[1]->installEventFilter(&cwef);
#endif

    return app.exec();
}

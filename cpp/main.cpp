#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJSValue>

#include "base/base.h"
#include "base/buildings/aetheritesilo.h"
#include "base/buildings/bar.h"
#include "base/buildings/barracks.h"
#include "base/buildings/centralunit.h"
#include "base/buildings/coolroom.h"
#include "base/buildings/dockingstation.h"
#include "base/buildings/factory.h"
#include "base/buildings/gym.h"
#include "base/buildings/hospital.h"
#include "base/buildings/laboratory.h"
#include "base/buildings/playingfield.h"
#include "base/buildings/powerplant.h"
#include "base/buildings/seclusion.h"
#include "base/buildings/shrine.h"
#include "base/buildings/storageroom.h"
#include "base/buildings/trainingground.h"
#include "clock/gameclock.h"
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
    QGuiApplication::setApplicationVersion("1.0.1-beta");

    Randomizer::initialize();

    qmlRegisterType<FPSText>("FPSComponent",1,0,"FPSCounter");

    qmlRegisterInterface<Base>("Base");
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
    qmlRegisterInterface<MercenariesContainer>("MercenariesContainer");
    qmlRegisterInterface<Equipment>("Equipment");
    qmlRegisterInterface<Mission>("Mission");
    qmlRegisterInterface<MissionInitializer>("MissionInitializer");
    qmlRegisterInterface<Land>("Land");
    qmlRegisterInterface<LandsInfo>("LandsInfo");
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

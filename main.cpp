#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "game.h"
#include "timer.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName("Adversity");
    QGuiApplication::setApplicationName("Adversity");
    QGuiApplication::setOrganizationName("Raddos Games");

    Randomizer::initialize();

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
    qmlRegisterSingletonType<Game>("Game", 1, 0, "GameApi", gameQObjectSingletontypeProvider);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

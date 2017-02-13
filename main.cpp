#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

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
    qmlRegisterInterface<PowerPlant>("PowerPlant");
    qmlRegisterInterface<Factory>("Factory");
    qmlRegisterInterface<CoolRoom>("CoolRoom");
    qmlRegisterInterface<StorageRoom>("StorageRoom");
    qmlRegisterInterface<AetheriteSilo>("AetheriteSilo");
    qmlRegisterInterface<Barracks>("Barracks");
    qmlRegisterInterface<DockingStation>("DockingStation");
    qmlRegisterSingletonType<Game>("Game", 1, 0, "GameApi", gameQObjectSingletontypeProvider);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    exit(app.exec());
}

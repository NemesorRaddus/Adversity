#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Randomizer::initialize();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

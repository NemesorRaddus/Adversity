#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "base.h"
#include "filereaderwriter.h"

class QQmlEngine;
class QJSEngine;

class Game : public QObject
{
    Q_OBJECT
public:
    Game(QObject *parent = 0) noexcept;

    Q_INVOKABLE Base *base() noexcept
    {
        return &m_base;
    }

private:
    Base m_base;
};

static QObject *gameQObjectSingletontypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Game *game = new Game();
    return game;
}

#endif // GAME_H

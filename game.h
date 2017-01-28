#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "rrefsingleton.h"

#include "base.h"
#include "filereaderwriter.h"

class Game : public QObject
{
    Q_OBJECT
    friend class RRefSingleton <Game>;
public:
    static Game &instance() noexcept
    {
        return RRefSingleton <Game>::getInstance()();
    }
    void start() noexcept;

private:
    Game() noexcept;

    Base m_base;
};

#endif // GAME_H

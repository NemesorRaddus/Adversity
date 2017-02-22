#include "game.h"

Game::Game(QObject *parent) noexcept
    : QObject(parent)
{
    m_base=new Base;
}

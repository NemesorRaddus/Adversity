#include "levelsinfo.h"

#include "general/game.h"
#include "logging/loggershandler.h"

AnyBuildingLevelsInfo::~AnyBuildingLevelsInfo() noexcept
{
    for (auto &e : m_levelsInfo)
        delete e;
}

unsigned AnyBuildingLevelsInfo::maxLevel() const noexcept
{
    return m_levelsInfo.size()-1;
}

void AnyBuildingLevelsInfo::reportFailure() noexcept
{
    Game::gameInstance()->loggers()->buildingsLogger()->error("AnyBuildingLevelsInfo was called on a noncompliant type.");
}

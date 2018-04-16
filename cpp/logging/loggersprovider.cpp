#include "loggersprovider.h"

#include "libs/spdlog-0.14.0/logger.h"

#include "loggershandler.h"
#include "general/game.h"

LoggerAbstraction *LoggersProvider::mainLogger() noexcept
{
    static LoggerAbstraction *r{new LoggerAbstraction{getGameLoggersHandler()->mainLogger().get()}};
    return r;
}

LoggerAbstraction *LoggersProvider::missionsLogger() noexcept
{
    static LoggerAbstraction *r{new LoggerAbstraction{getGameLoggersHandler()->missionsLogger().get()}};
    return r;
}

LoggerAbstraction *LoggersProvider::buildingsLogger() noexcept
{
    static LoggerAbstraction *r{new LoggerAbstraction{getGameLoggersHandler()->buildingsLogger().get()}};
    return r;
}

LoggerAbstraction *LoggersProvider::mercenariesLogger() noexcept
{
    static LoggerAbstraction *r{new LoggerAbstraction{getGameLoggersHandler()->mercenariesLogger().get()}};
    return r;
}

LoggerAbstraction *LoggersProvider::xmlLogger() noexcept
{
    static LoggerAbstraction *r{new LoggerAbstraction{getGameLoggersHandler()->xmlLogger().get()}};
    return r;
}

LoggersHandler *LoggersProvider::getGameLoggersHandler() noexcept
{
    return Game::gameInstance()->loggers();
}

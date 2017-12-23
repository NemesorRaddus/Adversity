#pragma once

#include "loggerabstraction.h"

class LoggersHandler;

class LoggersProvider
{
public:
    static LoggerAbstraction *mainLogger() noexcept;
    static LoggerAbstraction *missionsLogger() noexcept;
    static LoggerAbstraction *buildingsLogger() noexcept;
    static LoggerAbstraction *mercenariesLogger() noexcept;
    static LoggerAbstraction *xmlLogger() noexcept;

private:
    static LoggersHandler *getGameLoggersHandler() noexcept;
};

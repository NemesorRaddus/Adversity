#include "loggerabstraction.h"

LoggerAbstraction::LoggerAbstraction(spdlog::logger * const realLogger) noexcept
    : m_realLogger(realLogger) {}

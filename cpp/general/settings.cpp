#include "settings.h"

Settings::Settings() noexcept
    : m_animsSpeed(AS_Normal), m_showFPS(0), m_logsAmount(LA_None) {}

void Settings::setAnimationsSpeed(Settings::AnimationsSpeed speed) noexcept
{
    m_animsSpeed = speed;
}

void Settings::showFPS(bool enabled) noexcept
{
    m_showFPS = enabled;
}

void Settings::setLogsAmount(Settings::LogsAmount amount) noexcept
{
    m_logsAmount = amount;
}

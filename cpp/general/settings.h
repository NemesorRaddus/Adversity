#pragma once

class Settings
{
public:
    enum AnimationsSpeed
    {
        AS_None,
        AS_Slow,
        AS_Normal,
        AS_Fast,
        AS_END
    };
    enum LogsAmount
    {
        LA_None,
        LA_Some,
        LA_Most,
        LA_All,
        LA_END
    };

    Settings() noexcept;

    void setAnimationsSpeed(AnimationsSpeed speed) noexcept;
    void showFPS(bool enabled) noexcept;
    void setLogsAmount(LogsAmount amount) noexcept;

    inline AnimationsSpeed animationsSpeed() const noexcept
    {
        return m_animsSpeed;
    }
    inline bool showsFPS() const noexcept
    {
        return m_showFPS;
    }
    inline LogsAmount logsAmount() const noexcept
    {
        return m_logsAmount;
    }

private:
    AnimationsSpeed m_animsSpeed;
    bool m_showFPS;
    LogsAmount m_logsAmount;
};

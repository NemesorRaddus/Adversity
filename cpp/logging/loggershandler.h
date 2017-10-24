#pragma once

#include <QObject>

#include "libs/spdlog-0.14.0/spdlog.h"

class LoggersHandler : public QObject
{
    Q_OBJECT

public:
    LoggersHandler() noexcept;
    ~LoggersHandler() noexcept;

    void setLevel(spdlog::level::level_enum lvl) noexcept;

    // For QML only!
    Q_INVOKABLE void trace(const QString &msg) noexcept;
    Q_INVOKABLE void debug(const QString &msg) noexcept;
    Q_INVOKABLE void info(const QString &msg) noexcept;
    Q_INVOKABLE void warn(const QString &msg) noexcept;
    Q_INVOKABLE void error(const QString &msg) noexcept;
    Q_INVOKABLE void critical(const QString &msg) noexcept;

    Q_INVOKABLE void traceIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void debugIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void infoIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void warnIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void errorIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void criticalIf(bool cond, const QString &msg) noexcept;

    // these are for C++
    inline auto mainLogger() noexcept
    {
        return m_mainLogger;
    }
    inline auto missionsLogger() noexcept
    {
        return m_missionsLogger;
    }
    inline auto buildingsLogger() noexcept
    {
        return m_buildingsLogger;
    }
    inline auto mercenariesLogger() noexcept
    {
        return m_mercenariesLogger;
    }
    inline auto xmlLogger() noexcept
    {
        return m_xmlLogger;
    }

    inline auto qtLogger() noexcept
    {
        return m_qtLogger;
    }

    static void redirectQtMsgs(QtMsgType type, const QMessageLogContext &, const QString &msg) noexcept;

    Q_INVOKABLE inline QString outputPath() const noexcept
    {
        return m_outputPath;
    }

private:
    bool isLoggingEnabled() const noexcept;

    QString m_outputPath;
    std::shared_ptr <spdlog::sinks::app_start_rotating_file_sink_st> m_output;
    std::shared_ptr <spdlog::sinks::null_sink_st> m_noOutput;//probably could change those 2 into one thing, but meh
    std::shared_ptr <spdlog::logger> m_mainLogger;
    std::shared_ptr <spdlog::logger> m_missionsLogger;
    std::shared_ptr <spdlog::logger> m_buildingsLogger;
    std::shared_ptr <spdlog::logger> m_mercenariesLogger;
    std::shared_ptr <spdlog::logger> m_xmlLogger;
    std::shared_ptr <spdlog::logger> m_qmlLogger;
    std::shared_ptr <spdlog::logger> m_qtLogger;
};

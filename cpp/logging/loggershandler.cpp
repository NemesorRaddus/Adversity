#include "loggershandler.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include "general/appbuildinfo.h"
#include "general/game.h"

LoggersHandler::LoggersHandler() noexcept
{
    try
    {
        if (isLoggingEnabled())
        {
#ifdef ANDROID // QStandardPaths was giving strange paths for Android devices
            m_outputPath = "/storage/emulated/0/Android/data/com.raddosgames.adversity/logs";
#else
            m_outputPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/logs";
#endif
            QDir().mkpath(m_outputPath);
            m_output = std::make_shared<spdlog::sinks::app_start_rotating_file_sink_st>(m_outputPath.toStdString()+"/adversity.log",40);

            m_mainLogger = std::make_shared<spdlog::logger>("Main", m_output);
            m_missionsLogger = std::make_shared<spdlog::logger>("MissionsModule", m_output);
            m_buildingsLogger = std::make_shared<spdlog::logger>("BuildingsModule", m_output);
            m_mercenariesLogger = std::make_shared<spdlog::logger>("MercenariesModule", m_output);
            m_xmlLogger = std::make_shared<spdlog::logger>("XML", m_output);
            m_qmlLogger = std::make_shared<spdlog::logger>("QML", m_output);
            m_qtLogger = std::make_shared<spdlog::logger>("Qt", m_output);

#ifdef ANDROID
            qInstallMessageHandler(LoggersHandler::redirectQtMsgs);
#endif

        }
        else
        {
            m_noOutput = std::make_shared<spdlog::sinks::null_sink_st>();

            m_mainLogger = std::make_shared<spdlog::logger>("Main", m_noOutput);
            m_missionsLogger = std::make_shared<spdlog::logger>("MissionsModule", m_noOutput);
            m_buildingsLogger = std::make_shared<spdlog::logger>("BuildingsModule", m_noOutput);
            m_mercenariesLogger = std::make_shared<spdlog::logger>("MercenariesModule", m_noOutput);
            m_xmlLogger = std::make_shared<spdlog::logger>("XML", m_noOutput);
            m_qmlLogger = std::make_shared<spdlog::logger>("Gui", m_noOutput);
            m_qtLogger = std::make_shared<spdlog::logger>("Qt", m_noOutput);
        }

        spdlog::register_logger(m_mainLogger);
        spdlog::register_logger(m_missionsLogger);
        spdlog::register_logger(m_buildingsLogger);
        spdlog::register_logger(m_mercenariesLogger);
        spdlog::register_logger(m_xmlLogger);
        spdlog::register_logger(m_qmlLogger);
        spdlog::register_logger(m_qtLogger);

        spdlog::set_async_mode(1, spdlog::async_overflow_policy::block_retry,nullptr,std::chrono::seconds(1));

        if (isLoggingEnabled())
        {
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] %v");
            spdlog::set_level(spdlog::level::trace);

            auto lvl = spdlog::level::info;
            m_mainLogger->log(lvl, "Adversity "+Game::gameInstance()->appBuildInfo()->versionNumber().toStdString());
            m_mainLogger->log(lvl, "");
        }

        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] (%l) %n: %v");

        switch (Game::gameInstance()->settings().logsAmount())
        {
        case Settings::LA_All:
            spdlog::set_level(spdlog::level::trace);
            break;
        case Settings::LA_Most:
            spdlog::set_level(spdlog::level::info);
            break;
        case Settings::LA_Some:
            spdlog::set_level(spdlog::level::warn);
            break;
        default:
            spdlog::set_level(spdlog::level::off);
            break;
        }
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        qCritical() << "Loggers initialization failed: " << ex.what();
    }
    catch (...)
    {
        abort();
    }
}

LoggersHandler::~LoggersHandler() noexcept
{
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] %v");
    spdlog::set_level(spdlog::level::trace);
    m_mainLogger->info("Closing");
}

void LoggersHandler::setLevel(spdlog::level::level_enum lvl) noexcept
{
    m_mainLogger->set_level(lvl);
    m_xmlLogger->set_level(lvl);
    m_qmlLogger->set_level(lvl);
}

void LoggersHandler::trace(const QString &msg) noexcept
{
    m_qmlLogger->trace(msg.toStdString());
}

void LoggersHandler::debug(const QString &msg) noexcept
{
    m_qmlLogger->debug(msg.toStdString());
}

void LoggersHandler::info(const QString &msg) noexcept
{
    m_qmlLogger->info(msg.toStdString());
}

void LoggersHandler::warn(const QString &msg) noexcept
{
    m_qmlLogger->warn(msg.toStdString());
}

void LoggersHandler::error(const QString &msg) noexcept
{
    m_qmlLogger->error(msg.toStdString());
}

void LoggersHandler::critical(const QString &msg) noexcept
{
    m_qmlLogger->critical(msg.toStdString());
}

void LoggersHandler::traceIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->trace_if(cond, msg.toStdString());
}

void LoggersHandler::debugIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->debug_if(cond, msg.toStdString());
}

void LoggersHandler::infoIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->info_if(cond, msg.toStdString());
}

void LoggersHandler::warnIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->warn_if(cond, msg.toStdString());
}

void LoggersHandler::errorIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->error_if(cond, msg.toStdString());
}

void LoggersHandler::criticalIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->critical_if(cond, msg.toStdString());
}

void LoggersHandler::redirectQtMsgs(QtMsgType type, const QMessageLogContext &, const QString &msg) noexcept
{
    switch (type) {
    case QtDebugMsg:
        Game::gameInstance()->loggers()->qtLogger()->log(spdlog::level::debug, msg.toStdString());
        break;
    case QtInfoMsg:
        Game::gameInstance()->loggers()->qtLogger()->log(spdlog::level::info, msg.toStdString());
        break;
    case QtWarningMsg:
        Game::gameInstance()->loggers()->qtLogger()->log(spdlog::level::warn, msg.toStdString());
        break;
    case QtCriticalMsg:
        Game::gameInstance()->loggers()->qtLogger()->log(spdlog::level::critical, msg.toStdString());
        break;
    case QtFatalMsg:
        abort();
    }
}

bool LoggersHandler::isLoggingEnabled() const noexcept
{
    return Game::gameInstance()->settings().logsAmount() != Settings::LA_None;
}

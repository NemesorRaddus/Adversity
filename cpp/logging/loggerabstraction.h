#pragma once

#include "libs/spdlog-0.14.0/logger.h"

class LoggerAbstraction
{
public:
    explicit LoggerAbstraction(spdlog::logger * const realLogger) noexcept;
    ~LoggerAbstraction() noexcept = default;

    template <typename Arg1, typename... Args>
    void trace(const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->trace(fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void debug(const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->debug(fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void info(const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->info(fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void warn(const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->warn(fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void error(const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->error(fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void critical(const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->critical(fmt, arg1, args...);
    }

    template <typename Arg1, typename... Args>
    void trace_if(const bool flag, const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->trace_if(flag, fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void debug_if(const bool flag, const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->debug_if(flag, fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void info_if(const bool flag, const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->info_if(flag, fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void warn_if(const bool flag, const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->warn_if(flag, fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void error_if(const bool flag, const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->error_if(flag, fmt, arg1, args...);
    }
    template <typename Arg1, typename... Args>
    void critical_if(const bool flag, const char* fmt, const Arg1 &arg1, const Args &... args)
    {
        m_realLogger->critical_if(flag, fmt, arg1, args...);
    }

    template <typename T>
    void trace(const T &msg)
    {
        m_realLogger->trace(msg);
    }
    template <typename T>
    void debug(const T &msg)
    {
        m_realLogger->debug(msg);
    }
    template <typename T>
    void info(const T &msg)
    {
        m_realLogger->info(msg);
    }
    template <typename T>
    void warn(const T &msg)
    {
        m_realLogger->warn(msg);
    }
    template <typename T>
    void error(const T &msg)
    {
        m_realLogger->error(msg);
    }
    template <typename T>
    void critical(const T &msg)
    {
        m_realLogger->critical(msg);
    }

    template <typename T>
    void trace_if(const bool flag, const T &msg)
    {
        m_realLogger->trace_if(flag, msg);
    }
    template <typename T>
    void debug_if(const bool flag, const T &msg)
    {
        m_realLogger->debug_if(flag, msg);
    }
    template <typename T>
    void info_if(const bool flag, const T &msg)
    {
        m_realLogger->info_if(flag, msg);
    }
    template <typename T>
    void warn_if(const bool flag, const T &msg)
    {
        m_realLogger->warn_if(flag, msg);
    }
    template <typename T>
    void error_if(const bool flag, const T &msg)
    {
        m_realLogger->error_if(flag, msg);
    }
    template <typename T>
    void critical_if(const bool flag, const T &msg)
    {
        m_realLogger->critical_if(flag, msg);
    }

private:
    spdlog::logger * const m_realLogger;
};

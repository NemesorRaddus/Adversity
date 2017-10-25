#pragma once

#include <QString>

#include "enums.h"
#include "clock/time.h"

class Report
{
public:
    virtual ~Report() noexcept = default;

    inline ReportEnums::Type type() const noexcept
    {
        return m_reportType;
    }

    virtual QString art() const noexcept = 0;
    virtual QString text() const noexcept = 0;
    inline Time time() const noexcept
    {
        return m_time;
    }

protected:
    explicit Report(ReportEnums::Type type, const Time &time) noexcept;

private:
    ReportEnums::Type m_reportType;
    Time m_time;
};

class NullReport final : public Report
{
public:
    NullReport(const Time &time = {}) noexcept
        : Report(ReportEnums::T_Null, time) {}

    inline QString art() const noexcept final
    {
        return "";
    }
    inline QString text() const noexcept final
    {
        return "";
    }
};

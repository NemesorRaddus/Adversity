#include "report.h"

Report::Report(ReportEnums::Type type, const Time &time) noexcept
    : m_reportType(type), m_time(time) {}

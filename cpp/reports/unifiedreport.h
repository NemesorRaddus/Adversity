#pragma once

#include <QObject>

#include "report.h"

struct UnifiedReportDataHelper
{
    unsigned id;
    Time time;
    QString msg;
    QString art;
};

class UnifiedReport : public QObject
{
    Q_OBJECT

public:
    UnifiedReport(const Time &time, const QString &msg, const QString &artSource = {}) noexcept;
    UnifiedReport(Report *sourceToDestroy) noexcept;
    UnifiedReport(const UnifiedReportDataHelper &data) noexcept;

    operator UnifiedReportDataHelper() const noexcept;

    inline unsigned id() const noexcept
    {
        return m_id;
    }
    Q_INVOKABLE QString timestamp() const noexcept;
    Q_INVOKABLE inline QString msg() const noexcept
    {
        return m_msg;
    }
    Q_INVOKABLE inline QString artSource() const noexcept
    {
        return m_art;
    }

    inline Time time() const noexcept
    {
        return m_time;
    }

private:
    static unsigned m_currentID;
    unsigned m_id;
    Time m_time;
    QString m_msg;
    QString m_art;
};

QDataStream &operator<<(QDataStream &stream, const UnifiedReportDataHelper &report) noexcept;
QDataStream &operator>>(QDataStream &stream, UnifiedReportDataHelper &report) noexcept;

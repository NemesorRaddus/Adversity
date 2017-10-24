#include "unifiedreport.h"

#include <QDataStream>

unsigned UnifiedReport::m_currentID = 0;

UnifiedReport::UnifiedReport(const Time &time, const QString &msg, const QString &artSource) noexcept
    : m_id(m_currentID++), m_time(time), m_msg(msg), m_art(artSource) {}

UnifiedReport::UnifiedReport(Report *sourceToDestroy) noexcept
{
    m_id=m_currentID++;
    m_time=sourceToDestroy->time();
    m_art=sourceToDestroy->art();
    m_msg=sourceToDestroy->text();

    delete sourceToDestroy;
}

UnifiedReport::UnifiedReport(const UnifiedReportDataHelper &data) noexcept
    : m_id(m_currentID++), m_time(data.time), m_msg(data.msg), m_art(data.art) {}

UnifiedReport::operator UnifiedReportDataHelper() const noexcept
{
    return {m_id, m_time, m_msg, m_art};
}

QString UnifiedReport::timestamp() const noexcept
{
    QString r;
    r+=static_cast<unsigned>(m_time.h)<10 ? "0"+QString::number(m_time.h) : QString::number(m_time.h);
    r+=":";
    r+=static_cast<unsigned>(m_time.min)<10 ? "0"+QString::number(m_time.min) : QString::number(m_time.min);
    r+=" Day ";
    r+=QString::number(m_time.d);
    return r;
}

QDataStream &operator<<(QDataStream &stream, const UnifiedReportDataHelper &report) noexcept
{
    stream<<static_cast<quint32>(report.id);
    stream<<report.time;
    stream<<report.msg;
    stream<<report.art;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, UnifiedReportDataHelper &report) noexcept
{
    quint32 uuu;
    stream>>uuu;
    report.id=uuu;
    stream>>report.time;
    stream>>report.msg;
    stream>>report.art;

    return stream;
}

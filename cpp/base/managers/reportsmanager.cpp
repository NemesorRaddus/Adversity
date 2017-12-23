#include "reportsmanager.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "general/game.h"
#include "logging/loggersprovider.h"
#include "missions/mission.h"
#include "reports/basereports.h"
#include "reports/missionreports.h"
#include "reports/unifiedreport.h"

ReportsManager::ReportsManager(Base *base) noexcept
    : BaseManagerInterface(base) {}

void ReportsManager::initializeForNewBase() noexcept {}

void ReportsManager::prepareReport(unsigned index) noexcept
{
    if (index<m_reports.size())
        m_preparedReport=m_reports[index];
}

void ReportsManager::prepareNewReport(unsigned index) noexcept
{
    if (index<m_newReports.size())
        m_preparedReport=m_newReports[index];
}

void ReportsManager::addReport(UnifiedReport *report) noexcept
{
    m_reports+=report;
    if (m_reports.size()>m_maxReportsAmount)
    {
        delete m_reports.first();
        m_reports.removeFirst();
    }
    m_newReports+=report;
    if (m_newReports.size()>m_maxReportsAmount)
        m_newReports.removeFirst();
    base()->gameObject()->showReportNotification();
    LoggersProvider::mainLogger()->trace("[{}] Received a new report: {}",base()->gameClock()->currentTime().toQString().toStdString(), report->msg().toStdString());
}

void ReportsManager::registerLatestReportInMission(Mission *mission) noexcept
{
    if (m_reports.isEmpty() || mission==nullptr)
        return;

    mission->addRelatedReport(m_reports.last());
}

void ReportsManager::markAllAsRead() noexcept
{
    m_newReports.clear();
}

void ReportsManager::removeReport(unsigned index) noexcept
{
    if (index<m_reports.size())
    {
        delete m_reports[index];
        m_reports.remove(index);
    }
}

void ReportsManager::clearReports() noexcept
{
    m_newReports.clear();
    for (auto &e : m_reports)
        delete e;
    m_reports.clear();
}

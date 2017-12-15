#pragma once

#include <QObject>

#include "basemanagerinterface.h"

class Mission;
class UnifiedReport;

class ReportsManager : public QObject, public BaseManagerInterface
{
    Q_OBJECT

    Q_PROPERTY(UnifiedReport* preparedReport MEMBER m_preparedReport)

    friend class H4X;
    friend class Base;

public:
    explicit ReportsManager(Base * base) noexcept;
    ~ReportsManager() noexcept = default;

    void initializeForNewBase() noexcept final;

    Q_INVOKABLE inline unsigned amountOfReports() const noexcept
    {
        return m_reports.size();
    }
    Q_INVOKABLE inline unsigned amountOfNewReports() const noexcept
    {
        return m_newReports.size();
    }
    Q_INVOKABLE void prepareReport(unsigned index) noexcept;
    Q_INVOKABLE void prepareNewReport(unsigned index) noexcept;//not used in QML
    void addReport(UnifiedReport *report) noexcept;
    void registerLatestReportInMission(Mission *mission) noexcept;
    inline QVector <UnifiedReport *> &reports() noexcept
    {
        return m_reports;
    }
    Q_INVOKABLE void markAllAsRead() noexcept;
    Q_INVOKABLE void removeReport(unsigned index) noexcept;//not used in QML
    Q_INVOKABLE void clearReports() noexcept;//not used in QML

private:
    QVector <UnifiedReport *> m_reports;
    const unsigned m_maxReportsAmount = 50;
    QVector <UnifiedReport *> m_newReports;
    UnifiedReport *m_preparedReport;
};

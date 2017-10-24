#pragma once

#include <QVector>

#include "report.h"

typedef QString EventReport;

class EncounterReport final : public Report
{
public:
    EncounterReport(const QString &mercenaryArt, const QVector <EventReport> &events, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QVector <EventReport> m_events;
};

class SignalLostReport final : public Report
{
public:
    SignalLostReport(const QString &mercenaryArt, const QString &mercenaryName, const QString &landName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_mercenaryName;
    QString m_landName;
};

class SignalRetrievedReport final : public Report
{
public:
    SignalRetrievedReport(const QString &mercenaryArt, const QString &landName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_landName;
};

class MissionEndReport final : public Report
{
public:
    MissionEndReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class MissionStartReport final : public Report
{
public:
    MissionStartReport(const QString &mercenaryArt, int stress, int stressLimit, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    int m_stress, m_stressLimit;
};

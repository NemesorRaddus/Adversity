#pragma once

#include "report.h"

class DesertionReport final : public Report
{
public:
    DesertionReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class HungerReport final : public Report
{
public:
    HungerReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class NoSalaryReport final : public Report
{
public:
    NoSalaryReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class MercenaryDeathReport final : public Report
{
public:
    MercenaryDeathReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_mercenaryName;
};

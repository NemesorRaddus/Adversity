#include "mercenaryreports.h"

#include "general/game.h"

DesertionReport::DesertionReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(ReportEnums::T_Desertion, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString DesertionReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" is missing! The room in barracks is empty and one of the shuttles in the docking station disappeared!";
}

HungerReport::HungerReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(ReportEnums::T_Hunger, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString HungerReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" hasn't got daily food ration!";
}

NoSalaryReport::NoSalaryReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(ReportEnums::T_NoSalary, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString NoSalaryReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" hadn't been paid this week.";
}

MercenaryDeathReport::MercenaryDeathReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept
    : Report(ReportEnums::T_MercenaryDeath, time), m_mercenaryArt(mercenaryArt), m_mercenaryName(mercenaryName) {}

QString MercenaryDeathReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_mercenaryName)+" has passed away.";
}

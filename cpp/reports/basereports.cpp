#include "basereports.h"

#include "general/game.h"
#include "general/globalutilities.h"

BuildingUpgradeReport::BuildingUpgradeReport(BuildingEnums::Building building, unsigned level, const Time &time) noexcept
    : Report(ReportEnums::T_BuildingUpgrade, time),
      m_buildingArt("qrc:/graphics/Buildings/"+GlobalUtilities::alterNormalTextToInternal(BuildingEnums::fromBuildingEnumToQString(building))+".png"),
      m_building(building), m_level(level) {}

QString BuildingUpgradeReport::text() const noexcept
{
    return BuildingEnums::fromBuildingEnumToQString(m_building)+" has been upgraded to level "+QString::number(m_level)+".";
}

MercenaryArrivalReport::MercenaryArrivalReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept
    : Report(ReportEnums::T_MercenaryArrival, time), m_mercenaryArt(mercenaryArt), m_name(mercenaryName) {}

QString MercenaryArrivalReport::text() const noexcept
{
    return "Recently hired mercenary, "+Game::gameInstance()->tr(m_name)+" has arrived.";
}

TradeCompletionReport::TradeCompletionReport(BaseEnums::Resource targetResource, unsigned amount, const Time &time) noexcept
    : Report(ReportEnums::T_TradeCompletion, time), m_targetResource(targetResource), m_amount(amount) {}

QString TradeCompletionReport::text() const noexcept
{
    return "We received that "+QString::number(m_amount)+" units of "+BaseEnums::fromResourceEnumToQString(m_targetResource)+" you ordered recently.";
}

EquipmentArrivalReport::EquipmentArrivalReport(const QString &name, const Time &time) noexcept
    : Report(ReportEnums::T_EquipmentArrival, time), m_name(name) {}

QString EquipmentArrivalReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" has been delivered and is now stored in storage room.";
}

TrainingCompletionReport::TrainingCompletionReport(const QString &mercenaryArt, const QString &mercenaryName, BuildingEnums::Building building, const Time &time) noexcept
    : Report(ReportEnums::T_MissionEnd, time), m_mercenaryArt(mercenaryArt), m_mercenaryName(mercenaryName), m_building(building) {}

QString TrainingCompletionReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_mercenaryName)+" has finished training in "+BuildingEnums::fromBuildingEnumToQString(m_building)+".";
}

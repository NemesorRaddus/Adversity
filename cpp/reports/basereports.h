#pragma once

#include "report.h"
#include "base/buildings/enums.h"
#include "base/enums.h"

class BuildingUpgradeReport final : public Report
{
public:
    BuildingUpgradeReport(BuildingEnums::Building building, unsigned level, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_buildingArt;
    }
    QString text() const noexcept final;

private:
    QString m_buildingArt;
    BuildingEnums::Building m_building;
    unsigned m_level;
};

class MercenaryArrivalReport final : public Report
{
public:
    MercenaryArrivalReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class TradeCompletionReport final : public Report
{
public:
    TradeCompletionReport(BaseEnums::Resource targetResource, unsigned amount, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return "qrc:/graphics/Buildings/DockingStation.png";
    }
    QString text() const noexcept final;

private:
    BaseEnums::Resource m_targetResource;
    unsigned m_amount;
};

class EquipmentArrivalReport final : public Report
{
public:
    EquipmentArrivalReport(const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return "qrc:/graphics/Buildings/DockingStation.png";
    }
    QString text() const noexcept final;

private:
    QString m_name;
};

class TrainingCompletionReport final : public Report
{
public:
    TrainingCompletionReport(const QString &mercenaryArt, const QString &mercenaryName, BuildingEnums::Building building, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_mercenaryName;
    BuildingEnums::Building m_building;
};

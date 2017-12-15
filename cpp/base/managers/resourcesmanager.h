#pragma once

#include <QObject>

#include "base/buildings/enums.h"
#include "basemanagerinterface.h"

class ResourcesManager : public QObject, public BaseManagerInterface
{
    Q_OBJECT

    friend class H4X;
    friend class Base;

public:
    explicit ResourcesManager(Base * base) noexcept;
    ~ResourcesManager() noexcept = default;

    void initializeForNewBase() noexcept final;

    Q_INVOKABLE inline int currentEnergyAmount() const noexcept
    {
        return m_energy;
    }
    Q_INVOKABLE inline int currentFoodSuppliesAmount() const noexcept
    {
        return m_foodSupplies;
    }
    Q_INVOKABLE inline int currentBuildingMaterialsAmount() const noexcept
    {
        return m_buildingMaterials;
    }
    Q_INVOKABLE inline int currentAetheriteAmount() const noexcept
    {
        return m_aetherite;
    }

    Q_INVOKABLE int currentTotalSalary() const noexcept;

    void setCurrentEnergyAmount(unsigned amount) noexcept;
    void setCurrentFoodSuppliesAmount(unsigned amount) noexcept;
    void setCurrentBuildingMaterialsAmount(unsigned amount) noexcept;
    void setCurrentAetheriteAmount(unsigned amount) noexcept;

    inline bool canDecreaseEnergyAmount(unsigned amount) const noexcept
    {
        return m_energy>=amount;
    }
    inline bool canDecreaseFoodSuppliesAmount(unsigned amount) const noexcept
    {
        return m_foodSupplies>=amount;
    }
    inline bool canDecreaseBuildingMaterialsAmount(unsigned amount) const noexcept
    {
        return m_buildingMaterials>=amount;
    }
    inline bool canDecreaseAetheriteAmount(unsigned amount) const noexcept
    {
        return m_aetherite>=amount;
    }

    void decreaseEnergyAmount(unsigned amount) noexcept;
    void decreaseFoodSuppliesAmount(unsigned amount) noexcept;
    void decreaseBuildingMaterialsAmount(unsigned amount) noexcept;
    void decreaseAetheriteAmount(unsigned amount) noexcept;

    void increaseEnergyAmount(unsigned amount) noexcept;
    void increaseFoodSuppliesAmount(unsigned amount) noexcept;
    void increaseBuildingMaterialsAmount(unsigned amount) noexcept;
    void increaseAetheriteAmount(unsigned amount) noexcept;

    Q_INVOKABLE int currentEnergyIncome() const noexcept;
    Q_INVOKABLE int currentFoodSuppliesIncome() const noexcept;
    Q_INVOKABLE int currentBuildingMaterialsIncome() const noexcept;
    Q_INVOKABLE int currentAetheriteIncome() const noexcept;

    Q_INVOKABLE int currentEnergyLimit() noexcept;
    Q_INVOKABLE int currentFoodSuppliesLimit() noexcept;
    Q_INVOKABLE int currentBuildingMaterialsLimit() noexcept;
    Q_INVOKABLE int currentAetheriteLimit() noexcept;

private:
    unsigned m_energy;
    unsigned m_foodSupplies;
    unsigned m_buildingMaterials;
    unsigned m_aetherite;
};

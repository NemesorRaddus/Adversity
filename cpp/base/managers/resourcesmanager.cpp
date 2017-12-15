#include "resourcesmanager.h"

#include "base/base.h"
#include "base/buildings/specific/production/powerplant.h"
#include "base/buildings/specific/storage/aetheritesilo.h"
#include "base/buildings/specific/storage/coolroom.h"
#include "base/buildings/specific/storage/storageroom.h"
#include "base/managers/buildingsmanager.h"
#include "base/managers/mercenariesmanager.h"
#include "mercenaries/enums.h"
#include "mercenaries/mercenariescontainer.h"
#include "mercenaries/mercenary.h"

ResourcesManager::ResourcesManager(Base *base) noexcept
    : BaseManagerInterface(base) {}

void ResourcesManager::initializeForNewBase() noexcept
{
    m_energy=250;
    m_foodSupplies=24;
    m_buildingMaterials=5;
    m_aetherite=50;
}

int ResourcesManager::currentTotalSalary() const noexcept
{
    int r=0;
    for (auto e : base()->mercenaries()->mercenaries()->mercenaries())
        if (e->currentActivity() != MercenaryEnums::CA_Arriving)
            r+=e->salary();
    return r;
}

void ResourcesManager::setCurrentEnergyAmount(unsigned amount) noexcept
{
    if (amount <= currentEnergyLimit())
        m_energy = amount;
}

void ResourcesManager::setCurrentFoodSuppliesAmount(unsigned amount) noexcept
{
    if (amount <= currentFoodSuppliesLimit())
        m_foodSupplies = amount;
}

void ResourcesManager::setCurrentBuildingMaterialsAmount(unsigned amount) noexcept
{
    if (amount <= currentBuildingMaterialsLimit())
        m_buildingMaterials = amount;
}

void ResourcesManager::setCurrentAetheriteAmount(unsigned amount) noexcept
{
    if (amount <= currentAetheriteLimit())
        m_aetherite = amount;
}

void ResourcesManager::decreaseEnergyAmount(unsigned amount) noexcept
{
    m_energy = m_energy>amount ? m_energy-amount : 0;
}

void ResourcesManager::decreaseFoodSuppliesAmount(unsigned amount) noexcept
{
    m_foodSupplies = m_foodSupplies>amount ? m_foodSupplies-amount : 0;
}

void ResourcesManager::decreaseBuildingMaterialsAmount(unsigned amount) noexcept
{
    m_buildingMaterials = m_buildingMaterials>amount ? m_buildingMaterials-amount : 0;
}

void ResourcesManager::decreaseAetheriteAmount(unsigned amount) noexcept
{
    m_aetherite = m_aetherite>amount ? m_aetherite-amount : 0;
}

void ResourcesManager::increaseEnergyAmount(unsigned amount) noexcept
{
    m_energy = m_energy+amount<currentEnergyLimit() ? m_energy+amount : currentEnergyLimit();
}

void ResourcesManager::increaseFoodSuppliesAmount(unsigned amount) noexcept
{
    m_foodSupplies = m_foodSupplies+amount<currentFoodSuppliesLimit() ? m_foodSupplies+amount : currentFoodSuppliesLimit();
}

void ResourcesManager::increaseBuildingMaterialsAmount(unsigned amount) noexcept
{
    m_buildingMaterials = m_buildingMaterials+amount<currentBuildingMaterialsLimit() ? m_buildingMaterials+amount : currentBuildingMaterialsLimit();
}

void ResourcesManager::increaseAetheriteAmount(unsigned amount) noexcept
{
    m_aetherite = m_aetherite+amount<currentAetheriteLimit() ? m_aetherite+amount : currentAetheriteLimit();
}

int ResourcesManager::currentEnergyIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=base()->buildings()->getBuilding(static_cast<BuildingEnums::Building>(i))->currentCostInEnergy();
    return r;
}

int ResourcesManager::currentFoodSuppliesIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=base()->buildings()->getBuilding(static_cast<BuildingEnums::Building>(i))->currentCostInFoodSupplies();
    for (auto e : base()->mercenaries()->mercenaries()->mercenaries())
        r-=e->dailyFoodConsumption();
    return r;
}

int ResourcesManager::currentBuildingMaterialsIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=base()->buildings()->getBuilding(static_cast<BuildingEnums::Building>(i))->currentCostInBuildingMaterials();
    return r;
}

int ResourcesManager::currentAetheriteIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=base()->buildings()->getBuilding(static_cast<BuildingEnums::Building>(i))->currentCostInAetherite();
    return r;
}

int ResourcesManager::currentEnergyLimit() noexcept
{
    return base()->buildings()->powerplant()->energyLimit();
}

int ResourcesManager::currentFoodSuppliesLimit() noexcept
{
    return base()->buildings()->coolRoom()->foodSuppliesLimit();
}

int ResourcesManager::currentBuildingMaterialsLimit() noexcept
{
    return base()->buildings()->storageRoom()->buildingMaterialsLimit();
}

int ResourcesManager::currentAetheriteLimit() noexcept
{
    return base()->buildings()->aetheriteSilo()->aetheriteLimit();
}

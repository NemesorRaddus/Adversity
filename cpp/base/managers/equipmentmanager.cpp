#include "equipmentmanager.h"

#include "base/base.h"
#include "equipment/equipment.h"

EquipmentManager::EquipmentManager(Base *base) noexcept
    : BaseManagerInterface(base) {}

void EquipmentManager::initializeForNewBase() noexcept {}

unsigned EquipmentManager::amountOfAvailableArmors() const noexcept
{
    unsigned r=0;
    for (auto e : m_availableEquipment)
        if (e->type() == EquipmentEnums::T_Armor)
            ++r;
    return r;
}

unsigned EquipmentManager::amountOfAvailableWeaponsTools() const noexcept
{
    unsigned r=0;
    for (auto e : m_availableEquipment)
        if (e->type() == EquipmentEnums::T_WeaponTool)
            ++r;
    return r;
}

void EquipmentManager::prepareAvailableEquipment(unsigned index) noexcept
{
    if (index<m_availableEquipment.size())
        m_preparedAvailableEquipment=m_availableEquipment[index];
}

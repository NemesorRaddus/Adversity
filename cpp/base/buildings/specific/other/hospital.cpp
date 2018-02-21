#include "hospital.h"

#include "base/base.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenariescontainer.h"

Hospital::Hospital(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Hospital, base, level, levelsInfo)
{
    m_mercenariesBeingHealed.fill(nullptr, currentLevelInfo()->amountOfSlots);
}

int Hospital::useCostInEnergy() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy * (m_mercenariesBeingHealed.size() - m_mercenariesBeingHealed.count(nullptr));
}

int Hospital::useCostInEnergySingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy;
}

int Hospital::useCostInEnergySingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInEnergy;
}

int Hospital::basicCostInFoodSupplies() const noexcept
{
    return currentLevelInfo()->basicCostInFoodSupplies;
}

int Hospital::useCostInFoodSupplies() const noexcept
{
    return currentLevelInfo()->perCapitaCostInFoodSupplies * (m_mercenariesBeingHealed.size() - m_mercenariesBeingHealed.count(nullptr));
}

int Hospital::useCostInFoodSuppliesSingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInFoodSupplies;
}

int Hospital::useCostInFoodSuppliesSingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInFoodSupplies;
}

int Hospital::amountOfSlots() const noexcept
{
    return m_mercenariesBeingHealed.size();
}

int Hospital::amountOfSlotsAfterUpgrade() const noexcept
{
    return nextLevelInfo()->amountOfSlots;
}

Mercenary *Hospital::slot(int index) noexcept
{
    return m_mercenariesBeingHealed.value(index,nullptr);
}

QString Hospital::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingHealed.size() && m_mercenariesBeingHealed[index]!=nullptr)
        return m_mercenariesBeingHealed[index]->name();
    return "";
}

QString Hospital::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingHealed.size() && m_mercenariesBeingHealed[index]!=nullptr)
        return m_mercenariesBeingHealed[index]->professionString();
    return "";
}

void Hospital::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
{
    if (slotIndex >= m_mercenariesBeingHealed.size())
        return;

    if (m_mercenariesBeingHealed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingHealed[slotIndex]=base()->mercenaries()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingHealed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_InHospital);
    setRecoveryValuesForMercenary(slotIndex);
}

void Hospital::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex >= m_mercenariesBeingHealed.size())
        return;

    if (m_mercenariesBeingHealed[slotIndex]==nullptr)
        return;

    m_mercenariesBeingHealed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingHealed[slotIndex]->setDailyHealthRecoveryBuildingBonus(0);
    m_mercenariesBeingHealed[slotIndex]=nullptr;
}

void Hospital::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i < m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr && m_mercenariesBeingHealed[i]->name() == name)
        {
            m_mercenariesBeingHealed[i]->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingHealed[i]=nullptr;
            break;
        }
}

int Hospital::hpRestoredPerDay() const noexcept
{
    return currentLevelInfo()->hpRestored;
}

int Hospital::hpRestoredPerDayAfterUpgrade() const noexcept
{
    return nextLevelInfo()->hpRestored;
}

int Hospital::daysToFullRecovery(const QString &name) const noexcept
{
    for (int i=0;i < m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr && m_mercenariesBeingHealed[i]->name() == name)
            return daysToFullRecovery(i);
}

int Hospital::daysToFullRecovery(unsigned slotIndex) const noexcept
{
    if (slotIndex < m_mercenariesBeingHealed.size())
    {
        if (m_mercenariesBeingHealed[slotIndex]==nullptr)
            return -1;

        return ceil(static_cast<float>(m_mercenariesBeingHealed[slotIndex]->healthLimit()-m_mercenariesBeingHealed[slotIndex]->health())/static_cast<float>(hpRestoredPerDay()));
    }
}

void Hospital::healMercenaries() noexcept
{
    for (int i=0;i < m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr && base()->resources()->canDecreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy) && base()->resources()->canDecreaseFoodSuppliesAmount(currentLevelInfo()->perCapitaCostInFoodSupplies))
        {
            base()->resources()->decreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy);
            base()->resources()->decreaseFoodSuppliesAmount(currentLevelInfo()->perCapitaCostInFoodSupplies);

            m_mercenariesBeingHealed[i]->changeHealth(currentLevelInfo()->hpRestored);
        }
}

void Hospital::setRecoveryValuesForMercenary(unsigned index) noexcept
{
    m_mercenariesBeingHealed[index]->setDailyHealthRecoveryBuildingBonus(hpRestoredPerDay());
}

void Hospital::setRecoveryValuesForMercenaries() noexcept
{
    for (int i=0;i < m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr)
            setRecoveryValuesForMercenary(i);
}

void Hospital::setLevelsInfo(const QVector < HospitalLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Hospital::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Hospital,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Hospital::registerUpgradeCompletion() noexcept
{
    m_isBeingUpgraded = 0;
    resizeSlotsAfterUpgrade();
}

void Hospital::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingHealed.size() < currentLevelInfo()->amountOfSlots)
        m_mercenariesBeingHealed.push_back(nullptr);
    m_mercenariesBeingHealed.resize(currentLevelInfo()->amountOfSlots);//for downgrades
    setRecoveryValuesForMercenaries();
}

HospitalLevelInfo *Hospital::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<HospitalLevelInfo > ();
}

HospitalLevelInfo *Hospital::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<HospitalLevelInfo > ();
}

void Hospital::setSlot(unsigned index, Mercenary *mercenary) noexcept
{
    if (index < m_mercenariesBeingHealed.size())
        m_mercenariesBeingHealed[index]=mercenary;
}

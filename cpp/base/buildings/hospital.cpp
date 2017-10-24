#include "hospital.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

Hospital::Hospital(Base *base, unsigned level, const QVector<HospitalLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_Hospital, base, level), m_levelsInfo(levelsInfo)
{
    m_mercenariesBeingHealed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
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
    if (slotIndex>=m_mercenariesBeingHealed.size())
        return;

    if (m_mercenariesBeingHealed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingHealed[slotIndex]=base()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingHealed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_InHospital);
    setRecoveryValuesForMercenary(slotIndex);
}

void Hospital::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingHealed.size())
        return;

    if (m_mercenariesBeingHealed[slotIndex]==nullptr)
        return;

    m_mercenariesBeingHealed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingHealed[slotIndex]->setDailyHealthRecoveryBuildingBonus(0);
    m_mercenariesBeingHealed[slotIndex]=nullptr;
}

void Hospital::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr && m_mercenariesBeingHealed[i]->name() == name)
        {
            m_mercenariesBeingHealed[i]->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingHealed[i]=nullptr;
            break;
        }
}

int Hospital::daysToFullRecovery(const QString &name) const noexcept
{
    for (int i=0;i<m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr && m_mercenariesBeingHealed[i]->name()==name)
            return daysToFullRecovery(i);
}

int Hospital::daysToFullRecovery(unsigned slotIndex) const noexcept
{
    if (slotIndex<m_mercenariesBeingHealed.size())
    {
        if (m_mercenariesBeingHealed[slotIndex]==nullptr)
            return -1;

        return ceil(static_cast<float>(m_mercenariesBeingHealed[slotIndex]->healthLimit()-m_mercenariesBeingHealed[slotIndex]->health())/static_cast<float>(hpRestoredPerDay()));
    }
}

void Hospital::healMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy) && base()->canDecreaseFoodSuppliesAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);
            base()->decreaseFoodSuppliesAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies);

            m_mercenariesBeingHealed[i]->changeHealth(m_levelsInfo.value(currentLevel()).hpRestored);
        }
}

void Hospital::setRecoveryValuesForMercenary(unsigned index) noexcept
{
    m_mercenariesBeingHealed[index]->setDailyHealthRecoveryBuildingBonus(hpRestoredPerDay());
}

void Hospital::setRecoveryValuesForMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingHealed.size();++i)
        if (m_mercenariesBeingHealed[i]!=nullptr)
            setRecoveryValuesForMercenary(i);
}

void Hospital::setLevelsInfo(const QVector<HospitalLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Hospital::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Hospital,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Hospital::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingHealed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_mercenariesBeingHealed.push_back(nullptr);
    m_mercenariesBeingHealed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForMercenaries();
}

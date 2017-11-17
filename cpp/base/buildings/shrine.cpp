#include "shrine.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenariescontainer.h"

Shrine::Shrine(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Shrine, base, level, levelsInfo)
{
    m_mercenariesBeingDestressed.fill(nullptr, currentLevelInfo()->amountOfSlots);
}

int Shrine::useCostInEnergy() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy * (m_mercenariesBeingDestressed.size() - m_mercenariesBeingDestressed.count(nullptr));
}

int Shrine::useCostInEnergySingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy;
}

int Shrine::useCostInEnergySingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInEnergy;
}

int Shrine::amountOfSlots() const noexcept
{
    return m_mercenariesBeingDestressed.size();
}

int Shrine::amountOfSlotsAfterUpgrade() const noexcept
{
    return nextLevelInfo()->amountOfSlots;
}

Mercenary *Shrine::slot(int index) noexcept
{
    return m_mercenariesBeingDestressed.value(index,nullptr);
}

QString Shrine::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->name();
    return "";
}

QString Shrine::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->professionString();
    return "";
}

void Shrine::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingDestressed[slotIndex]=base()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_InShrine);
    setRecoveryValuesForMercenary(slotIndex);
}

void Shrine::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]==nullptr)
        return;

    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_mercenariesBeingDestressed[slotIndex]=nullptr;
}

void Shrine::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && m_mercenariesBeingDestressed[i]->name() == name)
        {
            m_mercenariesBeingDestressed[i]->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingDestressed[i]=nullptr;
            break;
        }
}

int Shrine::activeStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForActive;
}

int Shrine::activeStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForActive;
}

int Shrine::convivialStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForConvivial;
}

int Shrine::convivialStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForConvivial;
}

int Shrine::recluseStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForRecluse;
}

int Shrine::recluseStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForRecluse;
}

int Shrine::religiousStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForReligious;
}

int Shrine::religiousStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForReligious;
}

void Shrine::destressMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && base()->canDecreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy))
        {
            base()->decreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy);

            if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Active)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForActive);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Convivial)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForConvivial);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Recluse)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForRecluse);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Religious)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForReligious);
        }
}

void Shrine::setRecoveryValuesForMercenary(unsigned index) noexcept
{
    switch (m_mercenariesBeingDestressed[index]->nature())
    {
    case MercenaryEnums::N_Active:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(activeStressRelief());
        break;
    case MercenaryEnums::N_Convivial:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(convivialStressRelief());
        break;
    case MercenaryEnums::N_Recluse:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(recluseStressRelief());
        break;
    case MercenaryEnums::N_Religious:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(religiousStressRelief());
        break;
    }
}

void Shrine::setRecoveryValuesForMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForMercenary(i);
}

void Shrine::setLevelsInfo(const QVector<ShrineLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Shrine::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Shrine,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Shrine::registerUpgradeCompletion() noexcept
{
    m_isBeingUpgraded=0;
    resizeSlotsAfterUpgrade();
}

void Shrine::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingDestressed.size() < currentLevelInfo()->amountOfSlots)
        m_mercenariesBeingDestressed.push_back(nullptr);
    m_mercenariesBeingDestressed.resize(currentLevelInfo()->amountOfSlots);//for downgrades
    setRecoveryValuesForMercenaries();
}

ShrineLevelInfo *Shrine::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<ShrineLevelInfo>();
}

ShrineLevelInfo *Shrine::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<ShrineLevelInfo>();
}

void Shrine::setSlot(unsigned index, Mercenary *mercenary) noexcept
{
    if (index<m_mercenariesBeingDestressed.size())
        m_mercenariesBeingDestressed[index]=mercenary;
}

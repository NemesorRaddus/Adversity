#include "land.h"

#include "general/randomizer.h"
#include "missions/encounter.h"

Land::Land(const LandInfo &info) noexcept
    : m_info(info)
{
    m_encounters = new EncountersContainer;
}

Land::~Land() noexcept
{
    delete m_encounters;
}

Encounter *Land::makeRandomEncounter() const noexcept
{
    if (m_encounters->encounters().isEmpty())
        return nullptr;

    auto r = new Encounter("",nullptr,0);

    unsigned amount = m_encounters->encounters().size();
    unsigned probs[amount];
    probs[0] = m_encounters->encounters()[0]->probability();
    for (int i=1;i < amount;++i)
        probs[i] = probs[i-1] + m_encounters->encounters()[i]->probability();

    unsigned resultProb = Randomizer::randomBetweenAAndB(1, probs[amount-1]);
    unsigned resultEnc = amount-1;
    for (int i=0;i < amount-1;++i)
        if (resultProb <= probs[i])
        {
            resultEnc = i;
            break;
        }
    *r=*(m_encounters->encounters()[resultEnc]);
    return r;
}

void Land::setInfo(const LandInfo &info) noexcept
{
    m_info = info;
}

void Land::setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept
{
    delete m_encounters;
    m_encounters = encCont;
}

LandBuilder::LandBuilder() noexcept
{
    m_land = new Land({});
}

LandBuilder::~LandBuilder() noexcept
{
    delete m_land;
}

Land *LandBuilder::getLand() noexcept
{
    Land *ret = m_land;
    m_land = new Land({});
    return ret;
}

void LandBuilder::resetLand() noexcept
{
    delete m_land;
    m_land = new Land({});
}

void LandBuilder::setInfo(const LandInfo &info) noexcept
{
    m_land->setInfo(info);
}

void LandBuilder::setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept
{
    m_land->setAssociatedEncountersContainer(encCont);
}

LandsInfo::LandsInfo(const QVector < Land *> *lands) noexcept
    : m_lands(lands), m_preparedLand(nullptr) {}

unsigned LandsInfo::amountOfLands() const noexcept
{
    return m_lands->size();
}

void LandsInfo::prepareLandAt(unsigned index) noexcept
{
    if (index < m_lands->size())
        m_preparedLand = (*m_lands)[index];
}

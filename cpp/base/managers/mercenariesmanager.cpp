#include "mercenariesmanager.h"

#include "assets_pool/assetspool.h"
#include "base/base.h"
#include "base/buildings/specific/other/barracks.h"
#include "base/managers/buildingsmanager.h"
#include "general/game.h"
#include "mercenaries/mercenariescontainer.h"

MercenariesManager::MercenariesManager(Base *base) noexcept
    : BaseManagerInterface(base)
{
    m_mercenaries = new MercenariesContainer(base);
}

MercenariesManager::~MercenariesManager() noexcept
{
    delete m_mercenaries;
}

void MercenariesManager::initializeForNewBase() noexcept
{
    m_mercenaries->setAmountOfSlots(base()->buildings()->barracks()->mercenariesLimit());//setting mercenaries limit

    base()->gameObject()->assetsPool().loadMercenaryNamedFromList("HeinzWitt");//creating default mercenaries
    auto loadedH = base()->gameObject()->assetsPool().loadedMercenaries();
    for (auto e : loadedH)
        if (e->name() == "HeinzWitt")
        {
            m_mercenaries->addMercenary(e);
            break;
        }
}

void MercenariesManager::recalculateAmountOfMercenarySlots() const noexcept
{
    m_mercenaries->setAmountOfSlots(base()->buildings()->barracks()->mercenariesLimit());
}

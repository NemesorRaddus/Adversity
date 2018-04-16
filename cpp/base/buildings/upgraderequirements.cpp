#include "upgraderequirements.h"

BuildingsRequirementsHandler::BuildingsRequirementsHandler(const BuildingsRequirementsMap &data) noexcept
    : m_data(data) {}

BuildingUpgradeRequirements BuildingsRequirementsHandler::requirements(BuildingEnums::Building building, unsigned level) const noexcept
{
    return m_data.value({building, level});
}

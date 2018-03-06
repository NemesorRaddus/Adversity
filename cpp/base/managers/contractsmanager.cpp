#include "contractsmanager.h"

ContractsManager::ContractsManager(Base *base) noexcept
	: BaseManagerInterface(base) {}

void ContractsManager::initializeForNewBase() noexcept {}

void ContractsManager::prepareContract(unsigned index) noexcept
{
	if (index < m_contracts.size())
		m_preparedContract = m_contracts[index];
}

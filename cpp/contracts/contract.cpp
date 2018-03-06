#include "contract.h"

bool Contract::isRewardReady() const noexcept
{
	for (const auto &e : m_goals)
		if (!e->hasBeenAchieved())
			return 0;
	return 1;
}

void Contract::decrementExpirationTime() noexcept
{
	--m_expirationTimeInDays;
}

Contract::Contract() noexcept
	: m_expirationTimeInDays(0), m_faction(ContractEnums::F_END), m_factionPoints(0) {}

ContractBuilder::ContractBuilder() noexcept
	: m_contract(new Contract) {}

ContractBuilder::~ContractBuilder() noexcept
{
	delete m_contract;
}

Contract *ContractBuilder::getContract() noexcept
{
	auto t = m_contract;
	m_contract = new Contract;
	return t;
}

void ContractBuilder::setGoals(const QVector<ContractGoal *> &goals) noexcept
{
	m_contract->m_goals = goals;
}

void ContractBuilder::setExpirationTime(unsigned days) noexcept
{
	m_contract->m_expirationTimeInDays = days;
}

void ContractBuilder::setFaction(ContractEnums::Faction faction) noexcept
{
	m_contract->m_faction = faction;
}

void ContractBuilder::setFactionPoints(unsigned amount) noexcept
{
	m_contract->m_factionPoints = amount;
}

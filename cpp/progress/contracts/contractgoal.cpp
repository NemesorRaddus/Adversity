#include "contractgoal.h"

void ContractGoal::decrementExpirationTime() noexcept
{
	--m_expirationTimeInDays;
}

ContractGoal::ContractGoal() noexcept
	: m_expirationTimeInDays(0), m_faction(ContractEnums::F_END), m_factionPoints(0) {}

ContractGoalBuilder::ContractGoalBuilder() noexcept
{
	m_object = new ContractGoal;
}

ContractGoalBuilder::~ContractGoalBuilder() noexcept
{
	delete m_object;
}

ContractGoal *ContractGoalBuilder::getObject() noexcept
{
	ContractGoal *r = object();
	m_object = new ContractGoal;
	return r;
}

void ContractGoalBuilder::setExpirationTime(unsigned days) noexcept
{
	object()->m_expirationTimeInDays = days;
}

void ContractGoalBuilder::setFaction(ContractEnums::Faction faction) noexcept
{
	object()->m_faction = faction;
}

void ContractGoalBuilder::setFactionPoints(unsigned amount) noexcept
{
	object()->m_factionPoints = amount;
}

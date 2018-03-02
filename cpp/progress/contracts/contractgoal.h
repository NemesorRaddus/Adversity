#pragma once

#include "progress/basics/goal.h"

namespace ContractEnums
{
	enum Faction
	{
		F_TR,
		F_UEG,
		F_UPOA,
		F_END
	};
	enum Type
	{
		T_Exploration,
		T_END
	};
}

class ContractGoal : public Goal
{
	friend class ContractGoalBuilder;

public:
	inline unsigned expirationTime() const noexcept
	{
		return m_expirationTimeInDays;
	}
	inline ContractEnums::Faction faction() const noexcept
	{
		return m_faction;
	}
	inline unsigned factionPoints() const noexcept
	{
		return m_faction;
	}

	void decrementExpirationTime() noexcept;

private:
	ContractGoal() noexcept;

	unsigned m_expirationTimeInDays;
	ContractEnums::Faction m_faction;
	unsigned m_factionPoints;
};

class ContractGoalBuilder : public AbstractGoalBuilder
{
public:
	ContractGoalBuilder() noexcept;
	~ContractGoalBuilder() noexcept;

	ContractGoal *getObject() noexcept;

	void setExpirationTime(unsigned days) noexcept;
	void setFaction(ContractEnums::Faction faction) noexcept;
	void setFactionPoints(unsigned amount) noexcept;

private:
	inline ContractGoal *object() noexcept
	{
		return static_cast<ContractGoal *>(m_object);
	}
};

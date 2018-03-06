#pragma once

#include <QString>

#include "basicgoal.h"
#include "enums.h"

class ContractGoal;

class ContractProgress : public BasicProgress
{
public:
	ContractProgress(ContractGoal *context, const rational &progress = {0}) noexcept; // for normal use
	ContractProgress(const rational &progress = {0}) noexcept; // for convertions
	~ContractProgress() noexcept = default;

	BasicProgress &operator =(const rational &value) noexcept;

	void operator +=(const rational &change) noexcept;
	void operator ++() noexcept;
	void operator ++(int) noexcept;

private:
	ContractGoal *context() noexcept;
};

class ContractGoal : public BasicGoal
{
	friend class ContractGoalBuilder;

public:
	~ContractGoal() noexcept = default;

	inline ContractEnums::Type type() const noexcept
	{
		return m_type;
	}

protected:
	ContractGoal() noexcept;

	ContractEnums::Type m_type;
};

class ContractGoalBuilder : public BasicGoalBuilder
{
public:
	ContractGoalBuilder() noexcept;
	~ContractGoalBuilder() noexcept = default;

	void setType(ContractEnums::Type type) noexcept;

private:
	ContractGoal *goal() noexcept;
};

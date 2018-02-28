#pragma once

#include "progress/basics/goal.h"

class ContractGoal : public Goal
{
public:
	ContractGoal();

private:
	unsigned m_expirationTimeInDays;
};

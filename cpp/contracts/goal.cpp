#include "goal.h"

ContractProgress::ContractProgress(ContractGoal *context, const rational &progress) noexcept
	: BasicProgress(context, progress) {}

ContractProgress::ContractProgress(const rational &progress) noexcept
	: BasicProgress(progress) {}

BasicProgress &ContractProgress::operator =(const rational &value) noexcept
{
	// TODO progress
}

void ContractProgress::operator +=(const rational &change) noexcept
{

}

void ContractProgress::operator ++() noexcept
{

}

void ContractProgress::operator ++(int) noexcept
{

}

ContractGoal::ContractGoal() noexcept
	: BasicGoal(new ContractProgress, new ContractProgress), m_type(ContractEnums::T_END) {}

ContractGoalBuilder::ContractGoalBuilder() noexcept
	: BasicGoalBuilder(new ContractGoal) {}

void ContractGoalBuilder::setType(ContractEnums::Type type) noexcept
{
	goal()->m_type = type;
}

ContractGoal *ContractGoalBuilder::goal() noexcept
{
	return static_cast<ContractGoal *>(m_goal);
}

ContractGoal *ContractProgress::context() noexcept
{
	return static_cast<ContractGoal *>(m_context);
}

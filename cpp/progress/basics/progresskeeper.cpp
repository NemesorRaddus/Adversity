#include "progresskeeper.h"

#include "goal.h"

void ProgressKeeper::addGoal(Goal *goal) noexcept
{
	m_goals += goal;
}

Goal *ProgressKeeper::goal(unsigned index) noexcept
{
	if (index < m_goals.size())
		return m_goals[index];
	return nullptr;
}

void ProgressKeeper::importGoals(const QVector<Goal *> &goals) noexcept
{
	m_goals = goals;
}

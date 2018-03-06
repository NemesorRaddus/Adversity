#include "basicgoal.h"

BasicProgress::BasicProgress(BasicGoal *context, const rational &progress) noexcept
	: m_context(context), m_progress(progress) {}

BasicProgress::BasicProgress(const rational &progress) noexcept
	: m_context(nullptr), m_progress(progress) {}

void BasicProgress::clear() noexcept
{
	m_progress = 0;
}

BasicGoal::BasicGoal(BasicProgress *needed, BasicProgress *current) noexcept
	: m_enableProgressAccumulation(true), m_neededProgress(needed), m_currentProgress(current) {}

BasicGoalBuilder::BasicGoalBuilder(BasicGoal *goal) noexcept
	: m_goal(goal)
{
	Q_ASSERT(goal != nullptr);
}

BasicGoalBuilder::~BasicGoalBuilder() noexcept
{
	delete m_goal;
}

#pragma once

#include <QVector>

class Goal;

class ProgressKeeper
{
public:
	void addGoal(Goal *goal) noexcept;
	inline unsigned amountOfGoals() const noexcept
	{
		return m_goals.size();
	}

private:
	QVector <Goal *> m_goals;
};

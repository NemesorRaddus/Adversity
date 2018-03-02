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
	Goal *goal(unsigned index) noexcept;

	inline QVector <Goal *> exportGoals() const noexcept
	{
		return m_goals;
	}
	void importGoals(const QVector <Goal *> &goals) noexcept;

private:
	QVector <Goal *> m_goals;
};

#include "goal.h"

Goal::Progress::Progress(const rational &progress) noexcept
	: m_progress(progress), m_goal(nullptr) {}

Goal::Progress &Goal::Progress::operator =(const rational &value) noexcept
{
	if (m_goal == nullptr)
		return *this;

	if (value < 0 || value > m_goal->m_neededProgress)
		return *this;

	m_progress = value;
	return *this;
}

Goal::Progress &Goal::Progress::operator +=(const rational &change) noexcept
{
	if (m_goal == nullptr)
		return *this;

	if (m_progress + change < 0)
		m_progress = 0;
	else
	{
		if (m_goal->m_enableProgressAccumulation)
		{
			if (m_progress + change > m_goal->m_neededProgress)
				m_progress = m_goal->m_neededProgress;
			else
				m_progress += change;
		}
		else
		{
			if (m_goal->m_neededProgress <= change)
				m_progress = m_goal->m_neededProgress;
			else
				m_progress = change;
		}
	}
	return *this;
}

Goal::Progress Goal::Progress::operator ++() noexcept
{
	*this += 1;
	return *this;
}

Goal::Progress Goal::Progress::operator ++(int) noexcept
{
	Progress t = *this;

	++(*this);

	return t;
}

void Goal::Progress::clear() noexcept
{
	m_progress = {0};
}

Goal::Goal(const QString &name, bool enableProgressAccumulation, const Progress &neededProgress, const Progress &currentProgress) noexcept
	: m_name(name), m_enableProgressAccumulation(enableProgressAccumulation), m_neededProgress(neededProgress), m_currentProgress(currentProgress) {}

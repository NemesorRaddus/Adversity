#pragma once

#include <QString>

#include "boost/rational.hpp"

typedef boost::rational<int> rational;

class Goal
{
public:
	class Progress
	{
	public:
		Progress(const rational &progress = {0}) noexcept;

		inline operator rational() const noexcept
		{
			return m_progress;
		}

		Progress &operator =(const rational &value) noexcept;

		inline bool operator ==(const Progress &other) const noexcept
		{
			return m_progress == other.m_progress;
		}
		inline bool operator !=(const Progress &other) const noexcept
		{
			return !(*this == other);
		}
		inline bool operator <(const Progress &other) const noexcept
		{
			return m_progress < other.m_progress;
		}
		inline bool operator <=(const Progress &other) const noexcept
		{
			return (*this < other) || (*this == other);
		}
		inline bool operator >(const Progress &other) const noexcept
		{
			return !(*this <= other);
		}
		inline bool operator >=(const Progress &other) const noexcept
		{
			return !(*this < other);
		}

		Progress &operator +=(const rational &change) noexcept;
		Progress operator ++() noexcept;
		Progress operator ++(int) noexcept;

		void clear() noexcept;

		inline void assignGoal(Goal *goal) noexcept
		{
			m_goal = goal;
		}

	private:
		rational m_progress;

		Goal *m_goal; // needed to perform checks if the operation should succeed
	};

	explicit Goal(const QString &name, bool enableProgressAccumulation, const Progress &neededProgress, const Progress &currentProgress = {0}) noexcept;

	inline QString name() const noexcept
	{
		return m_name;
	}
	inline rational neededProgress() const noexcept
	{
		return m_neededProgress;
	}
	inline rational currentProgress() const noexcept
	{
		return m_currentProgress;
	}
	inline Progress currentProgress() noexcept
	{
		return m_currentProgress;
	}
	inline bool hasBeenAchieved() const noexcept
	{
		return m_currentProgress >= m_neededProgress;
	}

private:
	const QString m_name;

	const bool m_enableProgressAccumulation;
	const Progress m_neededProgress;
	Progress m_currentProgress;
};

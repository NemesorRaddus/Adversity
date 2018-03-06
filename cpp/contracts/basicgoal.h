#pragma once

#include <QString>

#include "utils.h"

class BasicGoal;

class BasicProgress
{
public:
	BasicProgress(BasicGoal *context, const rational &progress = {0}) noexcept; // for normal use
	BasicProgress(const rational &progress = {0}) noexcept; // for convertions
	virtual ~BasicProgress() noexcept = default;

	inline operator rational() const noexcept
	{
		return m_progress;
	}
	inline rational operator ()() const noexcept
	{
		return m_progress;
	}

	virtual BasicProgress &operator =(const rational &value) noexcept = 0;

	inline bool operator ==(const BasicProgress &other) const noexcept
	{
		return m_progress == other.m_progress;
	}
	inline bool operator !=(const BasicProgress &other) const noexcept
	{
		return !(*this == other);
	}
	inline bool operator <(const BasicProgress &other) const noexcept
	{
		return m_progress < other.m_progress;
	}
	inline bool operator <=(const BasicProgress &other) const noexcept
	{
		return (*this < other) || (*this == other);
	}
	inline bool operator >(const BasicProgress &other) const noexcept
	{
		return !(*this <= other);
	}
	inline bool operator >=(const BasicProgress &other) const noexcept
	{
		return !(*this < other);
	}

	virtual void operator +=(const rational &change) noexcept = 0;
	virtual void operator ++() noexcept = 0;
	virtual void operator ++(int) noexcept = 0;

	virtual void clear() noexcept;

protected:
	rational m_progress;

	BasicGoal *m_context; // needed to perform checks should the operation succeed
};

class BasicGoal
{
	friend class BasicGoalBuilder;

public:
	virtual ~BasicGoal() noexcept = default;

	inline QString name() const noexcept
	{
		return m_name;
	}
	inline BasicProgress *neededProgress() const noexcept
	{
		return m_neededProgress;
	}
	inline BasicProgress *currentProgress() const noexcept
	{
		return m_currentProgress;
	}
	inline bool hasBeenAchieved() const noexcept
	{
		return *m_currentProgress >= *m_neededProgress;
	}

protected:
	BasicGoal(BasicProgress *needed, BasicProgress *current) noexcept;

	QString m_name;

	bool m_enableProgressAccumulation;
	BasicProgress *m_neededProgress;
	BasicProgress *m_currentProgress;
};

class BasicGoalBuilder
{
public:
	void setName(const QString &name) noexcept;
	void setEnableProgressAccumulation(bool enable) noexcept;
	void setNeededProgress(const rational &progress) noexcept;
	void setCurrentProgress(const rational &progress) noexcept;

protected:
	BasicGoalBuilder(BasicGoal *goal = nullptr) noexcept;
	virtual ~BasicGoalBuilder() noexcept;

	BasicGoal *m_goal;
};

#pragma once

#include <QObject>
#include <QVector>

#include "enums.h"
#include "goal.h"

class Contract : public QObject
{
	Q_OBJECT

	friend class ContractBuilder;

public:
	bool isRewardReady() const noexcept;
	inline unsigned expirationTime() const noexcept
	{
		return m_expirationTimeInDays;
	}
	inline bool hasExpired() const noexcept
	{
		return expirationTime() == 0;
	}
	inline ContractEnums::Faction faction() const noexcept
	{
		return m_faction;
	}
	inline unsigned factionPoints() const noexcept
	{
		return m_faction;
	}

	void decrementExpirationTime() noexcept;

private:
	Contract() noexcept;

	QVector <ContractGoal *> m_goals;
	unsigned m_expirationTimeInDays;
	ContractEnums::Faction m_faction;
	unsigned m_factionPoints;
};

class ContractBuilder
{
public:
	ContractBuilder() noexcept;
	~ContractBuilder() noexcept;

	Contract *getContract() noexcept;

	void setGoals(const QVector <ContractGoal *> &goals) noexcept;
	void setExpirationTime(unsigned days) noexcept;
	void setFaction(ContractEnums::Faction faction) noexcept;
	void setFactionPoints(unsigned amount) noexcept;

private:
	Contract *m_contract;
};

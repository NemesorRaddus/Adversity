#pragma once

#include <QObject>
#include <QVector>

#include "basemanagerinterface.h"

class Contract;

class ContractsManager : public QObject, public BaseManagerInterface
{
	Q_OBJECT

	Q_PROPERTY(Contract* preparedContract MEMBER m_preparedContract)

	friend class H4X;
	friend class Base;

public:
	ContractsManager(Base *base) noexcept;

	void initializeForNewBase() noexcept final;

	inline QVector <Contract *> &contracts() noexcept
	{
		return m_contracts;
	}
	Q_INVOKABLE void prepareContract(unsigned index) noexcept;

private:
	QVector <Contract *> m_contracts;
	Contract *m_preparedContract;
};

#pragma once

#include <QObject>
#include <QVector>

class Base;
class Mercenary;

class MercenariesContainer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Mercenary* preparedMercenary MEMBER m_preparedMercenary)

public:
    MercenariesContainer(Base *base) noexcept;
    ~MercenariesContainer() noexcept = default;

    Q_INVOKABLE bool prepareMercenaryAt(unsigned index) noexcept;
    void addMercenary(Mercenary *mercenary) noexcept;
    void removeMercenary(unsigned index) noexcept;
    inline const QVector <Mercenary *> &mercenaries() const noexcept
    {
        return m_mercenaries;
    }
    Q_INVOKABLE int amountOfMercenaries() const noexcept
    {
        return m_mercenaries.size();
    }
    Q_INVOKABLE int findMercenary(const QString &name) const noexcept;
    Mercenary *getMercenary(unsigned index) noexcept
    {
        return m_mercenaries.value(index,nullptr);
    }
    void setAmountOfSlots(unsigned amount) noexcept
    {
        m_amountOfSlots=amount;
    }
    Q_INVOKABLE inline unsigned amountOfSlots() const noexcept
    {
        return m_amountOfSlots;
    }
    bool canAddMercenary() const noexcept
    {
        return m_mercenaries.size() < m_amountOfSlots;
    }
    Q_INVOKABLE void dismissMercenary(const QString &name) noexcept
    {
        addDoStBan(name,m_durationOfBanAfterDismiss);
    }

    void handleNewDay() noexcept;
    void handleNewWeek() noexcept;

public slots:
    void addDoStBan(QString name, unsigned daysAmount) noexcept;
    void addDoStBan(QString name) noexcept;//permanent :c

private:
    void connectMercenaryToBanSystem(const QString &name) noexcept;
    void disconnectMercenaryFromBanSystem(const QString &name) noexcept;

    QVector <Mercenary *> m_mercenaries;
    Mercenary *m_preparedMercenary;
    unsigned m_amountOfSlots;
    const unsigned m_durationOfBanAfterDismiss = 21;
    Base *m_basePtr;
};

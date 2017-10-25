#include "checkevents.h"

#include "actionevents.h"
#include "general/randomizer.h"
#include "mercenaries/mercenary.h"

CheckEventResults::~CheckEventResults() noexcept
{
    for (auto &e : m_positive)
        delete e.first;
    for (auto &e : m_negative)
        delete e.first;
}

CheckEventResultsBuilder::CheckEventResultsBuilder() noexcept
{
    m_results=new CheckEventResults;
}

CheckEventResultsBuilder::~CheckEventResultsBuilder() noexcept
{
    delete m_results;
}

CheckEventResults *CheckEventResultsBuilder::get() noexcept
{
    validateJustBeforeReturning();
    auto r=m_results;
    m_results=new CheckEventResults;
    return r;
}

void CheckEventResultsBuilder::addPositive(const QPair<Event *, Chance> &result) noexcept
{
    if (result.first != nullptr)
        m_results->m_positive+=result;
}

void CheckEventResultsBuilder::addNegative(const QPair<Event *, Chance> &result) noexcept
{
    if (result.first != nullptr)
        m_results->m_negative+=result;
}

void CheckEventResultsBuilder::validateJustBeforeReturning() noexcept
{
    int x=100;
    for (auto e : m_results->m_positive)
    {
        if (e.second <= x)
            x-=e.second;
        else
        {
            e.second=x;
            x=0;
        }
    }
    if (x!=0)
    {
        if (m_results->m_positive.isEmpty())
            m_results->m_positive+={new NullEventResult(), 100};
        else
            m_results->m_positive.last().second=m_results->m_positive.last().second+x;
    }

    x=100;
    for (auto e : m_results->m_negative)
    {
        if (e.second <= x)
            x-=e.second;
        else
        {
            e.second=x;
            x=0;
        }
    }
    if (x!=0)
    {
        if (m_results->m_negative.isEmpty())
            m_results->m_negative+={new NullEventResult(), 100};
        else
            m_results->m_negative.last().second=m_results->m_negative.last().second+x;
    }
}

CheckEvent::CheckEvent(EventEnums::Check eventSubtype, CheckEventResults *results, QString text, const QVector<QString> &dbEntries) noexcept
    : Event(EventEnums::T_Check, text, dbEntries), m_results(results), m_eventSubtype(eventSubtype) {}

ValueCheckEvent::ValueCheckEvent(const Expression &condition, CheckEventResults *results, QString text, const QVector<QString> &dbEntries) noexcept
    : CheckEvent(EventEnums::C_ValueCheck, results, text, dbEntries), m_condition(condition) {}

QVector<EventReport> ValueCheckEvent::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (mercenary==nullptr)
        return {};

    Event *result=nullptr;

    QVariant var=m_condition.evaluate(mercenary);
    if (!var.canConvert(QVariant::Bool))
        return {};

    if (var.toBool())
    {
        int x=Randomizer::randomBetweenAAndB(1,100);
        for (auto e : m_results->positive())
        {
            if (e.second * mercenary->luck() >= x)
            {
                result=e.first;
                break;
            }
            else
                x-=e.second;
        }
    }
    else
    {
        int x=Randomizer::randomBetweenAAndB(1,100);
        for (auto e : m_results->negative())
        {
            if (e.second * mercenary->luck() >= x)
            {
                result=e.first;
                break;
            }
            else
                x-=e.second;
        }
    }

    if (result==nullptr)
        return {};

    return QVector<EventReport>{eventText()} + result->execute(mercenary);
}

EquipmentCheckEvent::EquipmentCheckEvent(EquipmentEnums::Category neededEq, CheckEventResults *results, QString text, const QVector<QString> &dbEntries) noexcept
    : CheckEvent(EventEnums::C_EquipmentCheck,results, text, dbEntries), m_neededEquipment(neededEq) {}

QVector<EventReport> EquipmentCheckEvent::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (mercenary==nullptr)
        return {};

    Event *result=nullptr;

    bool has=mercenary->hasEquipmentFromCategory(m_neededEquipment);

    if (has)
    {
        int x=Randomizer::randomBetweenAAndB(1,100);
        for (auto e : m_results->positive())
        {
            if (e.second * mercenary->luck() >= x)
            {
                result=e.first;
                break;
            }
            else
                x-=e.second;
        }
    }
    else
    {
        int x=Randomizer::randomBetweenAAndB(1,100);
        for (auto e : m_results->negative())
        {
            if (e.second * mercenary->luck() >= x)
            {
                result=e.first;
                break;
            }
            else
                x-=e.second;
        }
    }

    if (result==nullptr)
        return {};

    return QVector<EventReport>{eventText()} + result->execute(mercenary);
}

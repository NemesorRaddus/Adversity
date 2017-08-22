#include "event.h"

#include <QDebug>

Expression::Expression() noexcept
    : m_isExprValid(0)
{
    handleEngine();
}

Expression::Expression(const QString &expr) noexcept
    : m_expr(expr)
{
    handleEngine();
    validateExpr();
}

Expression::Expression(const Expression &other) noexcept
    : m_expr(other.m_expr)
{
    handleEngine();
    validateExpr();
}

void Expression::set(const QString &expr) noexcept
{
    m_expr=expr;
    validateExpr();
}

bool Expression::isValid() const noexcept
{
    return m_isExprValid;
}

QVariant Expression::evaluate(const Hero *context) const noexcept
{
    if (context==nullptr)
        return {};

    m_engine->globalObject().setProperty("CE",context->combatEffectiveness());
    m_engine->globalObject().setProperty("PR",context->proficiency());
    m_engine->globalObject().setProperty("CL",context->cleverness());
    m_engine->globalObject().setProperty("HP",context->health());
    m_engine->globalObject().setProperty("HL",context->healthLimit());
    m_engine->globalObject().setProperty("DHR",context->dailyHealthRecovery());
    m_engine->globalObject().setProperty("ST",context->stress());
    m_engine->globalObject().setProperty("SB",context->stressBorder());
    m_engine->globalObject().setProperty("SL",context->stressLimit());
    m_engine->globalObject().setProperty("SR",context->stressResistance());
    m_engine->globalObject().setProperty("DSR",context->dailyStressRecovery());
    m_engine->globalObject().setProperty("LU",context->luck());
    m_engine->globalObject().setProperty("SA",context->salary());
    m_engine->globalObject().setProperty("DFC",context->dailyFoodConsumption());

    return m_engine->evaluate(m_expr).toVariant();
}

void Expression::validateExpr() noexcept
{
    QJSValue v=m_engine->evaluate(m_expr);
    if (v.isError())
        m_isExprValid=0;
    else
        m_isExprValid=1;
}

void Expression::handleEngine() noexcept
{
    static QJSEngine *theEngine=nullptr;
    if (theEngine==nullptr)
    {
        theEngine=new QJSEngine();

        theEngine->globalObject().setProperty("CE",0);
        theEngine->globalObject().setProperty("PR",0);
        theEngine->globalObject().setProperty("CL",0);
        theEngine->globalObject().setProperty("HP",0);
        theEngine->globalObject().setProperty("HL",0);
        theEngine->globalObject().setProperty("DHR",0);
        theEngine->globalObject().setProperty("ST",0);
        theEngine->globalObject().setProperty("SB",0);
        theEngine->globalObject().setProperty("SL",0);
        theEngine->globalObject().setProperty("SR",0);
        theEngine->globalObject().setProperty("DSR",0);
        theEngine->globalObject().setProperty("LU",0);
        theEngine->globalObject().setProperty("SA",0);
        theEngine->globalObject().setProperty("DFC",0);
    }

    m_engine=theEngine;
}

QVector<EventReport> Event::execute(Hero *context) noexcept
{
    unlockDatabaseEntries(context);
    return executeSpecificOps(context);
}

void Event::setEventText(const QString &text) noexcept
{
    m_eventText=text;
}

void Event::unlockDatabaseEntries(Hero *context) noexcept
{
    for (auto e : m_unlockedDatabaseEntries)
        context->base()->database()->unlockEntry(e);
}

QVector<EventReport> MultiEvent::executeSpecificOps(Hero *context) noexcept
{
    QVector <EventReport> r;
    for (auto e : m_eventsToExecute)
        r+=e->execute(context);
    return r;
}

GiveHealthEventResult::GiveHealthEventResult(const Expression &addedValue) noexcept
    : ActionEvent(EventEnums::A_GiveHealth), m_value(addedValue) {}

QVector<EventReport> GiveHealthEventResult::executeSpecificOps(Hero *hero) noexcept
{
    hero->changeHealth(m_value.evaluate(hero).toUInt());

    return {eventText()};
}

GiveStressEventResult::GiveStressEventResult(const Expression &addedValue) noexcept
    : ActionEvent(EventEnums::A_GiveStress), m_value(addedValue) {}

QVector<EventReport> GiveStressEventResult::executeSpecificOps(Hero *hero) noexcept
{
    m_value.evaluate(hero).toUInt()>=0 ? hero->increaseStress(m_value.evaluate(hero).toUInt()) : hero->decreaseStress(-m_value.evaluate(hero).toUInt());

    return {eventText()};
}

ModifyAttributeEventResult::ModifyAttributeEventResult(const AttributeModification &modification) noexcept
    : ActionEvent(EventEnums::A_ModifyAttribute), m_modification(modification) {}

QVector<EventReport> ModifyAttributeEventResult::executeSpecificOps(Hero *hero) noexcept
{
    hero->addAttributeModification(new AttributeModification(m_modification));

    return {eventText()};
}

QVector<EventReport> KillHeroEventResult::executeSpecificOps(Hero *hero) noexcept
{
    hero->die();

    return {eventText()};
}

QVector<EventReport> AddEquipmentEventResult::executeSpecificOps(Hero *hero) noexcept
{
    if (m_equipmentToAdd->type()==EquipmentEnums::T_Armor)
    {
        if (hero->armor()==nullptr)
            hero->equipArmor(m_equipmentToAdd);
        else
            hero->addCarriedEquipment(m_equipmentToAdd);
    }
    else
    {
        bool ok=0;
        for (int i=0;i<hero->amountOfWeaponToolSlots();++i)
            if (hero->weaponTool(i)==nullptr)
            {
                hero->equipWeaponTool(m_equipmentToAdd,i);
                ok=1;
                break;
            }
        if (!ok)
            hero->addCarriedEquipment(m_equipmentToAdd);
    }

    return {eventText()};
}

QVector<EventReport> RemoveEquipmentEventResult::executeSpecificOps(Hero *hero) noexcept
{
    if (m_equipmentType==EquipmentEnums::T_Armor)
        hero->unequipArmor();
    else
        hero->unequipWeaponTool(m_equipmentSlot);

    return {eventText()};
}

GiveResourceEventResult::GiveResourceEventResult(BaseEnums::Resource resource, const Expression &amount) noexcept
    : ActionEvent(EventEnums::A_GiveResource), m_resource(resource), m_amount(amount) {}

QVector<EventReport> GiveResourceEventResult::executeSpecificOps(Hero *hero) noexcept
{
    int am=m_amount.evaluate(hero).toInt();
    int cam;

    switch (m_resource)
    {
    case BaseEnums::R_AetheriteOre:
        cam=hero->carriedAetheriteOre();
        if (cam > am)
            hero->setCarriedAetheriteOre(cam+am);
        else
            hero->setCarriedAetheriteOre(0);
        break;
    case BaseEnums::R_BuildingMaterials:
        cam=hero->carriedBuildingMaterials();
        if (cam > am)
            hero->setCarriedBuildingMaterials(cam+am);
        else
            hero->setCarriedBuildingMaterials(0);
        break;
    case BaseEnums::R_Energy:
        cam=hero->carriedEnergy();
        if (cam > am)
            hero->setCarriedEnergy(cam+am);
        else
            hero->setCarriedEnergy(0);
        break;
    case BaseEnums::R_FoodSupplies:
        cam=hero->carriedFoodSupplies();
        if (cam > am)
            hero->setCarriedFoodSupplies(cam+am);
        else
            hero->setCarriedFoodSupplies(0);
        break;
    default:
        break;
    }

    return {eventText()};
}

GiveResourceRandomEventResult::GiveResourceRandomEventResult(const Expression &amount) noexcept
    : GiveResourceEventResult(static_cast<BaseEnums::Resource>(Randomizer::randomBetweenAAndB(0, BaseEnums::R_END-1)), amount)
{
    static_cast<QString>(m_amount).replace("C_RESO", BaseEnums::fromResourceEnumToQString(m_resource).toUpper());
}

QVector<EventReport> NoSignalEventResult::executeSpecificOps(Hero *hero) noexcept
{
    hero->setNoSignalDaysRemaining(m_durationInDays);

    return {eventText()};
}

CheckEventResults::CheckEventResults(const CheckEventResults &other) noexcept
    : m_positive(other.m_positive), m_negative(other.m_negative) {}

CheckEventResults CheckEventResultsBuilder::get() noexcept
{
    validateJustBeforeReturning();
    auto r=m_results;
    reset();
    return r;
}

void CheckEventResultsBuilder::reset() noexcept
{
    m_results.m_positive.clear();
    m_results.m_negative.clear();
}

void CheckEventResultsBuilder::addPositive(const QPair<Event *, Chance> &result) noexcept
{
    if (result.first != nullptr)
        m_results.m_positive+=result;
}

void CheckEventResultsBuilder::addNegative(const QPair<Event *, Chance> &result) noexcept
{
    if (result.first != nullptr)
        m_results.m_negative+=result;
}

void CheckEventResultsBuilder::validateJustBeforeReturning() noexcept
{
    int x=100;
    for (auto e : m_results.m_positive)
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
        if (m_results.m_positive.isEmpty())
            m_results.m_positive+={new NullEventResult(), 100};
        else
            m_results.m_positive.last().second=m_results.m_positive.last().second+x;
    }

    x=100;
    for (auto e : m_results.m_negative)
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
        if (m_results.m_negative.isEmpty())
            m_results.m_negative+={new NullEventResult(), 100};
        else
            m_results.m_negative.last().second=m_results.m_negative.last().second+x;
    }
}

CheckEvent::CheckEvent(EventEnums::Check eventSubtype, const CheckEventResults &results) noexcept
    : Event(EventEnums::T_Check), m_eventSubtype(eventSubtype), m_results(results) {}

AttributeCheckEvent::AttributeCheckEvent(const Expression &condition, const CheckEventResults &results) noexcept
    : CheckEvent(EventEnums::C_AttributeCheck, results), m_condition(condition) {}

QVector<EventReport> ValueCheckEvent::executeSpecificOps(Hero *hero) noexcept
{
    if (hero==nullptr)
        return {};

    Event *result=nullptr;

    QVariant var=m_condition.evaluate(hero);
    if (!var.canConvert(QVariant::Bool))
        return {};

    if (var.toBool())
    {
        int x=Randomizer::randomBetweenAAndB(1,100);
        for (auto e : m_results.positive())
        {
            if (e.second>=x)
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
        for (auto e : m_results.negative())
        {
            if (e.second>=x)
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

    return result->execute(hero);
}

PossibilityEvent::PossibilityEvent(Chance chance, Event *event) noexcept
    : Event(EventEnums::T_Possibility), m_chance(chance), m_event(event) {}

QVector<EventReport> PossibilityEvent::executeSpecificOps(Hero *hero) noexcept
{
    if (hero==nullptr || m_event==nullptr)
        return {};

    if (m_chance>=Randomizer::randomBetweenAAndB(1,100))
        return m_event->execute(hero);
    return {};
}

EncounterReport::EncounterReport(const QString &encName, const QVector<EventReport> &events, const Time &time) noexcept
    : m_encounterName(encName), m_events(events), m_time(time) {}

Encounter::Encounter(const QString &name, Event *rootEvent) noexcept
    : m_name(name), m_rootEvent(rootEvent) {}

EncounterReport Encounter::execute(Hero *hero, const Time &currentTime) const noexcept
{
    return {m_name, m_rootEvent->execute(hero), currentTime};
}

Land::Land(const QString &name, const QString &description) noexcept
    : m_name(name), m_description(description) {}

void Land::setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept
{
    m_encounters=encCont;
}

Encounter *Land::getRandomEncounter() const noexcept
{
    if (m_encounters->encounters().isEmpty())
        return nullptr;

    auto r=new Encounter("",nullptr);
    *r=*(m_encounters->encounters()[Randomizer::randomBetweenAAndB(0, m_encounters->encounters().size()-1)]);
    return r;
}

void Land::setName(const QString &name) noexcept
{
    m_name=name;
}

void Land::setDescription(const QString &desc) noexcept
{
    m_description=desc;
}

void LandBuilder::setName(const QString &name) noexcept
{
    m_land->setName(name);
}

void LandBuilder::setDescription(const QString &desc) noexcept
{
    m_land->setDescription(desc);
}

Encounter *Mission::takeRandomEncounter() noexcept
{
    return m_encounters.takeAt(Randomizer::randomBetweenAAndB(0,m_encounters.size()-1));
}

void Mission::decrementDuration() noexcept
{
    --m_duration;
}

void Mission::assignHero(Hero *hero) noexcept
{
    m_assignedHero=hero;
}

void Mission::start() noexcept
{

}

void Mission::continueToNextEncounter() noexcept
{

}

Mission::Mission() noexcept
    : m_land(nullptr), m_duration(1), m_assignedHero(nullptr) {}

void Mission::setLand(Land *land) noexcept
{
    m_land = land;
}

void Mission::setDuration(unsigned days) noexcept
{
    if (days<1)
        return;
    m_duration=days;
}

void Mission::addEncounter(Encounter *encounter) noexcept
{
    m_encounters+=encounter;
}

MissionBuilder::MissionBuilder() noexcept
{
    m_mission=new Mission();
}

MissionBuilder::~MissionBuilder() noexcept
{
    delete m_mission;
}

Mission *MissionBuilder::getMission() noexcept
{
    Mission *ret=m_mission;
    m_mission=new Mission();
    return ret;
}

Mission *MissionBuilder::generateMission(Land *land, unsigned duration) noexcept
{
    resetMission();
    setLand(land);
    setDuration(duration);
    while (duration--)
        addRandomEncounter();
    Mission *ret=m_mission;
    m_mission=new Mission();
    return ret;
}

void MissionBuilder::resetMission() noexcept
{
    delete m_mission;
    m_mission=new Mission();
}

void MissionBuilder::setLand(Land *land) noexcept
{
    m_mission->setLand(land);
}

void MissionBuilder::setDuration(unsigned duration) noexcept
{
    m_mission->setDuration(duration);
}

void MissionBuilder::addRandomEncounter() noexcept
{
    addEncounter(m_mission->land()->getRandomEncounter());
}

void MissionBuilder::addEncounter(Encounter *encounter) noexcept
{
    m_mission->addEncounter(encounter);
}

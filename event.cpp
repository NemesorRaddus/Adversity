#include "event.h"

#include "game.h"

#include <QDebug>

EventEnums::MissionDifficulty EventEnums::fromQStringToMissionDifficultyEnum(const QString &missionDifficulty) noexcept
{
    if (missionDifficulty == "Short")
        return MD_Short;
    if (missionDifficulty == "Medium")
        return MD_Medium;
    if (missionDifficulty == "Long")
        return MD_Long;
    if (missionDifficulty == "Extreme")
        return MD_Extreme;
    if (missionDifficulty == "Veteran")
        return MD_Veteran;
    if (missionDifficulty == "Master")
        return MD_Master;
    if (missionDifficulty == "Heroic")
        return MD_Heroic;
    qWarning()<<"QString->enum conversion failed for "<<missionDifficulty;
}

QString EventEnums::fromMissionDifficultyEnumToQString(EventEnums::MissionDifficulty missionDifficulty) noexcept
{
    if (missionDifficulty == MD_Short)
        return "Short";
    if (missionDifficulty == MD_Medium)
        return "Medium";
    if (missionDifficulty == MD_Long)
        return "Long";
    if (missionDifficulty == MD_Extreme)
        return "Extreme";
    if (missionDifficulty == MD_Veteran)
        return "Veteran";
    if (missionDifficulty == MD_Master)
        return "Master";
    if (missionDifficulty == MD_Heroic)
        return "Heroic";
    qWarning()<<"enum->QString conversion failed for "<<missionDifficulty;
}

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

    m_engine->globalObject().setProperty("C_AETH",context->carriedAetheriteOre());
    m_engine->globalObject().setProperty("C_BMAT",context->carriedBuildingMaterials());
    m_engine->globalObject().setProperty("C_ENRG",context->carriedEnergy());
    m_engine->globalObject().setProperty("C_FOOS",context->carriedFoodSupplies());

    m_engine->globalObject().setProperty("M_FULLDUR",context->assignedMission()->fullDuration());
    m_engine->globalObject().setProperty("M_REMDAYS",context->assignedMission()->remainingDays());

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

        theEngine->globalObject().setProperty("C_AETH",0);
        theEngine->globalObject().setProperty("C_BMAT",0);
        theEngine->globalObject().setProperty("C_ENRG",0);
        theEngine->globalObject().setProperty("C_FOOS",0);

        theEngine->globalObject().setProperty("M_FULLDUR",0);
        theEngine->globalObject().setProperty("M_REMDAYS",0);
    }

    m_engine=theEngine;
}

ValueRange::ValueRange() noexcept
    : m_min("0"), m_max("0") {}

ValueRange::ValueRange(const Expression &min, const Expression &max) noexcept
    : m_min(min), m_max(max) {}

ValueRange::ValueRange(const Expression &value) noexcept
    : m_min(value), m_max(value) {}

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
        context->base()->database()->unlockEntry(e,context->assignedMission()->land()->name());
}

MultiEvent::~MultiEvent() noexcept
{
    for (auto &e : m_eventsToExecute)
        delete e;
}

QVector<EventReport> MultiEvent::executeSpecificOps(Hero *context) noexcept
{
    QVector <EventReport> r={eventText()};
    for (auto e : m_eventsToExecute)
        r+=e->execute(context);
    return r;
}

QVector<EventReport> NullEventResult::executeSpecificOps(Hero *) noexcept
{
    return {eventText()};
}

GiveHealthEventResult::GiveHealthEventResult(const ValueRange &addedValue, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_GiveHealth, text, dbEntries), m_value(addedValue) {}

QVector<EventReport> GiveHealthEventResult::executeSpecificOps(Hero *hero) noexcept
{
    if (m_value.singleValue())
        hero->changeHealth(m_value.max().evaluate(hero).toUInt());
    else
    {
        auto max=m_value.max().evaluate(hero).toUInt(), min=m_value.min().evaluate(hero).toUInt();
        hero->changeHealth(Randomizer::randomBetweenAAndB(min, max));
    }

    return {eventText()};
}

GiveStressEventResult::GiveStressEventResult(const ValueRange &addedValue, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_GiveStress, text, dbEntries), m_value(addedValue) {}

QVector<EventReport> GiveStressEventResult::executeSpecificOps(Hero *hero) noexcept
{
    int v;
    if (m_value.singleValue())
        v=m_value.max().evaluate(hero).toInt();
    else
    {
        int max=m_value.max().evaluate(hero).toInt(), min=m_value.min().evaluate(hero).toInt();
        v=Randomizer::randomBetweenAAndB(min,max);
    }
    if (v>=0)
        hero->increaseStress(v);
    else
        hero->decreaseStress(-v);

    return {eventText()};
}

ModifyAttributeEventResult::ModifyAttributeEventResult(const AttributeModificationHelper &modification, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_ModifyAttribute, text, dbEntries), m_modification(modification) {}

QVector<EventReport> ModifyAttributeEventResult::executeSpecificOps(Hero *hero) noexcept
{
    QVariant val;
    if (m_modification.expressionRange.singleValue())
        val=m_modification.expressionRange.max().evaluate(hero);
    else
    {
        QVariant min=m_modification.expressionRange.min().evaluate(hero);
        QVariant max=m_modification.expressionRange.max().evaluate(hero);

        if (min.type() == QVariant::Double || max.type() == QVariant::Double)
        {
            double dmin=min.toDouble(),dmax=max.toDouble();

            double diff=0;
            if (dmin<0)
            {
                diff=-dmin;
                dmin+=diff;
                dmax+=diff;
            }

            double r=static_cast<double>(Randomizer::randomBetweenAAndB(dmin*100,dmax*100))/100;

            r-=diff;

            val=r;
        }
        else
        {
            int imin=min.toInt(),imax=max.toInt();

            int diff=0;
            if (imin<0)
            {
                diff=-imin;
                imin+=diff;
                imax+=diff;
            }

            int r=Randomizer::randomBetweenAAndB(imin,imax);

            r-=diff;

            val=r;
        }
    }

    int durr;
    if (m_modification.durationRange.singleValue())
        durr=m_modification.durationRange.max().evaluate(hero).toInt();
    else
    {
        int durMin=m_modification.durationRange.min().evaluate(hero).toInt();
        int durMax=m_modification.durationRange.max().evaluate(hero).toInt();

        int durDiff=0;
        if (durMin<0)/*durMin==-1*/
        {
            durDiff=-durMin;
            durMin+=durDiff;
            durMax+=durDiff;
        }

        durr=Randomizer::randomBetweenAAndB(durMin,durMax);

        durr-=durDiff;
    }

    hero->addAttributeModification(new AttributeModification({m_modification.attribute,m_modification.type,val,durr}));

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

AddEquipmentRandomEventResult::AddEquipmentRandomEventResult(ValueRange tier, int equipmentTypeFlags, QString text, const QVector<QString> &dbEntries) noexcept
    : AddEquipmentEventResult(nullptr, text, dbEntries), m_tier(tier), m_eqTypes(equipmentTypeFlags) {}

QVector<EventReport> AddEquipmentRandomEventResult::executeSpecificOps(Hero *hero) noexcept
{
    unsigned min=m_tier.min().evaluate(hero).toUInt(), max=m_tier.max().evaluate(hero).toUInt();
    if (min>max)
        return {};

    while (true)
    {
        int randomized=Randomizer::randomBetweenAAndB(0, Game::gameInstance()->assetsPool().equipment().size()-1);
        auto t=Game::gameInstance()->assetsPool().equipment()[randomized]->type();
        if (t & m_eqTypes)
        {
            m_equipmentToAdd=Game::gameInstance()->assetsPool().makeEquipmentAtPos(randomized);
            break;
        }
    }

    return AddEquipmentEventResult::executeSpecificOps(hero);
}

QVector<EventReport> RemoveEquipmentEventResult::executeSpecificOps(Hero *hero) noexcept
{
    if (m_equipmentType==EquipmentEnums::T_Armor)
        hero->unequipArmor();
    else
        hero->unequipWeaponTool(m_equipmentSlot);

    return {eventText()};
}

GiveResourceEventResult::GiveResourceEventResult(BaseEnums::Resource resource, const ValueRange &amount, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_GiveResource, text, dbEntries), m_resource(resource), m_amount(amount) {}

QVector<EventReport> GiveResourceEventResult::executeSpecificOps(Hero *hero) noexcept
{
    int am;
    if (m_amount.singleValue())
        am=m_amount.max().evaluate(hero).toInt();
    else
    {
        int max=m_amount.max().evaluate(hero).toInt(), min=m_amount.min().evaluate(hero).toInt();
        am=Randomizer::randomBetweenAAndB(min,max);
    }
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

GiveResourceRandomEventResult::GiveResourceRandomEventResult(const ValueRange &amount, QString text, const QVector<QString> &dbEntries) noexcept
    : GiveResourceEventResult(static_cast<BaseEnums::Resource>(Randomizer::randomBetweenAAndB(0, BaseEnums::R_END-1)), amount, text, dbEntries)
{
    static_cast<QString>(m_amount.min()).replace("C_RESO", BaseEnums::fromResourceEnumToQString(m_resource).toUpper());
    static_cast<QString>(m_amount.max()).replace("C_RESO", BaseEnums::fromResourceEnumToQString(m_resource).toUpper());
}

NoSignalEventResult::NoSignalEventResult(const ValueRange &durationInDays, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_NoSignal, text, dbEntries), m_durationInDays(durationInDays) {}

QVector<EventReport> NoSignalEventResult::executeSpecificOps(Hero *hero) noexcept
{
    if (m_durationInDays.singleValue())
        hero->setNoSignalDaysRemaining(m_durationInDays.max().evaluate(hero).toInt());
    else
    {
        int max=m_durationInDays.max().evaluate(hero).toInt(), min=m_durationInDays.min().evaluate(hero).toInt();
        hero->setNoSignalDaysRemaining(Randomizer::randomBetweenAAndB(min,max));
    }

    return {eventText()};
}

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
        for (auto e : m_results->positive())
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
        for (auto e : m_results->negative())
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

    return QVector<EventReport>{eventText()} + result->execute(hero);
}

EquipmentCheckEvent::EquipmentCheckEvent(EquipmentEnums::Category neededEq, CheckEventResults *results, QString text, const QVector<QString> &dbEntries) noexcept
    : CheckEvent(EventEnums::C_EquipmentCheck,results, text, dbEntries), m_neededEquipment(neededEq) {}

QVector<EventReport> EquipmentCheckEvent::executeSpecificOps(Hero *hero) noexcept
{
    if (hero==nullptr)
        return {};

    Event *result=nullptr;

    bool has=hero->hasEquipmentFromCategory(m_neededEquipment);

    if (has)
    {
        int x=Randomizer::randomBetweenAAndB(1,100);
        for (auto e : m_results->positive())
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
        for (auto e : m_results->negative())
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

    return QVector<EventReport>{eventText()} + result->execute(hero);
}

PossibilityEvent::PossibilityEvent(Chance chance, Event *event, QString text, const QVector<QString> &dbEntries) noexcept
    : Event(EventEnums::T_Possibility, text, dbEntries), m_chance(chance), m_event(event) {}

PossibilityEvent::~PossibilityEvent() noexcept
{
    delete m_event;
}

QVector<EventReport> PossibilityEvent::executeSpecificOps(Hero *hero) noexcept
{
    if (hero==nullptr || m_event==nullptr)
        return {};

    if (static_cast<unsigned>(m_chance)>=Randomizer::randomBetweenAAndB(1,100))
        return QVector<EventReport>{eventText()} + m_event->execute(hero);
    return {eventText()};
}

Report::Report(EventEnums::ReportType type, const Time &time) noexcept
    : m_reportType(type), m_time(time) {}

EncounterReport::EncounterReport(const QString &heroArt, const QVector<EventReport> &events, const Time &time) noexcept
    : Report(EventEnums::RT_Encounter, time), m_heroArt(heroArt), m_events(events) {}

QString EncounterReport::text() const noexcept
{
    QString r;
    for (const auto &e : m_events)
        r+=e+"\n";
    return r;
}

BuildingUpgradeReport::BuildingUpgradeReport(BaseEnums::Building building, unsigned level, const Time &time) noexcept
    : Report(EventEnums::RT_BuildingUpgrade, time),
      m_buildingArt("qrc:/graphics/Buildings/"+Global::alterNormalTextToInternal(BaseEnums::fromBuildingEnumToQString(building))),
      m_building(building), m_level(level) {}

QString BuildingUpgradeReport::text() const noexcept
{
    return BaseEnums::fromBuildingEnumToQString(m_building)+" has been upgraded to level "+QString::number(m_level)+".";
}

HeroArrivalReport::HeroArrivalReport(const QString &heroArt, const QString &heroName, const Time &time) noexcept
    : Report(EventEnums::RT_HeroArrival, time), m_heroArt(heroArt), m_name(heroName) {}

QString HeroArrivalReport::text() const noexcept
{
    return "Recently hired mercenary, "+Game::gameInstance()->tr(m_name)+" has arrived.";
}

TradeCompletionReport::TradeCompletionReport(BaseEnums::Resource targetResource, unsigned amount, const Time &time) noexcept
    : Report(EventEnums::RT_TradeCompletion, time), m_targetResource(targetResource), m_amount(amount) {}

QString TradeCompletionReport::text() const noexcept
{
    return "We received that "+QString::number(m_amount)+" units of "+BaseEnums::fromResourceEnumToQString(m_targetResource)+" you ordered recently.";
}

EquipmentArrivalReport::EquipmentArrivalReport(const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_EquipmentArrival, time), m_name(name) {}

QString EquipmentArrivalReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" has been delivered and is now stored in storage room.";
}

DesertionReport::DesertionReport(const QString &heroArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_Desertion, time), m_heroArt(heroArt), m_name(name) {}

QString DesertionReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" is missing! The room in barracks is empty and one of the shuttles in the docking station disappeared!";
}

HungerReport::HungerReport(const QString &heroArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_Hunger, time), m_heroArt(heroArt), m_name(name) {}

QString HungerReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" hasn't got daily food ration!";
}

NoSalaryReport::NoSalaryReport(const QString &heroArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_NoSalary, time), m_heroArt(heroArt), m_name(name) {}

QString NoSalaryReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" hadn't been paid this week.";
}

MissionEndReport::MissionEndReport(const QString &heroArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_MissionEnd, time), m_heroArt(heroArt), m_name(name) {}

QString MissionEndReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" has successfully returned to the base.";
}

TrainingCompletionReport::TrainingCompletionReport(const QString &heroArt, const QString &heroName, BaseEnums::Building building, const Time &time) noexcept
    : Report(EventEnums::RT_MissionEnd, time), m_heroArt(heroArt), m_heroName(heroName), m_building(building) {}

QString TrainingCompletionReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_heroName)+" has finished training in "+BaseEnums::fromBuildingEnumToQString(m_building)+".";
}

SignalLostReport::SignalLostReport(const QString &heroArt, const QString &heroName, const QString &landName, const Time &time) noexcept
    : Report(EventEnums::RT_SignalLost, time), m_heroArt(heroArt), m_heroName(heroName), m_landName(landName) {}

QString SignalLostReport::text() const noexcept
{
    return "We've lost connection with "+Game::gameInstance()->tr(m_heroName)+", who is exploring "+m_landName+".";
}

SignalRetrievedReport::SignalRetrievedReport(const QString &heroArt, const QString &landName, const Time &time) noexcept
    : Report(EventEnums::RT_SignalRetrieved, time), m_heroArt(heroArt), m_landName(landName) {}

QString SignalRetrievedReport::text() const noexcept
{
    return "Finally I can hear you clearly.";
}

MissionStartReport::MissionStartReport(const QString &heroArt, int stress, int stressLimit, const Time &time) noexcept
    : Report(EventEnums::RT_MissionStart, time), m_heroArt(heroArt), m_stress(stress), m_stressLimit(stressLimit) {}

QString MissionStartReport::text() const noexcept
{
    if (m_stressLimit == -1)
        return "Order understood.";
    int perc = m_stress*10/m_stressLimit;
    switch (perc) {
    case 0:
        return "Finally! A new mission! I thought I would have died of boredom.";
    case 1:
        return "Well, I've been looking forward to go on mission.";
    case 2:
        return "A new mission? I think I can handle it.";
    case 3:
        return "I'm not too happy about going on the mission, but I guess I have to.";
    case 4:
        return "I'm not sure if I am the right person for this task.";
    case 5:
        return "Couldn't anyone go instead of me?";
    case 6:
        return "I don't feel well, it's too much for me.";
    case 7:
        return "Please! Don't make me go back to these horrors!";
    case 8:
        return "You must be crazy! I'm not ready for this shit! I'm going to fucking die!";
    default:
        return "Are you insane?! It's a fucking suicide mission! I'm gonna die there and my fucking body will be eaten by some shitworms!";
    }
}

unsigned UnifiedReport::m_currentID = 0;

UnifiedReport::UnifiedReport(const Time &time, const QString &msg, const QString &artSource) noexcept
    : m_id(m_currentID++), m_time(time), m_msg(msg), m_art(artSource) {}

UnifiedReport::UnifiedReport(Report *sourceToDestroy) noexcept
{
    m_id=m_currentID++;
    m_time=sourceToDestroy->time();
    m_art=sourceToDestroy->art();
    m_msg=sourceToDestroy->text();

    delete sourceToDestroy;
}

UnifiedReport::UnifiedReport(const UnifiedReportDataHelper &data) noexcept
    : m_id(m_currentID++), m_time(data.time), m_msg(data.msg), m_art(data.art) {}

UnifiedReport::operator UnifiedReportDataHelper() const noexcept
{
    return {m_id, m_time, m_msg, m_art};
}

QString UnifiedReport::timestamp() const noexcept
{
    QString r;
    r+=static_cast<unsigned>(m_time.h)<10 ? "0"+QString::number(m_time.h) : QString::number(m_time.h);
    r+=":";
    r+=static_cast<unsigned>(m_time.min)<10 ? "0"+QString::number(m_time.min) : QString::number(m_time.min);
    r+=" Day ";
    r+=QString::number(m_time.d);
    return r;
}

QDataStream &operator<<(QDataStream &stream, const UnifiedReportDataHelper &report) noexcept
{
    stream<<static_cast<quint32>(report.id);
    stream<<report.time;
    stream<<report.msg;
    stream<<report.art;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, UnifiedReportDataHelper &report) noexcept
{
    quint32 uuu;
    stream>>uuu;
    report.id=uuu;
    stream>>report.time;
    stream>>report.msg;
    stream>>report.art;

    return stream;
}

Encounter::Encounter(const QString &name, Event *rootEvent) noexcept
    : m_name(name), m_rootEvent(rootEvent) {}

EncounterReport *Encounter::execute(Hero *hero, const Time &currentTime) const noexcept
{
    auto reps = m_rootEvent->execute(hero);
    for (int i=0;i<reps.size();)
    {
        if (reps[i].isEmpty())
            reps.remove(i);
        else
            ++i;
    }
    return new EncounterReport{hero->pathToArt(), reps, currentTime};
}

EncountersContainer::~EncountersContainer() noexcept
{
    for (auto e : m_encounters)
        delete e;
}

void EncountersContainer::addEncounter(Encounter *enc) noexcept
{
    m_encounters+=enc;
}

void EncountersContainer::removeEncounter(unsigned index) noexcept
{
    if (index<m_encounters.size())
    {
        delete m_encounters[index];
        m_encounters.remove(index);
    }
}

Land::Land(const LandInfo &info) noexcept
    : m_info(info)
{
    m_encounters=new EncountersContainer;
}

Land::~Land() noexcept
{
    delete m_encounters;
}

Encounter *Land::makeRandomEncounter() const noexcept
{
    if (m_encounters->encounters().isEmpty())
        return nullptr;

    auto r=new Encounter("",nullptr);
    *r=*(m_encounters->encounters()[Randomizer::randomBetweenAAndB(0, m_encounters->encounters().size()-1)]);
    return r;
}

void Land::setInfo(const LandInfo &info) noexcept
{
    m_info=info;
}

void Land::setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept
{
    delete m_encounters;
    m_encounters=encCont;
}

LandBuilder::LandBuilder() noexcept
{
    m_land = new Land({});
}

LandBuilder::~LandBuilder() noexcept
{
    delete m_land;
}

Land *LandBuilder::getLand() noexcept
{
    Land *ret=m_land;
    m_land=new Land({});
    return ret;
}

void LandBuilder::resetLand() noexcept
{
    delete m_land;
    m_land = new Land({});
}

void LandBuilder::setInfo(const LandInfo &info) noexcept
{
    m_land->setInfo(info);
}

void LandBuilder::setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept
{
    m_land->setAssociatedEncountersContainer(encCont);
}

void Mission::decrementDuration() noexcept
{
    --m_remainingDays;
}

void Mission::assignHero(Hero *hero) noexcept
{
    m_assignedHero=hero;
}

void Mission::start() noexcept
{
    m_assignedHero->base()->addReport(new UnifiedReport(new MissionStartReport(m_assignedHero->pathToArt(), m_assignedHero->stress(), m_assignedHero->stressLimit(), m_assignedHero->base()->gameClock()->currentTime())));
    m_assignedHero->base()->registerLatestReportInMission(this);
    planNextEncounter();
}

EncounterReport *Mission::doEncounter(const Time &now) noexcept
{
    auto r = m_encounters[m_nextEncounter].second->execute(m_assignedHero, now);
    ++m_nextEncounter;
    planNextEncounter();
    return r;
}

void Mission::end() noexcept
{
    m_assignedHero->returnToBase();
}

void Mission::forceEnd() noexcept
{
    m_assignedHero->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    end();
}

void Mission::forceEndSilently() noexcept
{
    m_assignedHero->base()->gameClock()->removeAlarmsConnectedWithMission(this);
}

void Mission::abort() noexcept
{
    m_assignedHero->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    m_assignedHero->assignMission(nullptr);
    auto b=m_assignedHero->base();
    m_assignedHero->die();
    b->removeMission(this);
}

void Mission::addRelatedReport(UnifiedReport *report) noexcept
{
    m_relatedReports+=report;
}

void Mission::prepareReport(unsigned index) noexcept
{
    if (index<m_relatedReports.size())
        m_preparedRelatedReport=m_relatedReports[index];
}

Mission::Mission() noexcept
    : m_land(nullptr), m_difficulty(EventEnums::MD_END), m_duration(1), m_remainingDays(1), m_nextEncounter(0), m_minutesSinceMidnightOfLastEncounter(-1), m_assignedHero(nullptr), m_preparedRelatedReport(nullptr) {}

void Mission::planNextEncounter() noexcept
{
    if (m_nextEncounter<m_encounters.size())
    {
        auto clock=m_assignedHero->base()->gameClock();
        unsigned missionDayOfPlannedEncounter = m_encounters[m_nextEncounter].first;
        unsigned daysToAdd = m_nextEncounter==0 ? missionDayOfPlannedEncounter : missionDayOfPlannedEncounter-m_encounters[m_nextEncounter-1].first;
        unsigned dayOfPlannedEncounter = clock->currentDay() + daysToAdd;
        unsigned maxMinutes = 24*60-(m_encounters.size()-1-m_nextEncounter);// minutes since midnight
        unsigned minMinutes;
        if (m_nextEncounter == 0)
            minMinutes = clock->currentHour()*60 + clock->currentMin() + 1;
        else
        {
            if (daysToAdd == 0)
                minMinutes = m_minutesSinceMidnightOfLastEncounter + 1;
            else
                minMinutes = 0;
        }
        unsigned minutesResult = Randomizer::randomBetweenAAndB(minMinutes, maxMinutes);
        unsigned hourOfPlannedEncounter = minutesResult/60;
        unsigned minOfPlannedEncounter = minutesResult%60;
        Time timeResult={dayOfPlannedEncounter, hourOfPlannedEncounter, minOfPlannedEncounter};
        m_minutesSinceMidnightOfLastEncounter = minutesResult;

        clock->addMissionAlarm(timeResult, this);
    }
    else
        m_assignedHero->base()->gameClock()->addAlarm(m_remainingDays, new MissionEndTimerAlarm(m_assignedHero->base(),this));
}

void Mission::setLand(Land *land) noexcept
{
    m_land = land;
}

void Mission::setDifficulty(EventEnums::MissionDifficulty difficulty) noexcept
{
    m_difficulty=difficulty;
}

void Mission::setDuration(unsigned days) noexcept
{
    if (days<1)
        return;
    m_duration=days;
    m_remainingDays=days;
}

void Mission::addEncounter(MissionDay day, Encounter *encounter) noexcept
{
    m_encounters+={day,encounter};
}

QDataStream &operator<<(QDataStream &stream, const MissionDataHelper &mission) noexcept
{
    stream<<mission.land;
    stream<<static_cast<quint8>(mission.difficulty);
    stream<<static_cast<qint16>(mission.duration);
    stream<<static_cast<qint16>(mission.remainingDays);
    QVector <QPair <qint16, QString> > encounters;
    for (auto e : mission.encounters)
        encounters+={static_cast<qint16>(e.first),e.second};
    stream<<encounters;
    stream<<static_cast<qint16>(mission.nextEncounter);
    stream<<static_cast<qint16>(mission.minutesSinceMidnightOfLastEncounter);
    stream<<mission.hero;
    stream<<mission.relatedReportsIDs;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, MissionDataHelper &mission) noexcept
{
    quint8 n;
    qint16 ii;

    stream>>mission.land;

    stream>>n;
    mission.difficulty=static_cast<EventEnums::MissionDifficulty>(n);

    stream>>ii;
    mission.duration=ii;

    stream>>ii;
    mission.remainingDays=ii;

    QVector <QPair <qint16, QString> > encounters;
    stream>>encounters;
    for (auto e : encounters)
        mission.encounters+={e.first,e.second};

    stream>>ii;
    mission.nextEncounter=ii;

    stream>>ii;
    mission.minutesSinceMidnightOfLastEncounter=ii;

    stream>>mission.hero;

    stream>>mission.relatedReportsIDs;

    return stream;
}

MissionBuilder::MissionBuilder(Base *base) noexcept
    : m_base(base)
{
    m_mission=new Mission();
}

MissionBuilder::~MissionBuilder() noexcept
{
    delete m_mission;
}

Mission *MissionBuilder::getMission() noexcept
{
    qSort(m_mission->m_encounters.begin(), m_mission->m_encounters.end(), lessThanEncounterSorting);
    Mission *ret=m_mission;
    m_mission=new Mission();
    return ret;
}

Mission *MissionBuilder::generateMission(Land *land, EventEnums::MissionDifficulty difficulty) noexcept
{
    resetMission();
    setLand(land);
    setDifficulty(difficulty);
    unsigned duration=generateDuration(difficulty);
    setDuration(duration);
    m_mission->m_encounters=generateEncounters(land, difficulty, duration);
    Mission *ret=m_mission;
    m_mission=new Mission();
    return ret;
}

void MissionBuilder::resetMission() noexcept
{
    delete m_mission;
    m_mission=new Mission();
}

Mission *MissionBuilder::qobjectifyMissionData(const MissionDataHelper &mission, Base *base) noexcept
{
    Mission *r=new Mission();

    for (auto e : Game::gameInstance()->assetsPool().lands())
        if (e->name() == mission.land)
        {
            r->m_land = e;
            break;
        }
    if (r->m_land == nullptr)
        return r;
    r->m_difficulty = mission.difficulty;
    r->m_duration = mission.duration;
    r->m_remainingDays = mission.remainingDays;
    for (int i=0;i<mission.encounters.size();++i)
        for (auto e : r->m_land->encounters()->encounters())
            if (e->name() == mission.encounters[i].second)
            {
                r->m_encounters+={mission.encounters[i].first, e};
                break;
            }
    r->m_nextEncounter = mission.nextEncounter;
    r->m_minutesSinceMidnightOfLastEncounter = mission.minutesSinceMidnightOfLastEncounter;
    for (auto e : base->heroes()->heroes())
        if (e->name() == mission.hero)
        {
            r->assignHero(e);
            e->assignMission(r);
            break;
        }

    for (const auto &e : mission.relatedReportsIDs)
        for (auto &f : base->reports())
            if (f->id() == e)
            {
                r->addRelatedReport(f);
                break;
            }

    return r;
}

MissionDataHelper MissionBuilder::deqobjectifyMission(Mission *mission) noexcept
{
    if (mission == nullptr)
        return {};

    MissionDataHelper r;

    r.land = mission->land()->name();
    r.difficulty = mission->difficulty();
    r.duration = mission->fullDuration();
    r.remainingDays = mission->remainingDays();
    QVector <QPair <unsigned, QString> > encs;
    for (auto e : mission->m_encounters)
        encs+={e.first,e.second->name()};
    r.encounters = encs;
    r.nextEncounter = mission->m_nextEncounter;
    r.minutesSinceMidnightOfLastEncounter = mission->m_minutesSinceMidnightOfLastEncounter;
    r.hero = mission->assignedHero()->name();
    for (const auto &e : mission->reports())
        r.relatedReportsIDs+=e->id();

    return r;
}

void MissionBuilder::setLand(Land *land) noexcept
{
    m_mission->setLand(land);
}

void MissionBuilder::setDifficulty(EventEnums::MissionDifficulty difficulty) noexcept
{
    m_mission->setDifficulty(difficulty);
}

void MissionBuilder::setDuration(unsigned duration) noexcept
{
    m_mission->setDuration(duration);
}

void MissionBuilder::addRandomEncounter() noexcept
{
    addEncounter(Randomizer::randomBetweenAAndB(0,m_mission->fullDuration()-1),m_mission->land()->makeRandomEncounter());
}

void MissionBuilder::addEncounter(Mission::MissionDay day, Encounter *encounter) noexcept
{
    m_mission->addEncounter(day,encounter);
}

unsigned MissionBuilder::generateDuration(EventEnums::MissionDifficulty difficulty) const noexcept
{
    switch (difficulty)
    {
    case EventEnums::MD_Short:
        [[fallthrough]];
    case EventEnums::MD_Veteran:
        return Randomizer::randomBetweenAAndB(2,4);
    case EventEnums::MD_Medium:
        [[fallthrough]];
    case EventEnums::MD_Master:
        return Randomizer::randomBetweenAAndB(6,8);
    case EventEnums::MD_Long:
        [[fallthrough]];
    case EventEnums::MD_Heroic:
        return Randomizer::randomBetweenAAndB(11,17);
    case EventEnums::MD_Extreme:
        return Randomizer::randomBetweenAAndB(28,34);
    default:
        return 0;
    }
}

unsigned MissionBuilder::generateAmountOfEncountersPerDay(EventEnums::MissionDifficulty difficulty) const noexcept
{
    switch (difficulty)
    {
    case EventEnums::MD_Short:
        return Randomizer::randomBetweenAAndB(0,1);
    case EventEnums::MD_Medium:
        [[fallthrough]];
    case EventEnums::MD_Long:
        [[fallthrough]];
    case EventEnums::MD_Extreme:
        return Randomizer::randomBetweenAAndB(0,2);
    case EventEnums::MD_Veteran:
        [[fallthrough]];
    case EventEnums::MD_Master:
        return Randomizer::randomBetweenAAndB(2,3);
    case EventEnums::MD_Heroic:
        return Randomizer::randomBetweenAAndB(2,4);
    default:
        return 0;
    }
}

QVector<QPair<Mission::MissionDay, Encounter *> > MissionBuilder::generateEncounters(Land *land, EventEnums::MissionDifficulty difficulty, unsigned duration) const noexcept
{
    QVector <QPair <Mission::MissionDay, Encounter *> > r;
    for (int i=0;i<duration;++i)
    {
        unsigned am=generateAmountOfEncountersPerDay(difficulty);
        while (am--)
            r+={i,land->makeRandomEncounter()};
    }
    return r;
}

bool MissionBuilder::lessThanEncounterSorting(const QPair<Mission::MissionDay, Encounter *> &first, const QPair<Mission::MissionDay, Encounter *> &second) noexcept
{
    return first.first<second.first;
}

MissionInitializer::MissionInitializer(Base *base) noexcept
    : m_basePtr(base), m_missionBuilder(base), m_land(nullptr), m_difficulty(EventEnums::MD_END), m_hero(nullptr), m_armor(nullptr), m_weaponTool({nullptr,nullptr}), m_aetherite(0), m_energy(0), m_bm(0), m_food(0) {}

void MissionInitializer::reset() noexcept
{
    if (m_hero != nullptr)
        unprepareHero();
    m_land=nullptr;
    m_difficulty=EventEnums::MD_END;
    m_hero=nullptr;
    m_armor=nullptr;
    for (int i=0;i<Hero::amountOfWeaponToolSlots();++i)
        m_weaponTool[i]=nullptr;
    m_aetherite=0;
    m_energy=0;
    m_bm=0;
    m_food=0;
}

bool MissionInitializer::start() noexcept
{
    if (!(m_basePtr->canDecreaseAetheriteAmount(m_aetherite) && m_basePtr->canDecreaseEnergyAmount(m_energy) && m_basePtr->canDecreaseBuildingMaterialsAmount(m_bm) && m_basePtr->canDecreaseFoodSuppliesAmount(m_food)) && m_land != nullptr && m_difficulty != EventEnums::MD_END)
        return 0;

    auto &eqs=m_basePtr->availableEquipment();
    if (m_armor != nullptr)
        eqs.remove(eqs.indexOf(m_armor));
    for (int i=0;i<Hero::amountOfWeaponToolSlots();++i)
        if (m_weaponTool[i] != nullptr)
            eqs.remove(eqs.indexOf(m_weaponTool[i]));

    m_basePtr->decreaseAetheriteAmount(m_aetherite);
    m_basePtr->decreaseEnergyAmount(m_energy);
    m_basePtr->decreaseBuildingMaterialsAmount(m_bm);
    m_basePtr->decreaseFoodSuppliesAmount(m_food);

    m_hero->setCarriedAetheriteOre(m_aetherite);
    m_hero->setCarriedEnergy(m_energy);
    m_hero->setCarriedBuildingMaterials(m_bm);
    m_hero->setCarriedFoodSupplies(m_food);

    m_hero->setCurrentActivity(HeroEnums::CA_OnMission);

    Mission *m=m_missionBuilder.generateMission(m_land, m_difficulty);

    m_hero->assignMission(m);
    m->assignHero(m_hero);

    m_basePtr->startMission(m);

    reset();
    return 1;
}

void MissionInitializer::setLand(const QString &name) noexcept
{
    if (name.isEmpty())
    {
        m_land=nullptr;
        return;
    }
    auto ls=Game::gameInstance()->assetsPool().lands();
    for (auto e : ls)
        if (e->name() == name)
        {
            m_land=e;
            return;
        }
    m_land=nullptr;
}

void MissionInitializer::setDifficulty(const QString & difficulty) noexcept
{
    m_difficulty=EventEnums::fromQStringToMissionDifficultyEnum(difficulty);
}

QString MissionInitializer::difficulty() const noexcept
{
    return EventEnums::fromMissionDifficultyEnumToQString(m_difficulty);
}

void MissionInitializer::setHero(const QString &name) noexcept
{
    if (m_hero != nullptr)
        unprepareHero();
    if (name.isEmpty())
    {
        m_hero=nullptr;
        return;
    }
    auto hs=m_basePtr->heroes()->heroes();
    for (int i=0;i<hs.size();++i)
        if (hs[i]->name() == name)
        {
            m_hero=m_basePtr->heroes()->getHero(i);
            prepareHero();
            return;
        }
    m_hero=nullptr;
}

void MissionInitializer::setArmor(const QString &name) noexcept
{
    if (name.isEmpty())
    {
        if (m_armor != nullptr)
        {
            m_armor=nullptr;
            if (m_hero != nullptr)
                prepareHero();
        }
        return;
    }
    auto eqs=m_basePtr->availableEquipment();
    for (int i=0;i<eqs.size();++i)
        if (eqs[i]->name() == name)
        {
            m_armor=eqs[i];
            if (m_hero != nullptr)
                prepareHero();
            return;
        }
    if (m_armor != nullptr)
    {
        m_armor=nullptr;
        if (m_hero != nullptr)
            prepareHero();
    }
}

void MissionInitializer::setWeaponTool(const QString &name, unsigned slot) noexcept
{
    if (name.isEmpty() || slot>=Hero::amountOfWeaponToolSlots())
    {
        if (m_weaponTool[slot] != nullptr)
        {
            m_weaponTool[slot]=nullptr;
            if (m_hero != nullptr)
                prepareHero();
        }
        return;
    }
    auto eqs=m_basePtr->availableEquipment();
    for (int i=0;i<eqs.size();++i)
        if (eqs[i]->name() == name)
        {
            m_weaponTool[slot]=eqs[i];
            if (m_hero != nullptr)
                prepareHero();
            return;
        }
    if (m_weaponTool[slot] != nullptr)
    {
        m_weaponTool[slot]=nullptr;
        if (m_hero != nullptr)
            prepareHero();
    }
}

void MissionInitializer::setAetherite(unsigned amount) noexcept
{
    m_aetherite = amount;
}

void MissionInitializer::setEnergy(unsigned amount) noexcept
{
    m_energy = amount;
}

void MissionInitializer::setBuildingMaterials(unsigned amount) noexcept
{
    m_bm = amount;
}

void MissionInitializer::setFoodSupplies(unsigned amount) noexcept
{
    m_food = amount;
}

void MissionInitializer::prepareHero() noexcept
{
    m_hero->removeArmor();
    m_hero->equipArmor(m_armor);
    for (int i=0;i<Hero::amountOfWeaponToolSlots();++i)
    {
        m_hero->removeWeaponTool(i);
        m_hero->equipWeaponTool(m_weaponTool[i],i);
    }
}

void MissionInitializer::unprepareHero() noexcept
{
    m_hero->removeArmor();
    for (int i=0;i<Hero::amountOfWeaponToolSlots();++i)
        m_hero->removeWeaponTool(i);
}

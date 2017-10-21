#include "event.h"

#include "game.h"

#include <QDebug>

EventEnums::MissionLength EventEnums::fromQStringToMissionLengthEnum(const QString &missionLength) noexcept
{
    if (missionLength == "Short")
        return ML_Short;
    if (missionLength == "Medium")
        return ML_Medium;
    if (missionLength == "Long")
        return ML_Long;
    if (missionLength == "Extreme")
        return ML_Extreme;
    if (missionLength == "Veteran")
        return ML_Veteran;
    if (missionLength == "Master")
        return ML_Master;
    if (missionLength == "Heroic")
        return ML_Heroic;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->MissionLength enum conversion failed for {}",missionLength.toStdString());
}

QString EventEnums::fromMissionLengthEnumToQString(EventEnums::MissionLength missionLength) noexcept
{
    if (missionLength == ML_Short)
        return "Short";
    if (missionLength == ML_Medium)
        return "Medium";
    if (missionLength == ML_Long)
        return "Long";
    if (missionLength == ML_Extreme)
        return "Extreme";
    if (missionLength == ML_Veteran)
        return "Veteran";
    if (missionLength == ML_Master)
        return "Master";
    if (missionLength == ML_Heroic)
        return "Heroic";
    Game::gameInstance()->loggers()->mainLogger()->warn("MissionLength enum->QString conversion failed for {}",static_cast<unsigned>(missionLength));
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

QVariant Expression::evaluate(const Mercenary *context) const noexcept
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

QVector<EventReport> Event::execute(Mercenary *context) noexcept
{
    auto r = executeSpecificOps(context);
    if (!context->isDead())
    {
        if (context->isCommunicationAvailable())
            unlockDatabaseEntries(context);
        else
        {
            for (const auto &e : m_unlockedDatabaseEntries)
                context->addWaitingDBEntry(e);
        }
    }
    return r;
}

void Event::setEventText(const QString &text) noexcept
{
    m_eventText=text;
}

void Event::unlockDatabaseEntries(Mercenary *context) noexcept
{
    for (auto e : m_unlockedDatabaseEntries)
        if (!context->base()->database()->isEntryUnlocked(e, context->assignedMission()->land()->name()))
            context->base()->database()->unlockEntry(e,context->assignedMission()->land()->name());
}

MultiEvent::~MultiEvent() noexcept
{
    for (auto &e : m_eventsToExecute)
        delete e;
}

QVector<EventReport> MultiEvent::executeSpecificOps(Mercenary *context) noexcept
{
    QVector <EventReport> r={eventText()};
    for (auto e : m_eventsToExecute)
    {
        if (context!=nullptr && !context->isDead())
            r+=e->execute(context);
        else
            break;
    }
    return r;
}

QVector<EventReport> NullEventResult::executeSpecificOps(Mercenary *) noexcept
{
    return {eventText()};
}

GiveHealthEventResult::GiveHealthEventResult(const ValueRange &addedValue, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_GiveHealth, text, dbEntries), m_value(addedValue) {}

QVector<EventReport> GiveHealthEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    int am;
    if (m_value.singleValue())
        am=m_value.max().evaluate(mercenary).toInt();
    else
    {
        auto max=m_value.max().evaluate(mercenary).toInt(), min=m_value.min().evaluate(mercenary).toInt();
        am=Randomizer::randomBetweenAAndB(min, max);
    }

    if (am >= 0)
        am *= mercenary->luck();
    else
        am /= mercenary->luck();

    mercenary->changeHealth(am);

    return {eventText()};
}

GiveStressEventResult::GiveStressEventResult(const ValueRange &addedValue, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_GiveStress, text, dbEntries), m_value(addedValue) {}

QVector<EventReport> GiveStressEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    int v;
    if (m_value.singleValue())
        v=m_value.max().evaluate(mercenary).toInt();
    else
    {
        int max=m_value.max().evaluate(mercenary).toInt(), min=m_value.min().evaluate(mercenary).toInt();
        v=Randomizer::randomBetweenAAndB(min,max);
    }

    if (v >= 0)
    {
        v /= mercenary->luck();
        mercenary->increaseStress(v);
    }
    else
    {
        v *= mercenary->luck();
        mercenary->decreaseStress(-v);
    }

    return {eventText()};
}

ModifyAttributeEventResult::ModifyAttributeEventResult(const AttributeModificationHelper &modification, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_ModifyAttribute, text, dbEntries), m_modification(modification) {}

QVector<EventReport> ModifyAttributeEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    QVariant val;
    if (m_modification.expressionRange.singleValue())
        val=m_modification.expressionRange.max().evaluate(mercenary);
    else
    {
        QVariant min=m_modification.expressionRange.min().evaluate(mercenary);
        QVariant max=m_modification.expressionRange.max().evaluate(mercenary);

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
        durr=m_modification.durationRange.max().evaluate(mercenary).toInt();
    else
    {
        int durMin=m_modification.durationRange.min().evaluate(mercenary).toInt();
        int durMax=m_modification.durationRange.max().evaluate(mercenary).toInt();

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

    mercenary->addAttributeModification(new AttributeModification({m_modification.attribute,m_modification.type,val,durr}));

    return {eventText()};
}

QVector<EventReport> KillMercenaryEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    mercenary->die();

    return {eventText()};
}

QVector<EventReport> AddEquipmentEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (m_equipmentToAdd->type()==EquipmentEnums::T_Armor)
    {
        if (mercenary->armor()==nullptr)
            mercenary->equipArmor(m_equipmentToAdd);
        else
            mercenary->addCarriedEquipment(m_equipmentToAdd);
    }
    else
    {
        bool ok=0;
        for (int i=0;i<mercenary->amountOfWeaponToolSlots();++i)
            if (mercenary->weaponTool(i)==nullptr)
            {
                mercenary->equipWeaponTool(m_equipmentToAdd,i);
                ok=1;
                break;
            }
        if (!ok)
            mercenary->addCarriedEquipment(m_equipmentToAdd);
    }

    return {eventText()};
}

AddEquipmentRandomEventResult::AddEquipmentRandomEventResult(ValueRange tier, int equipmentTypeFlags, QString text, const QVector<QString> &dbEntries) noexcept
    : AddEquipmentEventResult(nullptr, text, dbEntries), m_tier(tier), m_eqTypes(equipmentTypeFlags) {}

QVector<EventReport> AddEquipmentRandomEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    unsigned min=m_tier.min().evaluate(mercenary).toUInt(), max=m_tier.max().evaluate(mercenary).toUInt();
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

    return AddEquipmentEventResult::executeSpecificOps(mercenary);
}

QVector<EventReport> RemoveEquipmentEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (m_equipmentType==EquipmentEnums::T_Armor)
        mercenary->unequipArmor();
    else
        mercenary->unequipWeaponTool(m_equipmentSlot);

    return {eventText()};
}

GiveResourceEventResult::GiveResourceEventResult(BaseEnums::Resource resource, const ValueRange &amount, QString text, const QVector<QString> &dbEntries) noexcept
    : ActionEvent(EventEnums::A_GiveResource, text, dbEntries), m_resource(resource), m_amount(amount) {}

QVector<EventReport> GiveResourceEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    int am;
    if (m_amount.singleValue())
        am=m_amount.max().evaluate(mercenary).toInt();
    else
    {
        int max=m_amount.max().evaluate(mercenary).toInt(), min=m_amount.min().evaluate(mercenary).toInt();
        am=Randomizer::randomBetweenAAndB(min,max);
    }
    if (am >= 0)
        am *= mercenary->luck();
    else
        am /= mercenary->luck();
    int cam;

    switch (m_resource)
    {
    case BaseEnums::R_AetheriteOre:
        cam=mercenary->carriedAetheriteOre();
        if (cam > -am)
            mercenary->setCarriedAetheriteOre(cam+am);
        else
            mercenary->setCarriedAetheriteOre(0);
        break;
    case BaseEnums::R_BuildingMaterials:
        cam=mercenary->carriedBuildingMaterials();
        if (cam > -am)
            mercenary->setCarriedBuildingMaterials(cam+am);
        else
            mercenary->setCarriedBuildingMaterials(0);
        break;
    case BaseEnums::R_Energy:
        cam=mercenary->carriedEnergy();
        if (cam > -am)
            mercenary->setCarriedEnergy(cam+am);
        else
            mercenary->setCarriedEnergy(0);
        break;
    case BaseEnums::R_FoodSupplies:
        cam=mercenary->carriedFoodSupplies();
        if (cam > -am)
            mercenary->setCarriedFoodSupplies(cam+am);
        else
            mercenary->setCarriedFoodSupplies(0);
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

QVector<EventReport> NoSignalEventResult::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (m_durationInDays.singleValue())
        mercenary->setNoSignalDaysRemaining(m_durationInDays.max().evaluate(mercenary).toInt());
    else
    {
        int max=m_durationInDays.max().evaluate(mercenary).toInt(), min=m_durationInDays.min().evaluate(mercenary).toInt();
        mercenary->setNoSignalDaysRemaining(Randomizer::randomBetweenAAndB(min,max));
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

PossibilityEvent::PossibilityEvent(Chance chance, Event *event, QString text, const QVector<QString> &dbEntries) noexcept
    : Event(EventEnums::T_Possibility, text, dbEntries), m_chance(chance), m_event(event) {}

PossibilityEvent::~PossibilityEvent() noexcept
{
    delete m_event;
}

QVector<EventReport> PossibilityEvent::executeSpecificOps(Mercenary *mercenary) noexcept
{
    if (mercenary==nullptr || m_event==nullptr)
        return {};

    if (static_cast<unsigned>(m_chance)>=Randomizer::randomBetweenAAndB(1,100))
        return QVector<EventReport>{eventText()} + m_event->execute(mercenary);
    return {eventText()};
}

Report::Report(EventEnums::ReportType type, const Time &time) noexcept
    : m_reportType(type), m_time(time) {}

EncounterReport::EncounterReport(const QString &mercenaryArt, const QVector<EventReport> &events, const Time &time) noexcept
    : Report(EventEnums::RT_Encounter, time), m_mercenaryArt(mercenaryArt), m_events(events) {}

QString EncounterReport::text() const noexcept
{
    QString r;
    for (const auto &e : m_events)
        r+=e+"\n";
    return r;
}

BuildingUpgradeReport::BuildingUpgradeReport(BaseEnums::Building building, unsigned level, const Time &time) noexcept
    : Report(EventEnums::RT_BuildingUpgrade, time),
      m_buildingArt("qrc:/graphics/Buildings/"+Global::alterNormalTextToInternal(BaseEnums::fromBuildingEnumToQString(building))+".png"),
      m_building(building), m_level(level) {}

QString BuildingUpgradeReport::text() const noexcept
{
    return BaseEnums::fromBuildingEnumToQString(m_building)+" has been upgraded to level "+QString::number(m_level)+".";
}

MercenaryArrivalReport::MercenaryArrivalReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept
    : Report(EventEnums::RT_MercenaryArrival, time), m_mercenaryArt(mercenaryArt), m_name(mercenaryName) {}

QString MercenaryArrivalReport::text() const noexcept
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

DesertionReport::DesertionReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_Desertion, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString DesertionReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" is missing! The room in barracks is empty and one of the shuttles in the docking station disappeared!";
}

HungerReport::HungerReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_Hunger, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString HungerReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" hasn't got daily food ration!";
}

NoSalaryReport::NoSalaryReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_NoSalary, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString NoSalaryReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" hadn't been paid this week.";
}

MissionEndReport::MissionEndReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept
    : Report(EventEnums::RT_MissionEnd, time), m_mercenaryArt(mercenaryArt), m_name(name) {}

QString MissionEndReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_name)+" has successfully returned to the base.";
}

TrainingCompletionReport::TrainingCompletionReport(const QString &mercenaryArt, const QString &mercenaryName, BaseEnums::Building building, const Time &time) noexcept
    : Report(EventEnums::RT_MissionEnd, time), m_mercenaryArt(mercenaryArt), m_mercenaryName(mercenaryName), m_building(building) {}

QString TrainingCompletionReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_mercenaryName)+" has finished training in "+BaseEnums::fromBuildingEnumToQString(m_building)+".";
}

SignalLostReport::SignalLostReport(const QString &mercenaryArt, const QString &mercenaryName, const QString &landName, const Time &time) noexcept
    : Report(EventEnums::RT_SignalLost, time), m_mercenaryArt(mercenaryArt), m_mercenaryName(mercenaryName), m_landName(landName) {}

QString SignalLostReport::text() const noexcept
{
    return "We've lost connection with "+Game::gameInstance()->tr(m_mercenaryName)+", who is exploring "+m_landName+".";
}

SignalRetrievedReport::SignalRetrievedReport(const QString &mercenaryArt, const QString &landName, const Time &time) noexcept
    : Report(EventEnums::RT_SignalRetrieved, time), m_mercenaryArt(mercenaryArt), m_landName(landName) {}

QString SignalRetrievedReport::text() const noexcept
{
    return "Finally I can hear you clearly.";
}

MissionStartReport::MissionStartReport(const QString &mercenaryArt, int stress, int stressLimit, const Time &time) noexcept
    : Report(EventEnums::RT_MissionStart, time), m_mercenaryArt(mercenaryArt), m_stress(stress), m_stressLimit(stressLimit) {}

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

MercenaryDeathReport::MercenaryDeathReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept
    : Report(EventEnums::RT_MercenaryDeath, time), m_mercenaryArt(mercenaryArt), m_mercenaryName(mercenaryName) {}

QString MercenaryDeathReport::text() const noexcept
{
    return Game::gameInstance()->tr(m_mercenaryName)+" has passed away.";
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

Encounter::Encounter(const QString &name, Event *rootEvent, unsigned probability) noexcept
    : m_name(name), m_rootEvent(rootEvent), m_probability(probability) {}

EncounterReport *Encounter::execute(Mercenary *mercenary, const Time &currentTime) const noexcept
{
    auto b = mercenary->base();
    auto reps = m_rootEvent->execute(mercenary);
    for (int i=0;i<reps.size();)
    {
        if (reps[i].isEmpty())
            reps.remove(i);
        else
            ++i;
    }
    if (!b->mercenaries()->mercenaries().contains(mercenary))//TODO probably remove
        return static_cast<EncounterReport *>(static_cast<Report *>(new NullReport));//mercenary died during encounter
    return new EncounterReport{mercenary->pathToArt(), reps, currentTime};
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

    auto r=new Encounter("",nullptr,0);

    unsigned amount = m_encounters->encounters().size();
    unsigned probs[amount];
    probs[0] = m_encounters->encounters()[0]->probability();
    for (int i=1;i<amount;++i)
        probs[i] = probs[i-1] + m_encounters->encounters()[i]->probability();

    unsigned resultProb = Randomizer::randomBetweenAAndB(1, probs[amount-1]);
    unsigned resultEnc = amount-1;
    for (int i=0;i<amount-1;++i)
        if (resultProb <= probs[i])
        {
            resultEnc = i;
            break;
        }
    *r=*(m_encounters->encounters()[resultEnc]);
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

void Mission::handleNewDay() noexcept
{
    ++m_daysSpent;
}

void Mission::assignMercenary(Mercenary *mercenary) noexcept
{
    m_assignedMercenary=mercenary;
}

void Mission::start() noexcept
{
    m_assignedMercenary->base()->addReport(new UnifiedReport(new MissionStartReport(m_assignedMercenary->pathToArt(), m_assignedMercenary->stress(), m_assignedMercenary->stressLimit(), m_assignedMercenary->base()->gameClock()->currentTime())));
    m_assignedMercenary->base()->registerLatestReportInMission(this);
    planEverything();

    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Mission started: (mercenary: {}, length: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString(), EventEnums::fromMissionLengthEnumToQString(m_length).toStdString());
    for (const auto &e : m_encounters)
        Game::gameInstance()->loggers()->missionsLogger()->trace("Day {}: {}",e.first,e.second->name().toStdString());
    Game::gameInstance()->loggers()->missionsLogger()->trace("Mission ends in {}",remainingDays());
}

EncounterReport *Mission::doEncounter(const Time &now) noexcept
{
    m_timeOfCurrentEncounter = now;

    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Doing encounter: {} (mercenary: {})",now.toQString().toStdString(),m_encounters[m_nextEncounter].second->name().toStdString(), m_assignedMercenary->name().toStdString());

    return m_encounters[m_nextEncounter++].second->execute(m_assignedMercenary, now);
}

void Mission::end() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Ending mission (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->returnToBase();
}

void Mission::forceEndSuccessfully() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Forcing mission end (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    auto b=m_assignedMercenary->base();
    end();
    b->removeMission(this);
}

void Mission::forceEndSilently() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Forcing mission end silently (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
}

void Mission::forceEndBecauseOfDeath() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Forcing mission end because of death or sth like that (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    m_assignedMercenary->assignMission(nullptr);
    m_assignedMercenary->base()->removeMission(this);
}

void Mission::abort() noexcept
{
    Game::gameInstance()->loggers()->missionsLogger()->trace("[{}] Aborting mission (mercenary: {})",m_assignedMercenary->base()->gameClock()->currentTime().toQString().toStdString(), m_assignedMercenary->name().toStdString());

    m_assignedMercenary->base()->gameClock()->removeAlarmsConnectedWithMission(this);
    m_assignedMercenary->assignMission(nullptr);
    auto b=m_assignedMercenary->base();
    m_assignedMercenary->die(1,0);
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
    : m_land(nullptr), m_length(EventEnums::ML_END), m_duration(1), m_daysSpent(0), m_nextEncounter(0), m_minutesSinceMidnightOfLastEncounter(-1), m_assignedMercenary(nullptr), m_preparedRelatedReport(nullptr) {}

void Mission::planEverything() noexcept
{
    planAllEncounters();
    planEnd();
}

void Mission::planAllEncounters() noexcept
{
    auto clock=m_assignedMercenary->base()->gameClock();
    for (int i=0;i<m_encounters.size();++i)
    {
        unsigned missionDayOfPlannedEncounter = m_encounters[i].first;
        unsigned daysToAdd = i==0 ? missionDayOfPlannedEncounter : missionDayOfPlannedEncounter-m_encounters[0].first;
        unsigned dayOfPlannedEncounter = clock->currentDay() + daysToAdd;
        unsigned maxMinutes = 24*60-(m_encounters.size()-1-i);// minutes since midnight
        unsigned minMinutes;
        if (i == 0)
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
}

void Mission::planEnd() noexcept
{
    m_assignedMercenary->base()->gameClock()->addAlarm(m_duration, new MissionEndTimerAlarm(m_assignedMercenary->base(),this));
}

void Mission::setLand(Land *land) noexcept
{
    m_land = land;
}

void Mission::setLength(EventEnums::MissionLength length) noexcept
{
    m_length=length;
}

void Mission::setDuration(unsigned days) noexcept
{
    if (days<1)
        return;
    m_duration=days;
    m_daysSpent=0;
}

void Mission::addEncounter(MissionDay day, Encounter *encounter) noexcept
{
    m_encounters+={day,encounter};
}

QDataStream &operator<<(QDataStream &stream, const MissionDataHelper &mission) noexcept
{
    stream<<mission.land;
    stream<<static_cast<quint8>(mission.length);
    stream<<static_cast<qint16>(mission.duration);
    stream<<static_cast<qint16>(mission.daysSpent);
    QVector <QPair <qint16, QString> > encounters;
    for (auto e : mission.encounters)
        encounters+={static_cast<qint16>(e.first),e.second};
    stream<<encounters;
    stream<<static_cast<qint16>(mission.nextEncounter);
    stream<<static_cast<qint16>(mission.minutesSinceMidnightOfLastEncounter);
    stream<<mission.mercenary;
    stream<<mission.relatedReportsIDs;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, MissionDataHelper &mission) noexcept
{
    quint8 n;
    qint16 ii;

    stream>>mission.land;

    stream>>n;
    mission.length=static_cast<EventEnums::MissionLength>(n);

    stream>>ii;
    mission.duration=ii;

    stream>>ii;
    mission.daysSpent=ii;

    QVector <QPair <qint16, QString> > encounters;
    stream>>encounters;
    for (auto e : encounters)
        mission.encounters+={e.first,e.second};

    stream>>ii;
    mission.nextEncounter=ii;

    stream>>ii;
    mission.minutesSinceMidnightOfLastEncounter=ii;

    stream>>mission.mercenary;

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

Mission *MissionBuilder::generateMission(Land *land, EventEnums::MissionLength length) noexcept
{
    resetMission();
    setLand(land);
    setLength(length);
    unsigned duration=generateDuration(length);
    setDuration(duration);
    m_mission->m_encounters=generateEncounters(land, length, duration);
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
    r->m_length = mission.length;
    r->m_duration = mission.duration;
    r->m_daysSpent = mission.daysSpent;
    for (int i=0;i<mission.encounters.size();++i)
        for (auto e : r->m_land->encounters()->encounters())
            if (e->name() == mission.encounters[i].second)
            {
                r->m_encounters+={mission.encounters[i].first, e};
                break;
            }
    r->m_nextEncounter = mission.nextEncounter;
    r->m_minutesSinceMidnightOfLastEncounter = mission.minutesSinceMidnightOfLastEncounter;
    for (auto e : base->mercenaries()->mercenaries())
        if (e->name() == mission.mercenary)
        {
            r->assignMercenary(e);
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
    r.length = mission->length();
    r.duration = mission->fullDuration();
    r.daysSpent = mission->daysSpent();
    QVector <QPair <unsigned, QString> > encs;
    for (auto e : mission->m_encounters)
        encs+={e.first,e.second->name()};
    r.encounters = encs;
    r.nextEncounter = mission->m_nextEncounter;
    r.minutesSinceMidnightOfLastEncounter = mission->m_minutesSinceMidnightOfLastEncounter;
    r.mercenary = mission->assignedMercenary()->name();
    for (const auto &e : mission->reports())
        r.relatedReportsIDs+=e->id();

    return r;
}

void MissionBuilder::setLand(Land *land) noexcept
{
    m_mission->setLand(land);
}

void MissionBuilder::setLength(EventEnums::MissionLength length) noexcept
{
    m_mission->setLength(length);
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

unsigned MissionBuilder::generateDuration(EventEnums::MissionLength length) const noexcept
{
    switch (length)
    {
    case EventEnums::ML_Short:
        [[fallthrough]];
    case EventEnums::ML_Veteran:
        return Randomizer::randomBetweenAAndB(2,4);
    case EventEnums::ML_Medium:
        [[fallthrough]];
    case EventEnums::ML_Master:
        return Randomizer::randomBetweenAAndB(6,8);
    case EventEnums::ML_Long:
        [[fallthrough]];
    case EventEnums::ML_Heroic:
        return Randomizer::randomBetweenAAndB(11,17);
    case EventEnums::ML_Extreme:
        return Randomizer::randomBetweenAAndB(28,34);
    default:
        return 0;
    }
}

unsigned MissionBuilder::generateAmountOfEncountersPerDay(EventEnums::MissionLength length) const noexcept
{
    switch (length)
    {
    case EventEnums::ML_Short:
        return Randomizer::randomBetweenAAndB(0,3,Randomizer::RandomizationMethods::bentRand);
    case EventEnums::ML_Medium:
        [[fallthrough]];
    case EventEnums::ML_Long:
        [[fallthrough]];
    case EventEnums::ML_Extreme:
        return Randomizer::randomBetweenAAndB(0,4,Randomizer::RandomizationMethods::bentRand);
    case EventEnums::ML_Veteran:
        [[fallthrough]];
    case EventEnums::ML_Master:
        return Randomizer::randomBetweenAAndB(2,5,Randomizer::RandomizationMethods::bentRand);
    case EventEnums::ML_Heroic:
        return Randomizer::randomBetweenAAndB(2,6,Randomizer::RandomizationMethods::bentRand);
    default:
        return 0;
    }
}

QVector<QPair<Mission::MissionDay, Encounter *> > MissionBuilder::generateEncounters(Land *land, EventEnums::MissionLength length, unsigned duration) const noexcept
{
    QVector <QPair <Mission::MissionDay, Encounter *> > r;
    for (int i=0;i<duration;++i)
    {
        unsigned am=generateAmountOfEncountersPerDay(length);
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
    : m_basePtr(base), m_missionBuilder(base), m_land(nullptr), m_length(EventEnums::ML_END), m_mercenary(nullptr), m_armor(nullptr), m_weaponTool({nullptr,nullptr}), m_aetherite(0), m_energy(0), m_bm(0), m_food(0) {}

void MissionInitializer::reset() noexcept
{
    if (m_mercenary != nullptr)
        unprepareMercenary();
    m_land=nullptr;
    m_length=EventEnums::ML_END;
    m_mercenary=nullptr;
    m_armor=nullptr;
    for (int i=0;i<Mercenary::amountOfWeaponToolSlots();++i)
        m_weaponTool[i]=nullptr;
    m_aetherite=0;
    m_energy=0;
    m_bm=0;
    m_food=0;
}

bool MissionInitializer::start() noexcept
{
    if (!(m_basePtr->canDecreaseAetheriteAmount(m_aetherite) && m_basePtr->canDecreaseEnergyAmount(m_energy) && m_basePtr->canDecreaseBuildingMaterialsAmount(m_bm) && m_basePtr->canDecreaseFoodSuppliesAmount(m_food)) && m_land != nullptr && m_length != EventEnums::ML_END)
        return 0;

    auto &eqs=m_basePtr->availableEquipment();
    if (m_armor != nullptr)
        eqs.remove(eqs.indexOf(m_armor));
    for (int i=0;i<Mercenary::amountOfWeaponToolSlots();++i)
        if (m_weaponTool[i] != nullptr)
            eqs.remove(eqs.indexOf(m_weaponTool[i]));

    m_basePtr->decreaseAetheriteAmount(m_aetherite);
    m_basePtr->decreaseEnergyAmount(m_energy);
    m_basePtr->decreaseBuildingMaterialsAmount(m_bm);
    m_basePtr->decreaseFoodSuppliesAmount(m_food);

    m_mercenary->setCarriedAetheriteOre(m_aetherite);
    m_mercenary->setCarriedEnergy(m_energy);
    m_mercenary->setCarriedBuildingMaterials(m_bm);
    m_mercenary->setCarriedFoodSupplies(m_food);

    m_mercenary->setCurrentActivity(MercenaryEnums::CA_OnMission);

    Mission *m=m_missionBuilder.generateMission(m_land, m_length);

    m_mercenary->assignMission(m);
    m->assignMercenary(m_mercenary);

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

void MissionInitializer::setLength(const QString & length) noexcept
{
    m_length=EventEnums::fromQStringToMissionLengthEnum(length);
}

QString MissionInitializer::length() const noexcept
{
    return EventEnums::fromMissionLengthEnumToQString(m_length);
}

void MissionInitializer::setMercenary(const QString &name) noexcept
{
    if (m_mercenary != nullptr)
        unprepareMercenary();
    if (name.isEmpty())
    {
        m_mercenary=nullptr;
        return;
    }
    auto hs=m_basePtr->mercenaries()->mercenaries();
    for (int i=0;i<hs.size();++i)
        if (hs[i]->name() == name)
        {
            m_mercenary=m_basePtr->mercenaries()->getMercenary(i);
            prepareMercenary();
            return;
        }
    m_mercenary=nullptr;
}

void MissionInitializer::setArmor(const QString &name) noexcept
{
    if (name.isEmpty())
    {
        if (m_armor != nullptr)
        {
            m_armor=nullptr;
            if (m_mercenary != nullptr)
                prepareMercenary();
        }
        return;
    }
    auto eqs=m_basePtr->availableEquipment();
    for (int i=0;i<eqs.size();++i)
        if (eqs[i]->name() == name)
        {
            m_armor=eqs[i];
            if (m_mercenary != nullptr)
                prepareMercenary();
            return;
        }
    if (m_armor != nullptr)
    {
        m_armor=nullptr;
        if (m_mercenary != nullptr)
            prepareMercenary();
    }
}

void MissionInitializer::setWeaponTool(const QString &name, unsigned slot) noexcept
{
    if (name.isEmpty() || slot>=Mercenary::amountOfWeaponToolSlots())
    {
        if (m_weaponTool[slot] != nullptr)
        {
            m_weaponTool[slot]=nullptr;
            if (m_mercenary != nullptr)
                prepareMercenary();
        }
        return;
    }
    auto eqs=m_basePtr->availableEquipment();
    for (int i=0;i<eqs.size();++i)
        if (eqs[i]->name() == name)
        {
            m_weaponTool[slot]=eqs[i];
            if (m_mercenary != nullptr)
                prepareMercenary();
            return;
        }
    if (m_weaponTool[slot] != nullptr)
    {
        m_weaponTool[slot]=nullptr;
        if (m_mercenary != nullptr)
            prepareMercenary();
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

void MissionInitializer::prepareMercenary() noexcept
{
    m_mercenary->removeArmor();
    m_mercenary->equipArmor(m_armor);
    for (int i=0;i<Mercenary::amountOfWeaponToolSlots();++i)
    {
        m_mercenary->removeWeaponTool(i);
        m_mercenary->equipWeaponTool(m_weaponTool[i],i);
    }
}

void MissionInitializer::unprepareMercenary() noexcept
{
    m_mercenary->removeArmor();
    for (int i=0;i<Mercenary::amountOfWeaponToolSlots();++i)
        m_mercenary->removeWeaponTool(i);
}

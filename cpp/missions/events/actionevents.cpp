#include "actionevents.h"

#include <QVariant>
#include <QString>
#include <QVector>

#include "equipment/equipment.h"
#include "general/game.h"
#include "general/randomizer.h"
#include "mercenaries/mercenary.h"
#include "reports/missionreports.h"

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

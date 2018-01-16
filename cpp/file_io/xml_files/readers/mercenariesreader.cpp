#include "mercenariesreader.h"

#include "equipment/equipment.h"
#include "general/game.h"
#include "general/globalutilities.h"
#include "logging/loggersprovider.h"
#include "mercenaries/mercenary.h"

QList <QString> MercenariesReader::getMercenariesNamesList(const QString &pathToMercenariesDir) noexcept
{
    if (!QDir(pathToMercenariesDir).exists())
        qCritical()<<"Directory "+pathToMercenariesDir+" doesn't exist.";

    auto r = QDir(pathToMercenariesDir).entryList({"*.xml"});
    for (int i=0;i < r.size();++i)
        r[i].remove(r[i].size()-4,4);
    if (r.isEmpty())
        qCritical("No mercenaries detected.");
    return r;
}

Mercenary *MercenariesReader::getMercenary(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    MercenaryBuilder hB;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="mercenary")
        {
            QXmlStreamAttributes attrs = m_xmlReader->attributes();
            hB.setName(attrs.value("name").toString());

            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="attributes")
                {
                    attrs = m_xmlReader->attributes();
                    hB.setCombatEffectiveness(attrs.value("combatEffectiveness").toInt());
                    hB.setProficiency(attrs.value("proficiency").toInt());
                    hB.setCleverness(attrs.value("cleverness").toInt());
                    hB.setLuck(GlobalUtilities::roundDouble(attrs.value("luck").toFloat(),2));
                    hB.setHealth(attrs.value("health").toInt());
                    hB.setHealthLimit(attrs.value("healthLimit").toInt());
                    hB.setDailyHealthRecovery(attrs.value("dailyHealthRecovery").toInt());
                    hB.setStress(attrs.value("stress").toInt());
                    hB.setStressResistance(GlobalUtilities::roundDouble(attrs.value("stressResistance").toFloat(),2));
                    hB.setStressLimit(attrs.value("stressLimit").toInt());
                    hB.setStressBorder(attrs.value("stressBorder").toInt());
                    hB.setDailyStressRecovery(attrs.value("dailyStressRecovery").toInt());
                    hB.setSalary(attrs.value("salary").toInt());
                    hB.setDailyFoodConsumption(attrs.value("dailyFoodConsumption").toInt());
                    hB.setNature(MercenaryEnums::fromQStringToNatureEnum(attrs.value("nature").toString()));
                    hB.setProfession(MercenaryEnums::fromQStringToProfessionEnum(attrs.value("profession").toString()));

                    m_xmlReader->skipCurrentElement();
                }
                else if (m_xmlReader->name()=="sbeList")
                {
                    QVector <MercenaryStressBorderEffect> sbes;
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="sbe")
                            sbes.push_back({MercenaryEnums::fromQStringToStressBorderEffectEnum(m_xmlReader->readElementText())});
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    hB.setStressBorderEffects(sbes);
                }
                else if (m_xmlReader->name()=="equipment")
                {
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="armor")
                        {
                            attrs = m_xmlReader->attributes();
                            for (int i=0;i < Game::gameInstance()->assetsPool().equipment().size();++i)
                                if (Game::gameInstance()->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                                {
                                    hB.setAndEquipArmor(Game::gameInstance()->assetsPool().makeEquipmentAtPos(i));
                                    break;
                                }
                        }
                        else if (m_xmlReader->name()=="weaponTool")
                        {
                            attrs = m_xmlReader->attributes();
                            for (int i=0;i < Game::gameInstance()->assetsPool().equipment().size();++i)
                                if (Game::gameInstance()->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                                {
                                    hB.setAndEquipWeaponTool(Game::gameInstance()->assetsPool().makeEquipmentAtPos(i),attrs.value("slot").toInt());
                                    break;
                                }
                        }
                        m_xmlReader->skipCurrentElement();
                    }
                }
                else if (m_xmlReader->name()=="additionalData")
                {
                    attrs = m_xmlReader->attributes();

                    hB.setIsDead(static_cast<bool>(attrs.value("dead").toInt()));
                    hB.setIsDead(static_cast<bool>(attrs.value("stressBorderEffectActive").toInt()));

                    hB.setNoSignalDaysRemaining(attrs.value("noSigDaysRem").toInt());

                    m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return nullptr;
    }
    return hB.getMercenary();
}

QVector < Equipment *> MercenariesReader::getEquipment(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QVector <Equipment *> r;
    EquipmentBuilder eqB;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="equipmentList")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="weaponTool")
                {
                    eqB.setType(EquipmentEnums::T_WeaponTool);

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    eqB.setName(attrs.value("name").toString());
                    eqB.setTier(attrs.value("tier").toUInt());

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="effects")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="bonus")
                                {
                                    attrs = m_xmlReader->attributes();
                                    if (attrs.value("varName")=="combatEffectiveness")
                                        eqB.setCombatEffectivenessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="proficiency")
                                        eqB.setProficiencyBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="cleverness")
                                        eqB.setClevernessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="luck")
                                        eqB.setLuckBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="healthLimit")
                                        eqB.setHealthLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyHealthRecovery")
                                        eqB.setDailyHealthRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressResistance")
                                        eqB.setStressResistanceBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="stressLimit")
                                        eqB.setStressLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressBorder")
                                        eqB.setStressBorderBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyStressRecovery")
                                        eqB.setDailyStressRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="salary")
                                        eqB.setSalaryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyFoodConsumption")
                                        eqB.setDailyFoodConsumptionBonus(attrs.value("value").toInt());
                                    m_xmlReader->skipCurrentElement();
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.push_back(eqB.getEquipment());
                }
                else if (m_xmlReader->name()=="armor")
                {
                    eqB.setType(EquipmentEnums::T_Armor);

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    eqB.setName(attrs.value("name").toString());
                    eqB.setTier(attrs.value("tier").toUInt());

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="effects")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="bonus")
                                {
                                    attrs = m_xmlReader->attributes();
                                    if (attrs.value("varName")=="combatEffectiveness")
                                        eqB.setCombatEffectivenessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="proficiency")
                                        eqB.setProficiencyBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="cleverness")
                                        eqB.setClevernessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="luck")
                                        eqB.setLuckBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="healthLimit")
                                        eqB.setHealthLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyHealthRecovery")
                                        eqB.setDailyHealthRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressResistance")
                                        eqB.setStressResistanceBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="stressLimit")
                                        eqB.setStressLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressBorder")
                                        eqB.setStressBorderBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyStressRecovery")
                                        eqB.setDailyStressRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="salary")
                                        eqB.setSalaryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyFoodConsumption")
                                        eqB.setDailyFoodConsumptionBonus(attrs.value("value").toInt());
                                    m_xmlReader->skipCurrentElement();
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.push_back(eqB.getEquipment());
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        for (int i=0;i < r.size();++i)
            delete r[i];
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }

    LoggersProvider::xmlLogger()->info("Loaded equipment at {}. Entries: {}", path.toStdString(), r.size());

    return r;
}

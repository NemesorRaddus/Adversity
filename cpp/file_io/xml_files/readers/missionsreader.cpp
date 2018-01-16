#include "missionsreader.h"

#include "database/database.h"
#include "general/game.h"
#include "logging/loggersprovider.h"
#include "missions/encounter.h"
#include "missions/events/actionevents.h"
#include "missions/events/checkevents.h"
#include "missions/events/event.h"
#include "missions/events/otherevents.h"
#include "missions/events/value_scripts/valuerange.h"
#include "missions/land.h"

QList <QString> MissionsReader::getDatabaseFilesList(const QString &pathToDBDir) noexcept
{
    if (!QDir(pathToDBDir).exists())
        qCritical()<<"Directory "+pathToDBDir+" doesn't exist.";

    auto r = QDir(pathToDBDir).entryList({}, QDir::Files | QDir::NoDotAndDotDot);
    if (r.isEmpty())
        qCritical("No db files detected.");
    return r;
}

QVector <DatabaseEntry> MissionsReader::getDatabaseEntries(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QVector <DatabaseEntry> r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="dbEntries")
        {
            auto attrs = m_xmlReader->attributes();
            DatabaseEnums::EntryType entriesType = DatabaseEnums::fromQStringToEntryTypeEnum(attrs.value("type").toString());

            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="entry")
                {
                    QString name, description;
                    QVector <QString> inhs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name() == "name")
                            name = m_xmlReader->readElementText();
                        else if (m_xmlReader->name() == "description")
                            description = m_xmlReader->readElementText();
                        else if (m_xmlReader->name() == "inhabitancies")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name() == "inhabitancy")
                                    inhs+=m_xmlReader->readElementText();
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r += {name,{description,entriesType,inhs}};
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->skipCurrentElement();
    }

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }

    LoggersProvider::xmlLogger()->info("Loaded db entries at {}. Entries: {}", path.toStdString(), r.size());

    return r;
}

QList <QString> MissionsReader::getLandsNamesList(const QString &pathToLandsDir) noexcept
{
    if (!QDir(pathToLandsDir).exists())
        qCritical()<<"Directory "+pathToLandsDir+" doesn't exist.";

    auto r = QDir(pathToLandsDir).entryList({}, QDir::Dirs | QDir::NoDotAndDotDot);
    if (r.isEmpty())
        qCritical("No lands detected.");
    return r;
}

LandInfo MissionsReader::getLandInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    LandInfo r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="land")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="name")
                    r.name = m_xmlReader->readElementText();
                else if (m_xmlReader->name()=="description")
                    r.description = m_xmlReader->readElementText();
                else if (m_xmlReader->name()=="position")
                {
                    auto attrs = m_xmlReader->attributes();
                    r.position={attrs.value("x").toInt(), attrs.value("y").toInt()};
                    m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Parse error");
    }

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }

    LoggersProvider::xmlLogger()->info("Loaded land at {}.", path.toStdString());

    return r;
}

EncountersContainer *MissionsReader::getEncounters(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return nullptr;
    }

    EncountersContainer *r = new EncountersContainer;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="encounters")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="encounter")
                {
                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    QString name = attrs.value("name").toString();
                    Event *rootev = getEvent(0);
                    unsigned probability = attrs.hasAttribute("probability") ? attrs.value("probability").toUInt() : 1;

                    if (m_xmlReader->hasError())
                    {
                        qCritical()<<"Couldn't read "+path+" properly.";
                        delete r;
                        return nullptr;
                    }

                    r->addEncounter(new Encounter(name, rootev, probability));
                }
                m_xmlReader->skipCurrentElement();//encounter/*
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }

    LoggersProvider::xmlLogger()->info("Loaded encounters at {}. Entries: {}", path.toStdString(), r->encounters().size());

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        delete r;
        return nullptr;
    }
    return r;
}

Event *MissionsReader::getEvent(bool alreadyRead) noexcept
{
    Event *r = nullptr;

    QString text;
    QVector <QString> ude;

    if (alreadyRead || m_xmlReader->readNextStartElement())
    {
        if (alreadyRead || m_xmlReader->name()=="event")
        {
            QXmlStreamAttributes attrs = m_xmlReader->attributes();
            auto type = attrs.value("type").toString();

            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="text")
                {
                    text = m_xmlReader->readElementText();
                }
                else if (m_xmlReader->name()=="unlockedDBEntries")
                {
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="entry")
                        {
                            ude+=m_xmlReader->readElementText();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                }
                else
                    break;
            }

            if (type=="Multi")
            {
                if (m_xmlReader->name()=="events")
                {
                    QVector <Event *> evs;
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="event")
                        {
                            evs+=getEvent(1);
                            if (m_xmlReader->hasError())
                                return nullptr;
                        }
                    }
                    r = new MultiEvent(evs,text,ude);
                }
                m_xmlReader->skipCurrentElement();//event
            }
            else if (type=="Action")
            {
                auto subtype = attrs.value("subtype").toString();

                if (subtype=="Null")
                {
                    r = new NullEventResult(text,ude);
                }
                else if (subtype=="GiveHealth")
                {
                    if (m_xmlReader->name()=="addedValue")
                        r = new GiveHealthEventResult(parseValue(m_xmlReader->attributes().value("value").toString()),text,ude);
                    m_xmlReader->skipCurrentElement();//addedValue
                }
                else if (subtype=="GiveStress")
                {
                    if (m_xmlReader->name()=="addedValue")
                        r = new GiveStressEventResult(parseValue(m_xmlReader->attributes().value("value").toString()),text,ude);
                    m_xmlReader->skipCurrentElement();//addedValue
                }
                else if (subtype=="ModifyAttribute")
                {
                    if (m_xmlReader->name()=="modification")
                    {
                        AttributeModificationHelper mod;
                        attrs = m_xmlReader->attributes();

                        mod.attribute = MercenaryEnums::fromQStringToAttributeEnum(attrs.value("attribute").toString());
                        if (attrs.value("type").toString()=="+")
                            mod.type = AttributeModification::T_Add;
                        else if (attrs.value("type").toString()=="-")
                            mod.type = AttributeModification::T_Subtract;
                        else if (attrs.value("type").toString()=="*")
                            mod.type = AttributeModification::T_Multiply;
                        else if (attrs.value("type").toString()=="/")
                            mod.type = AttributeModification::T_Divide;
                        else if (attrs.value("type").toString()=="=")
                            mod.type = AttributeModification::T_Set;

                        mod.expressionRange = parseValue(attrs.value("value").toString());

                        mod.durationRange = parseValue(attrs.value("duration").toString());

                        r = new ModifyAttributeEventResult(mod,text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//modification
                }
                else if (subtype=="Kill")
                {
                    r = new KillMercenaryEventResult(text,ude);
                }
                else if (subtype=="AddEquipment")
                {
                    if (m_xmlReader->name()=="equipment")
                    {
                        attrs = m_xmlReader->attributes();
                        for (int i=0;i < Game::gameInstance()->assetsPool().equipment().size();++i)
                            if (Game::gameInstance()->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                            {
                                r = new AddEquipmentEventResult(Game::gameInstance()->assetsPool().makeEquipmentAtPos(i),text,ude);
                                break;
                            }
                    }
                    else if (m_xmlReader->name()=="random")
                    {
                        attrs = m_xmlReader->attributes();

                        bool allowArmor = attrs.value("armor").toString()=="true" ? true : false;
                        bool allowWeaponTool = attrs.value("weaponTool").toString()=="true" ? true : false;
                        int flags = 0;
                        if (allowArmor)
                            flags |= EquipmentEnums::T_Armor;
                        if (allowWeaponTool)
                            flags |= EquipmentEnums::T_WeaponTool;

                        r = new AddEquipmentRandomEventResult(parseValue(attrs.value("tier").toString()), flags,text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//equipment/random
                }
                else if (subtype=="RemoveEquipment")
                {
                    if (m_xmlReader->name()=="armor")
                        r = new RemoveEquipmentEventResult(EquipmentEnums::T_Armor,0,text,ude);
                    else if (m_xmlReader->name()=="weaponTool")
                    {
                        attrs = m_xmlReader->attributes();
                        r = new RemoveEquipmentEventResult(EquipmentEnums::T_WeaponTool, attrs.value("slot").toInt(),text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//armor/weaponTool
                }
                else if (subtype=="GiveResource")
                {
                    if (m_xmlReader->name()=="resource")
                    {
                        attrs = m_xmlReader->attributes();

                        r = new GiveResourceEventResult(BaseEnums::fromQStringToResourceEnum(attrs.value("type").toString()), parseValue(attrs.value("amount").toString()),text,ude);
                    }
                    else if (m_xmlReader->name()=="random")
                    {
                        attrs = m_xmlReader->attributes();

                        r = new GiveResourceRandomEventResult(parseValue(attrs.value("amount").toString()),text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//resource
                }
                else if (subtype=="NoSignal")
                {
                    if (m_xmlReader->name()=="duration")
                        r = new NoSignalEventResult(parseValue(m_xmlReader->attributes().value("duration").toString()),text,ude);
                    m_xmlReader->skipCurrentElement();//duration
                }
                else
                    m_xmlReader->skipCurrentElement();

                if (subtype != "Null" && subtype != "Kill")
                    m_xmlReader->skipCurrentElement();//event
            }
            else if (type=="Check")
            {
                auto subtype = attrs.value("subtype").toString();

                if (subtype=="Value")
                {
                    Expression cond;
                    if (m_xmlReader->name()=="condition")
                    {
                        cond={m_xmlReader->attributes().value("condition").toString()};
                        m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    CheckEventResultsBuilder resb;
                    if (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="results")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="positive")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toUInt()};
                                            resb.addPositive({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else if (m_xmlReader->name()=="negative")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toUInt()};
                                            resb.addNegative({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    r = new ValueCheckEvent(cond, resb.get(),text,ude);
                }
                else if (subtype=="Equipment")
                {
                    EquipmentEnums::Category cond;
                    if (m_xmlReader->name()=="condition")
                    {
                        cond = EquipmentEnums::fromQStringToCategoryEnum(m_xmlReader->attributes().value("condition").toString());
                        m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    CheckEventResultsBuilder resb;
                    if (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="results")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="positive")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toInt()};
                                            resb.addPositive({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else if (m_xmlReader->name()=="negative")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toInt()};
                                            resb.addNegative({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    r = new EquipmentCheckEvent(cond, resb.get(),text,ude);
                }
                m_xmlReader->skipCurrentElement();//event
            }
            else if (type=="Possibility")
            {
                if (m_xmlReader->name()=="event")
                {
                    Chance chance{m_xmlReader->attributes().value("chance").toUInt()};
                    Event *ev = getEvent(1);
                    if (m_xmlReader->hasError())
                        return nullptr;
                    r = new PossibilityEvent(chance,ev,text,ude);
                }
                m_xmlReader->skipCurrentElement();//event
            }
            else
                m_xmlReader->raiseError("Parse error");
        }
        else
            m_xmlReader->skipCurrentElement();
    }
    if (m_xmlReader->hasError())
        return nullptr;
    if (r == nullptr)
        r = new NullEventResult;
    return r;
}

ValueRange MissionsReader::parseValue(QString text) noexcept
{
    if (text.isEmpty())
        return {{"-1"}};//error

    int semcolPos = text.indexOf(';');

    char rangeok = 0;
    if (text[0]=='<')
        rangeok |= 1;
    if (text[text.size()-1]=='>')
        rangeok |= 1<<1;
    if (semcolPos!=-1 && semcolPos>1 && semcolPos < text.size()-2)
        rangeok |= 1<<2;

    if (rangeok & (1|1<<1|1<<2))
        return {text.mid(1,semcolPos-1),text.mid(semcolPos+1,text.size()-semcolPos-2)};
    else if (rangeok == 0)
        return {text};
    else
        return {{"-1"}};//error
}

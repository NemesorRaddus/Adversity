#pragma once

#include <QMap>
#include <QVector>
#include <QJSEngine>

#include "mercenary.h"
#include "equipment.h"
#include "base.h"
#include "timer.h"

#include <QDebug>

struct EventEnums
{
    enum Action
    {
        A_Null,
        A_GiveHealth,
        A_GiveStress,
        A_ModifyAttribute,
        A_KillMercenary,
        A_AddEquipment,
        A_RemoveEquipment,
        A_GiveResource,
        A_NoSignal,
        A_END
    };
    enum Check
    {
        C_ValueCheck,
        C_EquipmentCheck,
        C_END
    };
    enum Type
    {
        T_Multi,
        T_Action,
        T_Check,
        T_Possibility,
        T_END
    };
    enum MissionLength
    {
        ML_Short,
        ML_Medium,
        ML_Long,
        ML_Extreme,
        ML_Veteran,
        ML_Master,
        ML_Heroic,
        ML_END
    };
    enum ReportType
    {
        RT_Null,
        RT_Encounter,
        RT_BuildingUpgrade,
        RT_MercenaryArrival,
        RT_TradeCompletion,
        RT_EquipmentArrival,
        RT_Desertion,
        RT_Hunger,
        RT_NoSalary,
        RT_MissionEnd,
        RT_TrainingCompletion,
        RT_SignalLost,
        RT_SignalRetrieved,
        RT_MissionStart,
        RT_MercenaryDeath,
        RT_NewDBEntry,
        RT_END
    };

    static MissionLength fromQStringToMissionLengthEnum(const QString &missionLength) noexcept;
    static QString fromMissionLengthEnumToQString(MissionLength missionLength) noexcept;
};

class Expression
{
public:
    Expression() noexcept;
    Expression(const QString &expr) noexcept;
    Expression(const Expression &other) noexcept;

    inline explicit operator QString() const noexcept
    {
        return m_expr;
    }

    void set(const QString &expr) noexcept;

    bool isValid() const noexcept;

    QVariant evaluate(const Mercenary *context) const noexcept;

private:
    void validateExpr() noexcept;
    void handleEngine() noexcept;

    QString m_expr;
    bool m_isExprValid;
    QJSEngine *m_engine;
};

class ValueRange
{
public:
    ValueRange() noexcept;
    ValueRange(const Expression &min, const Expression &max) noexcept;
    ValueRange(const Expression &value) noexcept;

    inline Expression min() const noexcept
    {
        return m_min;
    }
    inline Expression max() const noexcept
    {
        return m_max;
    }

    inline bool singleValue() const noexcept
    {
        return static_cast<QString>(m_min)==static_cast<QString>(m_max);
    }

private:
    Expression m_min, m_max;
};

typedef RBoundedValue<int, 0, 100, false> Chance;

typedef QString EventReport;

class Event
{
public:
    virtual ~Event() noexcept = default;

    inline EventEnums::Type eventType() const noexcept
    {
        return m_eventType;
    }
    inline QString eventText() const noexcept
    {
        return m_eventText;
    }
    inline QVector <QString> unlockedDatabaseEntries() const noexcept
    {
        return m_unlockedDatabaseEntries;
    }

    QVector <EventReport> execute(Mercenary *context) noexcept;

protected:
    explicit Event(EventEnums::Type eventType, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : m_eventType(eventType), m_eventText(text), m_unlockedDatabaseEntries(dbEntries) {}

    void setEventText(const QString &text) noexcept;

private:
    void unlockDatabaseEntries(Mercenary *context) noexcept;
    virtual QVector <EventReport> executeSpecificOps(Mercenary *context) noexcept = 0;

    EventEnums::Type m_eventType;
    QString m_eventText;
    QVector <QString> m_unlockedDatabaseEntries;
};

class MultiEvent final : public Event
{
public:
    MultiEvent(const QVector <Event *> &events, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : Event(EventEnums::T_Multi,text,dbEntries), m_eventsToExecute(events) {}
    ~MultiEvent() noexcept;

    QVector <EventReport> executeSpecificOps(Mercenary *context) noexcept final;

private:
    QVector <Event *> m_eventsToExecute;
};

class ActionEvent : public Event
{
public:
    virtual ~ActionEvent() noexcept = default;

    virtual QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept override = 0;
    EventEnums::Action eventSubtype() const noexcept
    {
        return m_eventSubtype;
    }

protected:
    explicit ActionEvent(EventEnums::Action eventSubtype, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : Event(EventEnums::T_Action,text,dbEntries), m_eventSubtype(eventSubtype) {}

private:
    EventEnums::Action m_eventSubtype;
};

class NullEventResult final : public ActionEvent
{
public:
    NullEventResult(QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_Null,text,dbEntries) {}
    ~NullEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *) noexcept;
};

class GiveHealthEventResult final : public ActionEvent
{
public:
    explicit GiveHealthEventResult(const ValueRange &addedValue, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~GiveHealthEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    ValueRange m_value;
};

class GiveStressEventResult final : public ActionEvent
{
public:
    explicit GiveStressEventResult(const ValueRange &addedValue, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~GiveStressEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    ValueRange m_value;
};

struct AttributeModification
{
    enum Type
    {
        T_Add,
        T_Subtract,
        T_Multiply,
        T_Divide,
        T_Set,
        T_END
    };

    MercenaryEnums::Attribute attribute;
    Type type;
    QVariant value;
    int duration;
};

struct AttributeModificationHelper
{
    MercenaryEnums::Attribute attribute;
    AttributeModification::Type type;
    ValueRange expressionRange;
    ValueRange durationRange;
};

class ModifyAttributeEventResult final : public ActionEvent
{
public:
    explicit ModifyAttributeEventResult(const AttributeModificationHelper &modification, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~ModifyAttributeEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    AttributeModificationHelper m_modification;
};

class KillMercenaryEventResult final : public ActionEvent
{
public:
    KillMercenaryEventResult(QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_KillMercenary,text,dbEntries) {}
    ~KillMercenaryEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;
};

class AddEquipmentEventResult : public ActionEvent
{
public:
    explicit AddEquipmentEventResult(Equipment *equipment, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_AddEquipment,text,dbEntries), m_equipmentToAdd(equipment) {}
    virtual ~AddEquipmentEventResult() noexcept = default;

    virtual QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept override;

    Equipment *equipmentToAdd() const noexcept
    {
        return m_equipmentToAdd;
    }

protected:
    Equipment *m_equipmentToAdd;
};

class AddEquipmentRandomEventResult final : public AddEquipmentEventResult
{
public:
    AddEquipmentRandomEventResult(ValueRange tier, int equipmentTypeFlags, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~AddEquipmentRandomEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    ValueRange m_tier;
    int m_eqTypes;
};

class RemoveEquipmentEventResult final : public ActionEvent
{
public:
    explicit RemoveEquipmentEventResult(EquipmentEnums::Type type, int slot, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept
        : ActionEvent(EventEnums::A_RemoveEquipment,text,dbEntries), m_equipmentType(type), m_equipmentSlot(slot) {}
    ~RemoveEquipmentEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

    auto equipmentType() const noexcept
    {
        return m_equipmentType;
    }
    int equipmentSlot() const noexcept
    {
        return m_equipmentSlot;
    }

private:
    EquipmentEnums::Type m_equipmentType;
    int m_equipmentSlot;
};

class GiveResourceEventResult : public ActionEvent
{
public:
    explicit GiveResourceEventResult(BaseEnums::Resource resource, const ValueRange &amount, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    virtual ~GiveResourceEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

    inline BaseEnums::Resource resource() const noexcept
    {
        return m_resource;
    }
    inline ValueRange addedAmount() const noexcept
    {
        return m_amount;
    }

protected:
    BaseEnums::Resource m_resource;
    ValueRange m_amount;
};

class GiveResourceRandomEventResult final : public GiveResourceEventResult
{
public:
    explicit GiveResourceRandomEventResult(const ValueRange &amount, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~GiveResourceRandomEventResult() noexcept = default;
};

class NoSignalEventResult final : public ActionEvent
{
public:
    explicit NoSignalEventResult(const ValueRange &durationInDays, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~NoSignalEventResult() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

    inline ValueRange durationInDays() const noexcept
    {
        return m_durationInDays;
    }

private:
    ValueRange m_durationInDays;
};

class CheckEventResults
{
    friend class CheckEventResultsBuilder;

public:
    ~CheckEventResults() noexcept;

    inline QVector <QPair <Event *, Chance> > positive() const noexcept
    {
        return m_positive;
    }
    inline QVector <QPair <Event *, Chance> > negative() const noexcept
    {
        return m_negative;
    }

private:
    CheckEventResults() noexcept {}

    QVector <QPair <Event *, Chance> > m_positive;
    QVector <QPair <Event *, Chance> > m_negative;
};

class CheckEventResultsBuilder
{
public:
    CheckEventResultsBuilder() noexcept;
    ~CheckEventResultsBuilder() noexcept;

    CheckEventResults *get() noexcept;

    void addPositive(const QPair <Event *, Chance> &result) noexcept;
    void addNegative(const QPair <Event *, Chance> &result) noexcept;

private:
    void validateJustBeforeReturning() noexcept;

    CheckEventResults *m_results;
};

class CheckEvent : public Event
{
public:
    ~CheckEvent() noexcept = default;

    inline auto eventResultType() const noexcept
    {
        return m_eventSubtype;
    }
    virtual QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept override = 0;

protected:
    explicit CheckEvent(EventEnums::Check eventSubtype, CheckEventResults *results, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;

    CheckEventResults *m_results;

private:
    EventEnums::Check m_eventSubtype;
};

class ValueCheckEvent final : public CheckEvent
{
public:
    explicit ValueCheckEvent(const Expression &condition, CheckEventResults *results, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~ValueCheckEvent() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    Expression m_condition;
};

class EquipmentCheckEvent final : public CheckEvent
{
public:
    explicit EquipmentCheckEvent(EquipmentEnums::Category neededEq, CheckEventResults *results, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~EquipmentCheckEvent() noexcept = default;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    EquipmentEnums::Category m_neededEquipment;
};

class PossibilityEvent final : public Event
{
public:
    explicit PossibilityEvent(Chance chance, Event *event, QString text = {}, const QVector <QString> &dbEntries = {}) noexcept;
    ~PossibilityEvent() noexcept;

    QVector <EventReport> executeSpecificOps(Mercenary *mercenary) noexcept final;

private:
    Chance m_chance;
    Event *m_event;
};

class Report
{
public:
    virtual ~Report() noexcept = default;

    inline EventEnums::ReportType type() const noexcept
    {
        return m_reportType;
    }

    virtual QString art() const noexcept = 0;
    virtual QString text() const noexcept = 0;
    inline Time time() const noexcept
    {
        return m_time;
    }

protected:
    explicit Report(EventEnums::ReportType type, const Time &time) noexcept;

private:
    EventEnums::ReportType m_reportType;
    Time m_time;
};

class NullReport final : public Report
{
public:
    NullReport(const Time &time = {}) noexcept
        : Report(EventEnums::RT_Null, time) {}

    inline QString art() const noexcept final
    {
        return "";
    }
    inline QString text() const noexcept final
    {
        return "";
    }
};

class EncounterReport final : public Report
{
public:
    EncounterReport(const QString &mercenaryArt, const QVector <EventReport> &events, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QVector <EventReport> m_events;
};

class BuildingUpgradeReport final : public Report
{
public:
    BuildingUpgradeReport(BaseEnums::Building building, unsigned level, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_buildingArt;
    }
    QString text() const noexcept final;

private:
    QString m_buildingArt;
    BaseEnums::Building m_building;
    unsigned m_level;
};

class MercenaryArrivalReport final : public Report
{
public:
    MercenaryArrivalReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class TradeCompletionReport final : public Report
{
public:
    TradeCompletionReport(BaseEnums::Resource targetResource, unsigned amount, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return "qrc:/graphics/Buildings/DockingStation.png";
    }
    QString text() const noexcept final;

private:
    BaseEnums::Resource m_targetResource;
    unsigned m_amount;
};

class EquipmentArrivalReport final : public Report
{
public:
    EquipmentArrivalReport(const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return "qrc:/graphics/Buildings/DockingStation.png";
    }
    QString text() const noexcept final;

private:
    QString m_name;
};

class DesertionReport final : public Report
{
public:
    DesertionReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class HungerReport final : public Report
{
public:
    HungerReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class NoSalaryReport final : public Report
{
public:
    NoSalaryReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class MissionEndReport final : public Report
{
public:
    MissionEndReport(const QString &mercenaryArt, const QString &name, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_name;
};

class TrainingCompletionReport final : public Report
{
public:
    TrainingCompletionReport(const QString &mercenaryArt, const QString &mercenaryName, BaseEnums::Building building, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_mercenaryName;
    BaseEnums::Building m_building;
};

class SignalLostReport final : public Report
{
public:
    SignalLostReport(const QString &mercenaryArt, const QString &mercenaryName, const QString &landName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_mercenaryName;
    QString m_landName;
};

class SignalRetrievedReport final : public Report
{
public:
    SignalRetrievedReport(const QString &mercenaryArt, const QString &landName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_landName;
};

class MissionStartReport final : public Report
{
public:
    MissionStartReport(const QString &mercenaryArt, int stress, int stressLimit, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    int m_stress, m_stressLimit;
};

class MercenaryDeathReport final : public Report
{
public:
    MercenaryDeathReport(const QString &mercenaryArt, const QString &mercenaryName, const Time &time) noexcept;

    inline QString art() const noexcept final
    {
        return m_mercenaryArt;
    }
    QString text() const noexcept final;

private:
    QString m_mercenaryArt;
    QString m_mercenaryName;
};

struct UnifiedReportDataHelper
{
    unsigned id;
    Time time;
    QString msg;
    QString art;
};

class UnifiedReport : public QObject
{
    Q_OBJECT

public:
    UnifiedReport(const Time &time, const QString &msg, const QString &artSource = {}) noexcept;
    UnifiedReport(Report *sourceToDestroy) noexcept;
    UnifiedReport(const UnifiedReportDataHelper &data) noexcept;

    operator UnifiedReportDataHelper() const noexcept;

    inline unsigned id() const noexcept
    {
        return m_id;
    }
    Q_INVOKABLE QString timestamp() const noexcept;
    Q_INVOKABLE inline QString msg() const noexcept
    {
        return m_msg;
    }
    Q_INVOKABLE inline QString artSource() const noexcept
    {
        return m_art;
    }

    inline Time time() const noexcept
    {
        return m_time;
    }

private:
    static unsigned m_currentID;
    unsigned m_id;
    Time m_time;
    QString m_msg;
    QString m_art;
};

QDataStream &operator<<(QDataStream &stream, const UnifiedReportDataHelper &report) noexcept;
QDataStream &operator>>(QDataStream &stream, UnifiedReportDataHelper &report) noexcept;

class Encounter
{
public:
    explicit Encounter(const QString &name, Event *rootEvent, unsigned probability) noexcept;

    EncounterReport *execute(Mercenary *mercenary, const Time &currentTime) const noexcept;

    inline QString name() const noexcept
    {
        return m_name;
    }

    inline unsigned probability() const noexcept
    {
        return m_probability;
    }

private:
    QString m_name;
    Event *m_rootEvent;
    unsigned m_probability;
};

class EncountersContainer
{
public:
    ~EncountersContainer() noexcept;

    void addEncounter(Encounter *enc) noexcept;
    void removeEncounter(unsigned index) noexcept;
    inline const QVector <Encounter *> &encounters() const noexcept
    {
        return m_encounters;
    }

private:
    QVector <Encounter *> m_encounters;
};

struct LandInfo
{
    QString name;
    QString description;
    QPair <int, int> position;
};

class Land : public QObject
{
    Q_OBJECT

    friend class LandBuilder;

public:
    explicit Land(const LandInfo &info) noexcept;
    ~Land() noexcept;

    Q_INVOKABLE inline QString name() const noexcept
    {
        return m_info.name;
    }
    Q_INVOKABLE inline QString description() const noexcept
    {
        return m_info.description;
    }
    Q_INVOKABLE inline int posX() const noexcept
    {
        return m_info.position.first;
    }
    Q_INVOKABLE inline int posY() const noexcept
    {
        return m_info.position.second;
    }

    Encounter *makeRandomEncounter() const noexcept;
    inline const EncountersContainer *encounters() const noexcept
    {
        return m_encounters;
    }

private:
    void setInfo(const LandInfo &info) noexcept;

    void setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept;

    LandInfo m_info;
    EncountersContainer *m_encounters;
};

class LandBuilder
{
public:
    LandBuilder() noexcept;
    ~LandBuilder() noexcept;

    Land *getLand() noexcept;
    void resetLand() noexcept;

    void setInfo(const LandInfo &info) noexcept;

    void setAssociatedEncountersContainer(EncountersContainer *encCont) noexcept;

private:
    Land *m_land;
};

class Mission : public QObject
{
    friend class MissionBuilder;

    Q_OBJECT

    Q_PROPERTY(Mercenary* mercenary MEMBER m_assignedMercenary)
    Q_PROPERTY(Land* land MEMBER m_land)
    Q_PROPERTY(UnifiedReport* preparedReport MEMBER m_preparedRelatedReport)

public:
    typedef unsigned MissionDay;

    inline const Land *land() const noexcept
    {
        return m_land;
    }
    inline EventEnums::MissionLength length() const noexcept
    {
        return m_length;
    }
    Q_INVOKABLE inline QString lengthString() const noexcept
    {
        return EventEnums::fromMissionLengthEnumToQString(length());
    }
    Q_INVOKABLE inline unsigned fullDuration() const noexcept
    {
        return m_duration;
    }
    Q_INVOKABLE inline unsigned remainingDays() const noexcept
    {
        return m_duration-m_daysSpent>0 ? m_duration-m_daysSpent : 0;
    }
    Q_INVOKABLE inline unsigned daysSpent() const noexcept
    {
        return m_daysSpent;
    }
    void handleNewDay() noexcept;

    void assignMercenary(Mercenary *mercenary) noexcept;
    inline const Mercenary *assignedMercenary() const noexcept
    {
        return m_assignedMercenary;
    }
    inline Mercenary *assignedMercenary() noexcept
    {
        return m_assignedMercenary;
    }

    void start() noexcept;
    EncounterReport *doEncounter(const Time &now) noexcept;
    inline Time timeOfCurrentEncounter() const noexcept
    {
        return m_timeOfCurrentEncounter;
    }

    void end() noexcept;
    void forceEndSuccessfully() noexcept;
    void forceEndSilently() noexcept;
    void forceEndBecauseOfDeath() noexcept;
    Q_INVOKABLE void abort() noexcept;

    void addRelatedReport(UnifiedReport *report) noexcept;
    Q_INVOKABLE void prepareReport(unsigned index) noexcept;
    Q_INVOKABLE inline unsigned amountOfReports() const noexcept
    {
        return m_relatedReports.size();
    }
    inline QVector <UnifiedReport *> &reports() noexcept
    {
        return m_relatedReports;
    }

private:
    Mission() noexcept;

    void planEverything() noexcept;
    void planAllEncounters() noexcept;
    void planEnd() noexcept;

    void setLand(Land *land) noexcept;
    void setLength(EventEnums::MissionLength length) noexcept;
    void setDuration(unsigned days) noexcept;
    void addEncounter(MissionDay day, Encounter *encounter) noexcept;

    Land *m_land;
    EventEnums::MissionLength m_length;
    unsigned m_duration;
    unsigned m_daysSpent;
    QVector <QPair <MissionDay, Encounter *> > m_encounters;
    unsigned m_nextEncounter;
    Time m_timeOfCurrentEncounter;
    int m_minutesSinceMidnightOfLastEncounter;
    Mercenary *m_assignedMercenary;
    QVector <UnifiedReport *> m_relatedReports;
    UnifiedReport *m_preparedRelatedReport;
};

struct MissionDataHelper
{
    QString land;
    EventEnums::MissionLength length;
    unsigned duration, daysSpent;
    QVector <QPair <unsigned, QString> > encounters;
    unsigned nextEncounter;
    int minutesSinceMidnightOfLastEncounter;
    QString mercenary;
    QVector <unsigned> relatedReportsIDs;
};

QDataStream &operator<<(QDataStream &stream, const MissionDataHelper &mission) noexcept;
QDataStream &operator>>(QDataStream &stream, MissionDataHelper &mission) noexcept;

class MissionBuilder
{
public:
    MissionBuilder(Base *base) noexcept;
    ~MissionBuilder() noexcept;

    Mission *getMission() noexcept; // resets
    Mission *generateMission(Land *land, EventEnums::MissionLength length) noexcept; // resets
    void resetMission() noexcept; 

    static Mission *qobjectifyMissionData(const MissionDataHelper &mission, Base *base) noexcept;
    static MissionDataHelper deqobjectifyMission(Mission *mission) noexcept;

    void setLand(Land *land) noexcept;
    void setLength(EventEnums::MissionLength length) noexcept;
    void setDuration(unsigned duration) noexcept;
    void addRandomEncounter() noexcept;
    void addEncounter(Mission::MissionDay day, Encounter *encounter) noexcept;

private:
    unsigned generateDuration(EventEnums::MissionLength length) const noexcept;
    unsigned generateAmountOfEncountersPerDay(EventEnums::MissionLength length) const noexcept;
    QVector <QPair <Mission::MissionDay, Encounter *> > generateEncounters(Land *land, EventEnums::MissionLength length, unsigned duration) const noexcept;

    static bool lessThanEncounterSorting(const QPair <Mission::MissionDay, Encounter *> &first, const QPair <Mission::MissionDay, Encounter *> &second) noexcept;

    Mission *m_mission;
    Base *m_base;
};

class MissionInitializer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Mercenary* selectedMercenary MEMBER m_mercenary)

public:
    explicit MissionInitializer(Base *base) noexcept;

    Q_INVOKABLE void reset() noexcept;
    Q_INVOKABLE bool start() noexcept;

    Q_INVOKABLE void setLand(const QString &name) noexcept;
    Q_INVOKABLE void setLength(const QString &length) noexcept;
    Q_INVOKABLE QString length() const noexcept;

    Q_INVOKABLE void setMercenary(const QString &name) noexcept;
    Q_INVOKABLE inline bool isMercenarySelected() const noexcept
    {
        return m_mercenary!=nullptr;
    }

    Q_INVOKABLE void setArmor(const QString &name) noexcept;
    Q_INVOKABLE void setWeaponTool(const QString &name, unsigned slot) noexcept;

    Q_INVOKABLE void setAetherite(unsigned amount) noexcept;
    Q_INVOKABLE void setEnergy(unsigned amount) noexcept;
    Q_INVOKABLE void setBuildingMaterials(unsigned amount) noexcept;
    Q_INVOKABLE void setFoodSupplies(unsigned amount) noexcept;

private:
    void prepareMercenary() noexcept;
    void unprepareMercenary() noexcept;

    Base *m_basePtr;
    MissionBuilder m_missionBuilder;
    Land *m_land;
    EventEnums::MissionLength m_length;
    Mercenary *m_mercenary;
    Equipment *m_armor;
    Equipment *m_weaponTool[2];
    unsigned m_aetherite, m_energy, m_bm, m_food;
};

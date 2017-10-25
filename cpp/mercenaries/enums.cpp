#include "enums.h"

#include <QString>

#include "general/game.h"
#include "logging/loggershandler.h"

MercenaryEnums::Nature MercenaryEnums::fromQStringToNatureEnum(const QString &nature) noexcept
{
    if (nature == "Active")
        return N_Active;
    if (nature == "Convivial")
        return N_Convivial;
    if (nature == "Religious")
        return N_Religious;
    if (nature == "Recluse")
        return N_Recluse;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Nature enum conversion failed for {}",nature.toStdString());
}

QString MercenaryEnums::fromNatureEnumToQString(MercenaryEnums::Nature nature) noexcept
{
    if (nature == N_Active)
        return "Active";
    if (nature == N_Convivial)
        return "Convivial";
    if (nature == N_Religious)
        return "Religious";
    if (nature == N_Recluse)
        return "Recluse";
    Game::gameInstance()->loggers()->mainLogger()->warn("Nature enum->QString conversion failed for {}",static_cast<unsigned>(nature));
}

MercenaryEnums::StressBorderEffect MercenaryEnums::fromQStringToStressBorderEffectEnum(const QString &stressBorderEffect) noexcept
{
    if (stressBorderEffect == "None")
        return SBE_None;
    if (stressBorderEffect == "Faint")
        return SBE_Faint;
    if (stressBorderEffect == "Desertion")
        return SBE_Desertion;
    if (stressBorderEffect == "Fear")
        return SBE_Fear;
    if (stressBorderEffect == "Rage")
        return SBE_Rage;
    if (stressBorderEffect == "Fanatic Wrath")
        return SBE_FanaticWrath;
    if (stressBorderEffect == "Paranoia")
        return SBE_Paranoia;
    if (stressBorderEffect == "Bravery")
        return SBE_Bravery;
    if (stressBorderEffect == "Hopeless")
        return SBE_Hopeless;
    if (stressBorderEffect == "Confusion")
        return SBE_Confusion;
    if (stressBorderEffect == "Masochism")
        return SBE_Masochism;
    if (stressBorderEffect == "Abandonce")
        return SBE_Abandonce;
    if (stressBorderEffect == "Restive")
        return SBE_Restive;
    if (stressBorderEffect == "Madness")
        return SBE_Madness;
    if (stressBorderEffect == "Restlessness")
        return SBE_Restlessness;
    if (stressBorderEffect == "Stupor")
        return SBE_Stupor;
    if (stressBorderEffect == "Consciousness")
        return SBE_Consciousness;
    if (stressBorderEffect == "Caution")
        return SBE_Caution;
    if (stressBorderEffect == "Awareness")
        return SBE_Awareness;
    if (stressBorderEffect == "Stone Skin")
        return SBE_StoneSkin;
    if (stressBorderEffect == "Multitasking")
        return SBE_Multitasking;
    if (stressBorderEffect == "Equilibrium")
        return SBE_Equilibrium;
    if (stressBorderEffect == "Stress Resistant")
        return SBE_StressResistant;
    if (stressBorderEffect == "The Lucky One")
        return SBE_TheLuckyOne;
    if (stressBorderEffect == "Doombringer")
        return SBE_Doombringer;
    if (stressBorderEffect == "Excellence")
        return SBE_Excellence;
    if (stressBorderEffect == "Absolute")
        return SBE_Absolute;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->StressBorderEffect enum conversion failed for {}",stressBorderEffect.toStdString());
}

QString MercenaryEnums::fromStressBorderEffectEnumToQString(MercenaryEnums::StressBorderEffect stressBorderEffect) noexcept
{
    if (stressBorderEffect == SBE_None)
        return "None";
    if (stressBorderEffect == SBE_Faint)
        return "Faint";
    if (stressBorderEffect == SBE_Desertion)
        return "Desertion";
    if (stressBorderEffect == SBE_Fear)
        return "Fear";
    if (stressBorderEffect == SBE_Rage)
        return "Rage";
    if (stressBorderEffect == SBE_FanaticWrath)
        return "Fanatic Wrath";
    if (stressBorderEffect == SBE_Paranoia)
        return "Paranoia";
    if (stressBorderEffect == SBE_Bravery)
        return "Bravery";
    if (stressBorderEffect == SBE_Hopeless)
        return "Hopeless";
    if (stressBorderEffect == SBE_Confusion)
        return "Confusion";
    if (stressBorderEffect == SBE_Masochism)
        return "Masochism";
    if (stressBorderEffect == SBE_Abandonce)
        return "Abandonce";
    if (stressBorderEffect == SBE_Restive)
        return "Restive";
    if (stressBorderEffect == SBE_Madness)
        return "Madness";
    if (stressBorderEffect == SBE_Restlessness)
        return "Restlessness";
    if (stressBorderEffect == SBE_Stupor)
        return "Stupor";
    if (stressBorderEffect == SBE_Consciousness)
        return "Consciousness";
    if (stressBorderEffect == SBE_Caution)
        return "Caution";
    if (stressBorderEffect == SBE_Awareness)
        return "Awareness";
    if (stressBorderEffect == SBE_StoneSkin)
        return "StoneSkin";
    if (stressBorderEffect == SBE_Multitasking)
        return "Multitasking";
    if (stressBorderEffect == SBE_Equilibrium)
        return "Equilibrium";
    if (stressBorderEffect == SBE_StressResistant)
        return "Stress Resistant";
    if (stressBorderEffect == SBE_TheLuckyOne)
        return "The Lucky One";
    if (stressBorderEffect == SBE_Doombringer)
        return "Doombringer";
    if (stressBorderEffect == SBE_Excellence)
        return "Excellence";
    if (stressBorderEffect == SBE_Absolute)
        return "Absolute";
    Game::gameInstance()->loggers()->mainLogger()->warn("StressBorderEffect enum->QString conversion failed for {}",static_cast<unsigned>(stressBorderEffect));
}

MercenaryEnums::Attribute MercenaryEnums::fromQStringToAttributeEnum(const QString &attribute) noexcept
{
    if (attribute == "Combat Effectiveness")
        return A_CombatEffectiveness;
    if (attribute == "Proficiency")
        return A_Proficiency;
    if (attribute == "Cleverness")
        return A_Cleverness;
    if (attribute == "Luck")
        return A_Luck;
    if (attribute == "Health")
        return A_Health;
    if (attribute == "Health Limit")
        return A_HealthLimit;
    if (attribute == "Daily Health Recovery")
        return A_DailyHealthRecovery;
    if (attribute == "Stress")
        return A_Stress;
    if (attribute == "Stress Resistance")
        return A_StressResistance;
    if (attribute == "Stress Limit")
        return A_StressLimit;
    if (attribute == "Stress Border")
        return A_StressBorder;
    if (attribute == "Daily Stress Recovery")
        return A_DailyStressRecovery;
    if (attribute == "Salary")
        return A_Salary;
    if (attribute == "Daily Food Consumption")
        return A_DailyFoodConsumption;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Attribute enum conversion failed for {}",attribute.toStdString());
}

QString MercenaryEnums::fromAttributeEnumToQString(MercenaryEnums::Attribute attribute) noexcept
{
    if (attribute == A_CombatEffectiveness)
        return "Combat Effectiveness";
    if (attribute == A_Proficiency)
        return "Proficiency";
    if (attribute == A_Cleverness)
        return "Cleverness";
    if (attribute == A_Luck)
        return "Luck";
    if (attribute == A_Health)
        return "Health";
    if (attribute == A_HealthLimit)
        return "Health Limit";
    if (attribute == A_DailyHealthRecovery)
        return "Daily Health Recovery";
    if (attribute == A_Stress)
        return "Stress";
    if (attribute == A_StressResistance)
        return "Stress Resistance";
    if (attribute == A_StressLimit)
        return "Stress Limit";
    if (attribute == A_StressBorder)
        return "Stress Border";
    if (attribute == A_DailyStressRecovery)
        return "Daily Stress Recovery";
    if (attribute == A_Salary)
        return "Salary";
    if (attribute == A_DailyFoodConsumption)
        return "Daily Food Consumption";
    Game::gameInstance()->loggers()->mainLogger()->warn("Attribute enum->QString conversion failed for {}",static_cast<unsigned>(attribute));
}

MercenaryEnums::CurrentActivity MercenaryEnums::fromQStringToCurrentActivityEnum(const QString &currentActivity) noexcept
{
    if (currentActivity == "Idle")
        return CA_Idle;
    if (currentActivity == "On Mission")
        return CA_OnMission;
    if (currentActivity == "In Hospital")
        return CA_InHospital;
    if (currentActivity == "On Training Ground")
        return CA_OnTrainingGround;
    if (currentActivity == "In Gym")
        return CA_InGym;
    if (currentActivity == "In Laboratory")
        return CA_InLaboratory;
    if (currentActivity == "In Playing Field")
        return CA_InPlayingField;
    if (currentActivity == "In Bar")
        return CA_InBar;
    if (currentActivity == "In Shrine")
        return CA_InShrine;
    if (currentActivity == "In Seclusion")
        return CA_InSeclusion;
    if (currentActivity == "Arriving")
        return CA_Arriving;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->CurrentActivity enum conversion failed for {}",currentActivity.toStdString());
}

QString MercenaryEnums::fromCurrentActivityEnumToQString(MercenaryEnums::CurrentActivity currentActivity) noexcept
{
    if (currentActivity == CA_Idle)
        return "Idle";
    if (currentActivity == CA_OnMission)
        return "On Mission";
    if (currentActivity == CA_InHospital)
        return "In Hospital";
    if (currentActivity == CA_OnTrainingGround)
        return "On Training Ground";
    if (currentActivity == CA_InGym)
        return "In Gym";
    if (currentActivity == CA_InLaboratory)
        return "In Laboratory";
    if (currentActivity == CA_InPlayingField)
        return "In Playing Field";
    if (currentActivity == CA_InBar)
        return "In Bar";
    if (currentActivity == CA_InShrine)
        return "In Shrine";
    if (currentActivity == CA_InSeclusion)
        return "In Seclusion";
    if (currentActivity == CA_Arriving)
        return "Arriving";
    Game::gameInstance()->loggers()->mainLogger()->warn("CurrentActivity enum->QString conversion failed for {}",static_cast<unsigned>(currentActivity));
}

MercenaryEnums::Profession MercenaryEnums::fromQStringToProfessionEnum(const QString &profession) noexcept
{
    if (profession == "Bounty Hunter")
        return P_BountyHunter;
    if (profession == "Gunzerker")
        return P_Gunzerker;
    if (profession == "Priest Of The Universe")
        return P_PriestOfTheUniverse;
    if (profession == "Priestess Of The Universe")
        return P_PriestessOfTheUniverse;
    if (profession == "Battle Droid")
        return P_BattleDroid;
    if (profession == "Space Nomad")
        return P_SpaceNomad;
    if (profession == "Archeologist")
        return P_Archeologist;
    if (profession == "Criminal")
        return P_Criminal;
    if (profession == "Cyborg")
        return P_Cyborg;
    if (profession == "Specialist")
        return P_Specialist;
    if (profession == "Doomsayer")
        return P_Doomsayer;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Profession enum conversion failed for {}",profession.toStdString());
}

QString MercenaryEnums::fromProfessionEnumToQString(MercenaryEnums::Profession profession) noexcept
{
    if (profession == P_BountyHunter)
        return "Bounty Hunter";
    if (profession == P_Gunzerker)
        return "Gunzerker";
    if (profession == P_PriestOfTheUniverse)
        return "Priest Of The Universe";
    if (profession == P_PriestessOfTheUniverse)
        return "Priestess Of The Universe";
    if (profession == P_BattleDroid)
        return "Battle Droid";
    if (profession == P_SpaceNomad)
        return "Space Nomad";
    if (profession == P_Archeologist)
        return "Archeologist";
    if (profession == P_Criminal)
        return "Criminal";
    if (profession == P_Cyborg)
        return "Cyborg";
    if (profession == P_Specialist)
        return "Specialist";
    if (profession == P_Doomsayer)
        return "Doomsayer";
    Game::gameInstance()->loggers()->mainLogger()->warn("Profession enum->QString conversion failed for {}",static_cast<unsigned>(profession));
}

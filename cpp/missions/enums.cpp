#include "enums.h"

#include <QString>

#include "general/game.h"
#include "logging/loggershandler.h"

MissionEnums::Length MissionEnums::fromQStringToLengthEnum(const QString &missionLength) noexcept
{
    if (missionLength == "Short")
        return L_Short;
    if (missionLength == "Medium")
        return L_Medium;
    if (missionLength == "Long")
        return L_Long;
    if (missionLength == "Extreme")
        return L_Extreme;
    if (missionLength == "Veteran")
        return L_Veteran;
    if (missionLength == "Master")
        return L_Master;
    if (missionLength == "Heroic")
        return L_Heroic;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Length enum conversion failed for {}",missionLength.toStdString());
}

QString MissionEnums::fromLengthEnumToQString(MissionEnums::Length missionLength) noexcept
{
    if (missionLength == L_Short)
        return "Short";
    if (missionLength == L_Medium)
        return "Medium";
    if (missionLength == L_Long)
        return "Long";
    if (missionLength == L_Extreme)
        return "Extreme";
    if (missionLength == L_Veteran)
        return "Veteran";
    if (missionLength == L_Master)
        return "Master";
    if (missionLength == L_Heroic)
        return "Heroic";
    Game::gameInstance()->loggers()->mainLogger()->warn("Length enum->QString conversion failed for {}",static_cast<unsigned>(missionLength));
}

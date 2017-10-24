#pragma once

class QString;

namespace MissionEnums
{
    enum Length
    {
        L_Short,
        L_Medium,
        L_Long,
        L_Extreme,
        L_Veteran,
        L_Master,
        L_Heroic,
        L_END
    };

    Length fromQStringToLengthEnum(const QString &missionLength) noexcept;
    QString fromLengthEnumToQString(Length missionLength) noexcept;
}

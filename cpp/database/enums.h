#pragma once

class QString;

namespace DatabaseEnums
{
    enum EntryType
    {
        ET_Lands,
        ET_Animals,
        ET_Plants,
        ET_Fungi,
        ET_END
    };

    EntryType fromQStringToEntryTypeEnum(const QString &entryType) noexcept;
    QString fromEntryTypeEnumToQString(EntryType entryType) noexcept;
}

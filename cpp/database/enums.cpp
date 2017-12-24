#include "enums.h"

#include <QString>

#include "logging/loggersprovider.h"

DatabaseEnums::EntryType DatabaseEnums::fromQStringToEntryTypeEnum(const QString &entryType) noexcept
{
    if (entryType == "Lands")
        return ET_Lands;
    if (entryType == "Animals")
        return ET_Animals;
    if (entryType == "Plants")
        return ET_Plants;
    if (entryType == "Fungi")
        return ET_Fungi;
    LoggersProvider::mainLogger()->warn("QString->EntryType enum conversion failed for {}",entryType.toStdString());
}

QString DatabaseEnums::fromEntryTypeEnumToQString(DatabaseEnums::EntryType entryType) noexcept
{
    if (entryType == ET_Lands)
        return "Lands";
    if (entryType == ET_Animals)
        return "Animals";
    if (entryType == ET_Plants)
        return "Plants";
    if (entryType == ET_Fungi)
        return "Fungi";
    LoggersProvider::mainLogger()->warn("EntryType enum->QString conversion failed for {}",static_cast<unsigned>(entryType));
}

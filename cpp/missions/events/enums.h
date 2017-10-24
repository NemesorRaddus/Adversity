#pragma once

namespace EventEnums
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
}

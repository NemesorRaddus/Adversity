#pragma once

#include "enums.h"

class QDataStream;

struct MercenaryStressBorderEffect
{
    MercenaryStressBorderEffect() noexcept
        : effectName(MercenaryEnums::SBE_None) {}
    MercenaryStressBorderEffect(MercenaryEnums::StressBorderEffect effectName_) noexcept
        : effectName(effectName_) {}

    MercenaryEnums::StressBorderEffect effectName;

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;
};

QDataStream &operator<<(QDataStream &stream, const MercenaryStressBorderEffect &effect) noexcept;
QDataStream &operator>>(QDataStream &stream, MercenaryStressBorderEffect &effect) noexcept;

#include "stressbordereffect.h"

#include <QDataStream>

QDataStream &MercenaryStressBorderEffect::read(QDataStream &stream) noexcept
{
    quint8 n;

    stream>>n;
    effectName = static_cast<MercenaryEnums::StressBorderEffect>(n);

    return stream;
}

QDataStream &MercenaryStressBorderEffect::write(QDataStream &stream) const noexcept
{
    stream<<static_cast<quint8>(effectName);

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const MercenaryStressBorderEffect &effect) noexcept
{
    return effect.write(stream);
}

QDataStream &operator>>(QDataStream &stream, MercenaryStressBorderEffect &effect) noexcept
{
    return effect.read(stream);
}

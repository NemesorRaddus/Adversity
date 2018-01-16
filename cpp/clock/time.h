#pragma once

#include "libs/RBoundedValue_v0_1_1-Beta/rboundedvalue.h"

class QString;
class QDataStream;

struct Time
{
    typedef unsigned Day;
    typedef RBoundedValue < unsigned, 0, 23, true> Hour;
    typedef RBoundedValue < unsigned, 0, 59, true> Minute;

    Time() noexcept;
    Time(unsigned day, unsigned hour, unsigned minute) noexcept;

    bool operator ==(const Time &other) const noexcept;
    inline bool operator !=(const Time &other) const noexcept
    {
        return !(*this == other);
    }

    bool operator <(const Time &other) const noexcept;
    inline bool operator <=(const Time &other) const noexcept
    {
        return *this == other || *this < other;
    }
    inline bool operator >(const Time &other) const noexcept
    {
        return !(*this <= other);
    }
    inline bool operator >=(const Time &other) const noexcept
    {
        return !(*this < other);
    }

    QString toQString() const noexcept;

    Day d;
    Hour h;
    Minute min;
};

QDataStream &operator<<(QDataStream &stream, const Time &time) noexcept;
QDataStream &operator>>(QDataStream &stream, Time &time) noexcept;

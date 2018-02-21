#include "time.h"

#include <QString>
#include <QDataStream>

Time::Time() noexcept
    : d(1), h(0), min(0) {}

Time::Time(unsigned day, unsigned hour, unsigned minute) noexcept
    : d(day), h(hour), min(minute) {}

bool Time::operator ==(const Time &other) const noexcept
{
    return d==other.d && h==other.h && min == other.min;
}

bool Time::operator <(const Time &other) const noexcept
{
    if (d < other.d)
        return 1;
    else if (d > other.d)
        return 0;

    if (h < other.h)
        return 1;
    else if (h > other.h)
        return 0;

    if (min < other.min)
        return 1;
    else
        return 0;
}

QString Time::toQString() const noexcept
{
    return QString("D")+QString::number(d)+" "+QString::number(h)+" "+QString::number(min);
}

QDataStream &operator<<(QDataStream &stream, const Time &time) noexcept
{
    stream<<static_cast<quint16>(time.d);
    stream<<static_cast<quint16>(time.h);
    stream<<static_cast<quint16>(time.min);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, Time &time) noexcept
{
    quint16 uii;

    stream>>uii;
    time.d = uii;

    stream>>uii;
    time.h = uii;

    stream>>uii;
    time.min = uii;

    return stream;
}

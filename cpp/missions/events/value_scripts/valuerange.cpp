#include "valuerange.h"

#include <QString>

ValueRange::ValueRange() noexcept
    : m_min("0"), m_max("0") {}

ValueRange::ValueRange(const Expression &min, const Expression &max) noexcept
    : m_min(min), m_max(max) {}

ValueRange::ValueRange(const Expression &value) noexcept
    : m_min(value), m_max(value) {}

bool ValueRange::singleValue() const noexcept
{
    return static_cast<QString>(m_min) == static_cast<QString>(m_max);
}

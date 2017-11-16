#pragma once

#include "expression.h"

class QString;

class ValueRange
{
public:
    ValueRange() noexcept;
    ValueRange(const Expression &min, const Expression &max) noexcept;
    ValueRange(const Expression &value) noexcept;

    inline Expression min() const noexcept
    {
        return m_min;
    }
    inline Expression max() const noexcept
    {
        return m_max;
    }

    bool singleValue() const noexcept;

private:
    Expression m_min, m_max;
};

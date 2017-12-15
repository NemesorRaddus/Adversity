#pragma once

class Base;

class BaseManagerInterface
{
protected:
    explicit BaseManagerInterface(Base * const ptrToBase) noexcept;
    virtual ~BaseManagerInterface() noexcept = default;

    inline Base *base() const noexcept
    {
        return m_ptrToBase;
    }

    virtual void initializeForNewBase() noexcept = 0;

private:
    Base * const m_ptrToBase;
};

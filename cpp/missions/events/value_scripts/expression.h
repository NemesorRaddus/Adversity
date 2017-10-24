#pragma once

#include <QString>

class QVariant;
class QJSEngine;

class Mercenary;

class Expression
{
public:
    Expression() noexcept;
    Expression(const QString &expr) noexcept;
    Expression(const Expression &other) noexcept;

    inline explicit operator QString() const noexcept
    {
        return m_expr;
    }

    void set(const QString &expr) noexcept;

    bool isValid() const noexcept;

    QVariant evaluate(const Mercenary *context) const noexcept;

private:
    void validateExpr() noexcept;
    void handleEngine() noexcept;

    QString m_expr;
    bool m_isExprValid;
    QJSEngine *m_engine;
};

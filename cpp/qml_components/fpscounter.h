#pragma once

#include <QQuickPaintedItem>

class FPSText: public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)

public:
    FPSText(QQuickItem *parent = 0) noexcept;
    ~FPSText() = default;

    void paint(QPainter *painter) noexcept;
    Q_INVOKABLE inline int fps() const noexcept
    {
        return m_currentFPS;
    }

signals:
    void fpsChanged(int);

private:
    void recalculateFPS() noexcept;

    int m_currentFPS;
    int m_cacheCount;
    QVector <qint64> m_times;
};

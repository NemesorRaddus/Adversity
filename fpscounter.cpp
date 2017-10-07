#include "fpscounter.h"

FPSText::FPSText(QQuickItem *parent) noexcept
    : QQuickPaintedItem(parent), m_currentFPS(0), m_cacheCount(0)
{
    m_times.clear();
    setFlag(QQuickItem::ItemHasContents);
}

void FPSText::paint(QPainter *painter) noexcept
{
    recalculateFPS();

    update();
}

void FPSText::recalculateFPS() noexcept
{
    qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    m_times.push_back(currentTime);

    while (m_times[0] < currentTime - 1000)
        m_times.pop_front();

    int currentCount = m_times.length();
    m_currentFPS = (currentCount + m_cacheCount) / 2;

    if (currentCount != m_cacheCount)
        fpsChanged(m_currentFPS);

    m_cacheCount = currentCount;
}

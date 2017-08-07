#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <QQuickPaintedItem>
#include <QBrush>
#include <QPainter>
#include <QDateTime>

class FPSText: public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)

public:
    FPSText(QQuickItem *parent = 0);
    ~FPSText() = default;

    void paint(QPainter *painter);
    Q_INVOKABLE int fps()const
    {
        return m_currentFPS;
    }

signals:
    void fpsChanged(int);

private:
    void recalculateFPS();

    int m_currentFPS;
    int m_cacheCount;
    QVector <qint64> m_times;
};

#endif // FPSCOUNTER_H

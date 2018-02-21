#pragma once

#include <QList>
#include <QQuickItem>
#include <QString>
#include <QVariant>
#include <QVector>

class SignalTransmitter : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QVector <QString> signalReceivers READ signalReceivers WRITE setSignalReceivers)
    Q_PROPERTY(bool forward MEMBER m_forward)
    Q_PROPERTY(bool enabled MEMBER m_enabled)
    Q_PROPERTY(bool blockReceived MEMBER m_blockReceived)

public:
    SignalTransmitter(QQuickItem *parent = 0) noexcept;
    SignalTransmitter(const QString &transmitterName, QQuickItem *parent = 0) noexcept;

    inline QString name() const noexcept
    {
        return m_name;
    }
    void setName(const QString &name) noexcept;

    inline QVector <QString> signalReceivers() const noexcept
    {
        return m_receiverNames;
    }
    void setSignalReceivers(const QVector<QString> &signalReceivers) noexcept;

    void receiveSignal(const QVariantList &parameters = {}) noexcept;

public slots:
    void emitSignal(const QVariantList &parameters = {}) noexcept;

signals:
    void signalReceived();
    void signalReceived(QVariantList);
    void signalBlocked();

private:
    void registerTransmitter() noexcept;
    void fixReceiverHandling(const SignalTransmitter *receiver) noexcept; // fixes things in case it should be handled but it isn't or vice versa
    void maybeAddReceiver(SignalTransmitter *receiver) noexcept;
    void maybeForwardSignal(const QVariantList &parameters = {}) noexcept;

    QString m_name;
    QVector <QString> m_receiverNames;
    QVector <SignalTransmitter *> m_receivers;
    bool m_forward;
    bool m_enabled;
    bool m_blockReceived;

    static QVector <SignalTransmitter *> m_transmitters;
};

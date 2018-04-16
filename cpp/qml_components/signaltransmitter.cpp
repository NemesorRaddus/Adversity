#include "signaltransmitter.h"

QVector <SignalTransmitter *> SignalTransmitter::m_transmitters;

SignalTransmitter::SignalTransmitter(QQuickItem *parent) noexcept
    : QQuickItem(parent), m_forward(false), m_enabled(false), m_blockReceived(false)
{
    registerTransmitter();
}

SignalTransmitter::SignalTransmitter(const QString &transmitterName, QQuickItem *parent) noexcept
    : QQuickItem(parent), m_name(transmitterName), m_forward(false), m_enabled(transmitterName.isEmpty() ? false : true), m_blockReceived(false)
{
    registerTransmitter();
}

void SignalTransmitter::setName(const QString &name) noexcept
{
    m_name = name;
    for (auto &e : m_transmitters)
        e->fixReceiverHandling(this);
}

void SignalTransmitter::setSignalReceivers(const QVector <QString> &signalReceivers) noexcept
{
    m_receiverNames = signalReceivers;
    m_receivers.clear();
    for (const auto &e : m_receiverNames)
        for (const auto &f : m_transmitters)
            if (f != this && f->name() == e)
                m_receivers.push_back(f);
}

void SignalTransmitter::receiveSignal(const QVariantList &parameters) noexcept
{
    if (m_enabled)
    {
        if (!m_blockReceived)
        {
            signalReceived(parameters);
            signalReceived();
        }
        else
            signalBlocked();
    }
}

void SignalTransmitter::emitSignal(const QVariantList &parameters) noexcept
{
    if (m_enabled)
        for (auto &e : m_receivers)
            e->receiveSignal(parameters);
}

void SignalTransmitter::registerTransmitter() noexcept
{
    for (auto &e : m_transmitters)
        e->maybeAddReceiver(this);
    m_transmitters += this;
}

void SignalTransmitter::maybeAddReceiver(SignalTransmitter *receiver) noexcept
{
    if (m_receiverNames.contains(receiver->name()) && !m_receivers.contains(receiver))
        m_receivers.push_back(receiver);
}

void SignalTransmitter::fixReceiverHandling(const SignalTransmitter *receiver) noexcept
{
    auto safeNonConstValPtr = const_cast<SignalTransmitter *>(receiver); // it isn't modified, QVector doesn't do anything with it, it just
    // handles pointers not the way it should, instead of requiring a (const) ptr to const value, it requires a const ptr to value
    bool containsPtr = m_receivers.contains(safeNonConstValPtr), containsName = m_receiverNames.contains(receiver->name());
    if (containsPtr)
    {
        if (!containsName)
            m_receivers.removeOne(safeNonConstValPtr);
    }
    else if (containsName)
        m_receivers.push_back(safeNonConstValPtr);
}

void SignalTransmitter::maybeForwardSignal(const QVariantList &parameters) noexcept
{
    if (m_enabled && m_forward)
        emitSignal(parameters);
}

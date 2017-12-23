#include "randomizer.h"

#include <QTime>
#include <QtMath>

#include "logging/loggersprovider.h"

unsigned Randomizer::RandomizationMethods::flatRand(unsigned a, unsigned b)
{
    return {qrand() % ((b + 1) - a) + a};
}

unsigned Randomizer::RandomizationMethods::bentRand(unsigned a, unsigned b)
{
    const unsigned df = 50; // dispersion factor

    unsigned amountOfValues = b-a+1;

    auto g = [a,b,amountOfValues](unsigned x)
    {
        return (100-df)*(qSin((x*M_PI) / (amountOfValues-1)) - 1) + 100;
    };

    auto getSum = [a,b,g]()
    {
        unsigned sum = 0;
        bool even = (a+b)%2 != 0;
        unsigned middle = (a+b)/2;
        for (int i=a;i<middle + even;++i)
            sum += g(i);
        sum *= 2;
        if (!even)
            sum += g(middle);

        return sum;
    };
    unsigned sum = getSum();

    auto f = [a,b,g,sum](unsigned x)
    {
        return g(x) / sum * 100;
    };

    unsigned chances[amountOfValues];
    for (int i=a;i<=b;++i)
        chances[i-a] = f(i);

    unsigned random = Randomizer::randomBetweenAAndB(0,100);

    for (int i=0;i<amountOfValues;++i)
    {
        if (random <= chances[i])
            return i+a;
        else
            random -= chances[i];
    }
}

void Randomizer::initialize() noexcept
{
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
}

unsigned Randomizer::randomBetweenAAndB(unsigned a, unsigned b, unsigned (*randomization)(unsigned, unsigned)) noexcept
{
    try
    {
        return randomization(a,b);
    }
    catch(...)
    {
        LoggersProvider::mainLogger()->critical("Wrong params for randomBetweenAAndB (a={}, b={})!",a,b);
        abort();
    }
}

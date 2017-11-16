#pragma once

namespace Randomizer
{
    namespace RandomizationMethods
    {
        unsigned flatRand(unsigned a, unsigned b);
        unsigned bentRand(unsigned a, unsigned b);
    }

    void initialize() noexcept;
    unsigned randomBetweenAAndB(unsigned a, unsigned b, unsigned(*randomization)(unsigned, unsigned) = RandomizationMethods::flatRand) noexcept;
}

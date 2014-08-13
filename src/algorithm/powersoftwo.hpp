/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    powersoftwo.hpp
 * Created: 2014-08-04
 * Authors: Jani Salo
 */

/*
 * Very simple class that returns specified powers of two for given integer.
 */

#ifndef RUNRUN_POWERSOFTWO_HPP
#define RUNRUN_POWERSOFTWO_HPP

#include <cstdint>

namespace runrun {
    class PowersOfTwo {
        public:
            PowersOfTwo(std::uint32_t value);

            bool isValid() const;

            std::uint32_t getGreatestLesserOrEqual() const;
            std::uint32_t getLeastGreaterOrEqual() const;

        private:
            std::uint32_t greatestLesserOrEqual;
            std::uint32_t leastGreaterOrEqual;
    };

    inline PowersOfTwo::PowersOfTwo(std::uint32_t value) {
        if (value == 0) {
            greatestLesserOrEqual = 0;
            leastGreaterOrEqual   = 0;
        }
        else {
            for (std::uint32_t u = 0; u <= 31; u++) {
                const std::uint32_t power = 1 << u;

                if (power >= value) {
                    leastGreaterOrEqual = power;
                    if (power == value) greatestLesserOrEqual = power;
                    else                greatestLesserOrEqual = power >> 1;

                    return;
                }
            }

            leastGreaterOrEqual = 0xFFFFFFFF;
        }
    }

    inline bool PowersOfTwo::isValid() const { return leastGreaterOrEqual != 0xFFFFFFFF; }

    inline std::uint32_t PowersOfTwo::getGreatestLesserOrEqual() const { return greatestLesserOrEqual; }
    inline std::uint32_t PowersOfTwo::getLeastGreaterOrEqual() const { return leastGreaterOrEqual; }
};

#endif /* RUNRUN_POWERSOFTWO_HPP */


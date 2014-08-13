/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    rng.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A wrapper for the Velox 3b pseudorandom number generator by Elias Yarrkov.
 * See http://cipherdev.org for more information.
 */

#ifndef RUUKKU_RNG_HPP
#define RUUKKU_RNG_HPP

#include <cstdint>
#include <ctime>

#include "roll.hpp"

namespace ruukku {
    class RNG {
        public:
            RNG(const std::uint32_t seed = 0);

        public:
            std::uint32_t genUInt32() { if (pos_ == 0) mix(); return vec_[--pos_]; }

            template < typename T >
            T genReal() { return static_cast< T > (genUInt32()) / static_cast< T >(4294967296.0); }

            std::uint32_t rollDice(std::uint32_t sides) { return (genUInt32() % sides) + 1; }

        private:
            void mix();

        private:
            uint32_t pos_;
            uint32_t vec_[4], ctr_[4];
    };

    inline RNG::RNG(const std::uint32_t seed) : pos_(0) {
        for (int i = 0; i < 4; i++) vec_[i] = ctr_[i] = i * 0x9E3779B9;
        vec_[0] ^= seed;

        // Generate few numbers to get it started for sure.
        for (int i = 0; i < 16; i++) genUInt32();
    }

    inline void RNG::mix() {
        vec_[0] = Roll::rol32(vec_[0] + vec_[3], 21);
        vec_[1] = Roll::rol32(vec_[1], 12) + vec_[2];
        vec_[2] = vec_[2] ^ vec_[0];
        vec_[3] = vec_[3] ^ vec_[1];
        vec_[0] = Roll::rol32(vec_[0] + vec_[3], 19);
        vec_[1] = Roll::rol32(vec_[1], 24) + vec_[2];
        vec_[2] = vec_[2] ^ vec_[0];
        vec_[3] = vec_[3] ^ vec_[1];
        vec_[0] = Roll::rol32(vec_[0] + vec_[3],  7);
        vec_[1] = Roll::rol32(vec_[1], 12) + vec_[2];
        vec_[2] = vec_[2] ^ vec_[0];
        vec_[3] = vec_[3] ^ vec_[1];
        vec_[0] = Roll::rol32(vec_[0] + vec_[3], 27);
        vec_[1] = Roll::rol32(vec_[1], 17) + vec_[2];
        vec_[2] = vec_[2] ^ vec_[0];
        vec_[3] = vec_[3] ^ vec_[1];

        for (int i = 0; i < 4; i++) vec_[i] += ctr_[i];
        for (int i = 0; i < 4; i++) if(++ctr_[i]) break;

        pos_ = 4;
    }
};

#endif /* RUUKKU_RNG_HPP */


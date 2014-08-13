/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    roll.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A collection of bit rolling algorithms.
 */

#ifndef RUUKKU_ROLL_HPP
#define RUUKKU_ROLL_HPP

#include <cstdint>

namespace ruukku {
    class Roll {
        public:
            static std::uint8_t rol8(std::uint8_t i, std::uint8_t shift) { return (i << shift) | (i >> (8 - shift)); }
            static std::uint8_t ror8(std::uint8_t i, std::uint8_t shift) { return (i >> shift) | (i << (8 - shift)); }

            static std::uint16_t rol16(std::uint16_t i, std::uint8_t shift) { return (i << shift) | (i >> (16 - shift)); }
            static std::uint16_t ror16(std::uint16_t i, std::uint8_t shift) { return (i >> shift) | (i << (16 - shift)); }

            static std::uint32_t rol32(std::uint32_t i, std::uint8_t shift) { return (i << shift) | (i >> (32 - shift)); }
            static std::uint32_t ror32(std::uint32_t i, std::uint8_t shift) { return (i >> shift) | (i << (32 - shift)); }
    };
};

#endif /* RUUKKU_ROLL_HPP */


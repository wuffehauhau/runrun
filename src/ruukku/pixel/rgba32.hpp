/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    rgba32.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A four byte tightly packing RGBA element in little-endian order.
 */

#ifndef RUUKKU_RGBA32_HPP
#define RUUKKU_RGBA32_HPP

#include <cstdint>

#pragma pack(push, 4)

namespace ruukku {
    struct RGBA32 {
        public:
            std::uint8_t r, g, b, a;

        public:
            RGBA32() {}
            RGBA32(
                const std::uint8_t r,
                const std::uint8_t g,
                const std::uint8_t b,
                const std::uint8_t a
            ) : r(r), g(g), b(b), a(a) {}

        public:
            bool operator ==(const RGBA32& c) const { return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a); }
            bool operator !=(const RGBA32& c) const { return (r != c.r) || (g != c.g) || (b != c.b) || (a != c.a); }
    };
};

#pragma pack(pop)

#endif /* RUUKKU_RGBA32_HPP */


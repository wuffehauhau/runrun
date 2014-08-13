/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    endianness.hpp
 * Created: 2013-01-17
 * Authors: Jani Salo
 */

/*
 * A collection of utilities for detecting and handling endianness.
 */

#ifndef RUUKKU_ENDIANNESS_HPP
#define RUUKKU_ENDIANNESS_HPP

#include <cstdint>
#include "SDL2/SDL_endian.h"

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
namespace ruukku {
    class Endianness {
        public:
            static bool isLittle() { return true;  }
            static bool isBig()    { return false; }

            // Reverses byte order to opposite if the system is little or big endian.
            static void flipIfLittle (std::uint32_t& x) { SDL_Swap32(x); }
            static void flipIfBig    (std::uint32_t& x) {}
    };
};

#else /* SDL_BYTEORDER == SDL_LIL_ENDIAN */

namespace ruukku {
    class Endianness {
        public:
            static bool isLittle() { return false; }
            static bool isBig()    { return true;  }

            // Reverses byte order to opposite if the system is little or big endian.
            static void flipIfLittle (std::uint32_t& x) {}
            static void flipIfBig    (std::uint32_t& x) { SDL_Swap32(x); }
    };
};

#endif /* SDL_BYTEORDER == SDL_LIL_ENDIAN */

#endif /* RUUKKU_ENDIANNESS_HPP */


/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    displaymode.hpp
 * Created: 2012-08-17
 * Authors: Jani Salo
 */

/*
 * A container for fullscreen display mode.
 */

#ifndef RUUKKU_DISPLAYMODE_HPP
#define RUUKKU_DISPLAYMODE_HPP

#include <cstdint>
#include <SDL2/SDL.h>

#include "../math/ivec2.hpp"

namespace ruukku {
    class DisplayMode {
        public:
            // Zero means default for refresh rate.
            DisplayMode(
                const Int2&         resolution  = Int2(0, 0),
                const std::uint32_t format      = SDL_PIXELFORMAT_UNKNOWN,
                const int           refreshRate = 0
            ) :
                resolution_  (resolution),
                format_      (format),
                refreshRate_ (refreshRate)
            {}

        public:
            Int2          getResolution()  const { return resolution_; }
            std::uint32_t getFormat()      const { return format_; }
            int           getRefreshRate() const { return refreshRate_; }

        private:
            Int2          resolution_;
            std::uint32_t format_;
            int           refreshRate_;
    };
};

#endif /* RUUKKU_DISPLAYMODE_HPP */


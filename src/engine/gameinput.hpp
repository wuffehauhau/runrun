/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    gameinput.hpp
 * Created: 2014-05-30
 * Authors: Jani Salo
 */

/*
 * Container for game input.
 */

#ifndef RUNRUN_GAMEINPUT_HPP
#define RUNRUN_GAMEINPUT_HPP

#include <cstdint>
#include "algorithm/flags.hpp"

namespace runrun {
    class GameInput {
        public:
            enum class Button : std::uint32_t {
                Left    = 1,
                Right   = 2,
                Down    = 4,
                Up      = 8,
                ZoomIn  = 16,
                ZoomOut = 32
            };

            Flags< Button > buttons;
    };
};

#endif /* RUNRUN_GAMEINPUT_HPP */


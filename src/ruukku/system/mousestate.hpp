/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    mousestate.cpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

/*
 * A container for mouse state.
 */

#ifndef RUUKKU_MOUSESTATE_HPP
#define RUUKKU_MOUSESTATE_HPP

#include <cstdint>
#include "../math/ivec2.hpp"

namespace ruukku {
    class MouseState {
        public:
            MouseState(
                const Int2& position = Int2(0, 0),
                const Int2& movement = Int2(0, 0),
                const std::uint8_t buttonMask = 0
            ) :
                position_   (position),
                movement_   (movement),
                buttonMask_ (buttonMask)
            {}

        public:
            Int2 getPosition() const { return position_; }
            Int2 getMovement() const { return movement_; }

            bool isButtonDown(const uint8_t button) const { return (buttonMask_ & button) != 0; }

        private:
            Int2 position_;
            Int2 movement_;

            std::uint8_t buttonMask_;
    };
};

#endif /* RUUKKU_MOUSESTATE_HPP */


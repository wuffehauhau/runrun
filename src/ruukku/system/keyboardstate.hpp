/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    keyboardstate.cpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

/*
 * A container for keyboard state.
 */

#ifndef RUUKKU_KEYBOARDSTATE_HPP
#define RUUKKU_KEYBOARDSTATE_HPP

#include <cstdint>
#include <vector>

#include <SDL2/SDL.h>

namespace ruukku {
    class KeyboardState {
        public:
            KeyboardState(
                const std::uint8_t* stateList = nullptr,
                const uint32_t      keyCount  = 0,
                const SDL_Keymod    modifiers = KMOD_NONE
            );

        public:
            bool isKeyDown        (const SDL_Keycode key) const;
            bool isModifierActive (const SDL_Keymod  mod) const;

        private:
            std::vector< uint8_t > stateList_;
            SDL_Keymod             modifiers_;
    };
};

#endif /* RUUKKU_KEYBOARDSTATE_HPP */


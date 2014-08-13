/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    keyboardstate.cpp
 * Created: 2013-01-23
 * Authors: Jani Salo
 */

#include "keyboardstate.hpp"

namespace ruukku {
    KeyboardState::KeyboardState(
        const std::uint8_t* stateList,
        const uint32_t      keyCount,
        const SDL_Keymod    modifiers
    ) : modifiers_(modifiers) {
        for (size_t i = 0; i < keyCount; i++) stateList_.push_back(stateList[i]);
    }

    bool KeyboardState::isKeyDown(const SDL_Keycode key) const {
        if (static_cast< size_t >(key) > (stateList_.size() - 1)) {
            return false;
        }
        else {
            return stateList_[key] == 1;
        }
    }

    bool KeyboardState::isModifierActive(const SDL_Keymod mod) const {
        return modifiers_ | mod;
    }
};


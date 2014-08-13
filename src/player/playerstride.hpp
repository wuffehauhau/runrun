/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    playerstride.hpp
 * Created: 2014-06-16
 * Authors: Jani Salo
 */

/*
 * Enumeration of player actions related to walking and running.
 */

#ifndef RUNRUN_PLAYERSTRIDE_HPP
#define RUNRUN_PLAYERSTRIDE_HPP

namespace runrun {
    enum class PlayerStride {
        Idle,
        WalkLeft,
        WalkRight
    };
};

#endif /* RUNRUN_PLAYERSTRIDE_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tileorientation.hpp
 * Created: 2014-07-28
 * Authors: Jani Salo
 */

/*
 * Simple enumeration of tile orientations.
 */

#ifndef RUNRUN_TILEORIENTATION_HPP
#define RUNRUN_TILEORIENTATION_HPP

namespace runrun{
    // Orientations are assumed to form a continuous range from 0 to N.
    enum class TileOrientation : unsigned int {
        LeftBottom  =   0,
        RightBottom =   1,
        RightTop    =   2,
        LeftTop     =   3,
        Undefined   = 255
    };
};

#endif /* RUNRUN_TILEORIENTATION_HPP */


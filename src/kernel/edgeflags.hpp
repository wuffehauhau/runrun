/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    kernelinfo.hpp
 * Created: 2014-07-31
 * Authors: Jani Salo
 */

/*
 * Return value for kernel read operation.
 */

#ifndef RUNRUN_KERNELINFO_HPP
#define RUNRUN_KERNELINFO_HPP

#include "algorithm/flags.hpp"

namespace runrun {
    // Not the cutest solution, but works well enough.
    enum class EdgeFlag : std::uint32_t {
        None        = 0,
        Left        = 1,
        Right       = 2,
        Bottom      = 4,
        Top         = 8,
        LeftBottom  = 1 + 4,
        RightBottom = 2 + 4,
        LeftTop     = 1 + 8,
        RightTop    = 2 + 8,
        LeftHalf    = 1 + 4 + 8,
        RightHalf   = 2 + 4 + 8,
        BottomHalf  = 1 + 2 + 4,
        TopHalf     = 1 + 2 + 8,
        All         = 1 + 2 + 4 + 8
    };

    typedef Flags< EdgeFlag > EdgeFlags;
};

#endif /* RUNRUN_KERNELINFO_HPP */


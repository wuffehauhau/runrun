/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    transformations.hpp
 * Created: 2014-06-24
 * Authors: Jani Salo
 */

/*
 * Collection of some tools for commonly used point transformations.
 */

#ifndef RUNRUN_TRANSFORMATIONS_HPP
#define RUNRUN_TRANSFORMATIONS_HPP

#include "ruukku/opengl/gltypes.hpp"

namespace runrun {
    class Transformations {
        public:
            enum class Rotation {
                None,
                CCW90,
                CCW180,
                CCW270,
                CW90,
                CW180,
                CW270
            };

            enum class Direction {
                Normal,
                MirrorX,
                MirrorY
            };

            static ruukku::GLFloatVec2 RotateAndFlip(
                const ruukku::GLFloatVec2& input,
                const ruukku::GLFloatVec2& center,
                const Rotation  rotation,
                const Direction direction
            );
    };
};

#endif /* RUNRUN_TRANSFORMATIONS_HPP */


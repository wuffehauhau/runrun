/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    transformation.cpp
 * Created: 2014-06-24
 * Authors: Jani Salo
 */

#include "transformations.hpp"

using namespace ruukku;

namespace runrun {
    GLFloatVec2 Transformations::RotateAndFlip(
        const GLFloatVec2& input,
        const GLFloatVec2& center,
        const Rotation  rotation,
        const Direction direction
    ) {
        GLFloatVec2 output = input - center;

        switch (rotation) {
            case Transformations::Rotation::CCW90:
            case Transformations::Rotation::CW270:
                output = GLFloatVec2(-output.y,  output.x);
                break;
            case Transformations::Rotation::CCW180:
            case Transformations::Rotation::CW180:
                output = GLFloatVec2(-output.x, -output.y);
                break;
            case Transformations::Rotation::CCW270:
            case Transformations::Rotation::CW90:
                output = GLFloatVec2( output.y, -output.x);
                break;
        }

        switch (direction) {
            case Transformations::Direction::MirrorX:
                output = GLFloatVec2(-output.x,  output.y);
                break;
            case Transformations::Direction::MirrorY:
                output = GLFloatVec2( output.x, -output.y);
                break;
        }

        return output + center;
    }
};


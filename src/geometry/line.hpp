/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    line.hpp
 * Created: 2014-06-04
 * Authors: Jani Salo
 */

/*
 * A line defined by a position and a vector, or normal, orthogonal to the line.
 * The normal is used to denote the "top half" of the space divided by the line.
 */

#ifndef RUNRUN_LINE_HPP
#define RUNRUN_LINE_HPP

#include "ruukku/opengl/gltypes.hpp"

namespace runrun {
    class Line {
        public:
            ruukku::GLFloatVec2 p;
            ruukku::GLFloatVec2 n;

            Line()                                                                        {}
            Line(const ruukku::GLFloatVec2& p, const ruukku::GLFloatVec2& n) : p(p), n(n) {}

            Line getTransformed(const ruukku::GLFloatMat3 tf) const;

            // Returns zero for points on the line.
            GLfloat test(const ruukku::GLFloatVec2& point) const { return (point - p).getDot(n); }
    };

    inline Line Line::getTransformed(const ruukku::GLFloatMat3 tf) const {
        return Line(tf.transform(p), tf.transform(n));
    }
};

#endif /* RUNRUN_LINE_HPP */


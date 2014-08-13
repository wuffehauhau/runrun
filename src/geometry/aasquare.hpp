/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    aasquare.hpp
 * Created: 2014-06-04
 * Authors: Jani Salo
 */

/*
 * An axis aligned square.
 */

#ifndef RUNRUN_AASQUARE_HPP
#define RUNRUN_AASQUARE_HPP

#include "ruukku/opengl/gltypes.hpp"
#include "line.hpp"

namespace runrun {
    class AASquare {
        public:
            ruukku::GLFloatVec2 origin;
            GLfloat edgeLength;

            AASquare()                                                                                                     {}
            AASquare(const ruukku::GLFloatVec2& origin, const GLfloat edgeLength) : origin(origin), edgeLength(edgeLength) {}

            GLfloat getInnerRadius() const { return 0.500000f * edgeLength; }
            GLfloat getOuterRadius() const { return 0.707107f * edgeLength; }

            ruukku::GLFloatVec2 getCenter() const { return origin + 0.5f * ruukku::GLFloatVec2(edgeLength, edgeLength); }

            ruukku::GLFloatVec2 getLBVertex() const { return origin; }
            ruukku::GLFloatVec2 getRBVertex() const { return ruukku::GLFloatVec2(origin.x + edgeLength, origin.y); }
            ruukku::GLFloatVec2 getLTVertex() const { return ruukku::GLFloatVec2(origin.x,              origin.y + edgeLength); }
            ruukku::GLFloatVec2 getRTVertex() const { return ruukku::GLFloatVec2(origin.x + edgeLength, origin.y + edgeLength); }

            AASquare getLBHalfSquare() const { return AASquare(origin + ruukku::GLFloatVec2(0.0f * edgeLength, 0.0f * edgeLength), 0.5f * edgeLength); }
            AASquare getRBHalfSquare() const { return AASquare(origin + ruukku::GLFloatVec2(0.5f * edgeLength, 0.0f * edgeLength), 0.5f * edgeLength); }
            AASquare getLTHalfSquare() const { return AASquare(origin + ruukku::GLFloatVec2(0.0f * edgeLength, 0.5f * edgeLength), 0.5f * edgeLength); }
            AASquare getRTHalfSquare() const { return AASquare(origin + ruukku::GLFloatVec2(0.5f * edgeLength, 0.5f * edgeLength), 0.5f * edgeLength); }

            bool isAboveLine(const Line& line) const;
    };

    inline bool AASquare::isAboveLine(const Line& line) const {
        if      (line.test(getLBVertex()) <= 0.0f) return false;
        else if (line.test(getRBVertex()) <= 0.0f) return false;
        else if (line.test(getLTVertex()) <= 0.0f) return false;
        else if (line.test(getRTVertex()) <= 0.0f) return false;
        else return true;
    }
};

#endif /* RUNRUN_AASQUARE_HPP */


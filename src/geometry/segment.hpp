/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    segment.hpp
 * Created: 2014-07-04
 * Authors: Jani Salo
 */

/*
 * Describes a line segment.
 */

#ifndef RUNRUN_SEGMENT_HPP
#define RUNRUN_SEGMENT_HPP

#include "ruukku/opengl/gltypes.hpp"

namespace runrun {
    class Segment {
        public:
            ruukku::GLFloatVec2 a, b;

            Segment()                                                                         {}
            Segment(const ruukku::GLFloatVec2& a, const ruukku::GLFloatVec2& b) : a(a), b(b) {}

            bool isPoint() const;

            ruukku::GLFloatVec2 getDelta() const;

            // Returns delta rotated 90 degrees clockwise.
            ruukku::GLFloatVec2 getOrthogonal() const;

            // Returns value indicating whether the point lies on the left
            // or the right side of the line defined by the segment. The return
            // value is negative for points on the left side, positive for
            // points on the right side and zero for points on the line.
            // Returns zero always if the segment doesn't define a line at all.
            GLfloat testPoint(const ruukku::GLFloatVec2& point) const;

            // Returns scalar s on the range ]0, 1] if this segment intersects
            // target segment. Return value of -1.0 denotes no intersection.
            // The intersection point is given by the equation a + s * getDelta()
            // Cases with point like segments and paraller segments are ignored.
            GLfloat intersect(const Segment& segment) const;
    };

    inline bool Segment::isPoint() const { return a == b; }

    inline ruukku::GLFloatVec2 Segment::getDelta()      const { return b - a; }
    inline ruukku::GLFloatVec2 Segment::getOrthogonal() const { return ruukku::GLFloatVec2(b.y - a.y, a.x - b.x); }

    inline GLfloat Segment::testPoint(const ruukku::GLFloatVec2& point) const {
        const ruukku::GLFloatVec2 offset = point - a;
        return offset.getDot(getOrthogonal());
    }

    // TODO Check whether it makes sense to implement this as a 1D projection.
    inline GLfloat Segment::intersect(const Segment& segment) const {
        if (isPoint() || segment.isPoint()) return -1.0f;

        const GLfloat rayA = segment.testPoint(a);
        const GLfloat rayB = segment.testPoint(b);

        if (rayA >= 0.0f && rayB <= 0.0f) {
            if (rayA == 0.0f && rayB == 0.0f) return 0.0f;

            const GLfloat wallA = testPoint(segment.a);
            const GLfloat wallB = testPoint(segment.b);

            const GLfloat u = std::min(wallA, wallB);
            const GLfloat v = std::max(wallA, wallB);

            if (u <= 0.0f && v >= 0.0f) return rayA / (rayA - rayB);
        }

        return -1.0f;
    }
};

#endif /* RUNRUN_SEGMENT_HPP */


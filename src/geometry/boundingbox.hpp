/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    boundingbox.hpp
 * Created: 2014-07-06
 * Authors: Jani Salo
 */

/*
 * An axis aligned bounding box.
 */

#ifndef RUNRUN_BOUNDINGBOX_HPP
#define RUNRUN_BOUNDINGBOX_HPP

#include <algorithm>
#include "ruukku/opengl/gltypes.hpp"

namespace runrun {
    class BoundingBox {
        public:
            ruukku::GLFloatVec2 min, max;

            BoundingBox() {}
            BoundingBox(const ruukku::GLFloatVec2& min, const ruukku::GLFloatVec2& max);
            BoundingBox(const std::vector< ruukku::GLFloatVec2 >& vertexList);

            bool isNull()  const;
            bool isValid() const;

            ruukku::GLFloatVec2 getSize() const;

            bool operator ==(const BoundingBox& other) const;
            bool operator !=(const BoundingBox& other) const;

            // Neither operator checks for the validity of either bounding box.
            BoundingBox  operator + (const BoundingBox& other) const;
            BoundingBox& operator +=(const BoundingBox& other);

            BoundingBox getRealigned() const;
            BoundingBox getTransformed(const ruukku::GLFloatMat3& transformation) const;

            bool intersect(const BoundingBox& other) const;
            void clip(ruukku::GLFloatVec2& position);

            static BoundingBox createNull();
    };

    inline BoundingBox::BoundingBox(const ruukku::GLFloatVec2& min, const ruukku::GLFloatVec2& max) : min(min), max(max) {}
    inline BoundingBox::BoundingBox(const std::vector< ruukku::GLFloatVec2 >& vertexList) {
        if (vertexList.size() > 0) {
            min = max = vertexList[0];

            for (std::size_t i = 1; i < vertexList.size(); i++) {
                min.x = std::min(min.x, vertexList[i].x);
                min.y = std::min(min.y, vertexList[i].y);
                max.x = std::max(max.x, vertexList[i].x);
                max.y = std::max(max.y, vertexList[i].y);
            }
        }
    }

    inline bool BoundingBox::isNull()  const { return min.x == 0.0f && min.y == 0.0f && max.x == 0.0f && max.y == 0.0f; }
    inline bool BoundingBox::isValid() const { return min.x <= max.x && min.y <= max.y; }

    inline ruukku::GLFloatVec2 BoundingBox::getSize() const { return max - min; }

    inline bool BoundingBox::operator ==(const BoundingBox& box) const { return (min == box.min) && (max == box.max); }
    inline bool BoundingBox::operator !=(const BoundingBox& box) const { return (min != box.min) || (max != box.max); }

    inline BoundingBox BoundingBox::operator +(const BoundingBox& box) const {
        return BoundingBox(
            ruukku::GLFloatVec2(std::min(min.x, box.min.x), std::min(min.y, box.min.y)),
            ruukku::GLFloatVec2(std::max(max.x, box.max.x), std::max(max.y, box.max.y))
        );
    }

    inline BoundingBox& BoundingBox::operator +=(const BoundingBox& box) { return *this = *this + box; }

    inline BoundingBox BoundingBox::getRealigned() const {
        return BoundingBox(
            ruukku::GLFloatVec2(std::min(min.x, max.x), std::min(min.y, max.y)),
            ruukku::GLFloatVec2(std::max(min.x, max.x), std::max(min.y, max.y))
        );
    }

    inline BoundingBox BoundingBox::getTransformed(const ruukku::GLFloatMat3& transformation) const {
        const ruukku::GLFloatVec2 v0 = transformation.transform(min);
        const ruukku::GLFloatVec2 v1 = transformation.transform(min + ruukku::GLFloatVec2(getSize().x, 0.0f));
        const ruukku::GLFloatVec2 v2 = transformation.transform(max);
        const ruukku::GLFloatVec2 v3 = transformation.transform(min + ruukku::GLFloatVec2(0.0f, getSize().y));

        return BoundingBox(
            ruukku::GLFloatVec2(std::min({v0.x, v1.x, v2.x, v3.x}), std::min({v0.y, v1.y, v2.y, v3.y})),
            ruukku::GLFloatVec2(std::max({v0.x, v1.x, v2.x, v3.x}), std::max({v0.y, v1.y, v2.y, v3.y}))
        );
    }

    inline bool BoundingBox::intersect(const BoundingBox& other) const {
        if      (max.x < other.min.x || min.x > other.max.x) return false;
        else if (max.y < other.min.y || min.y > other.max.y) return false;
        return true;
    }

    inline void BoundingBox::clip(ruukku::GLFloatVec2& position) {
        if      (position.x < min.x) position.x = min.x;
        else if (position.x > max.x) position.x = max.x;

        if      (position.y < min.y) position.y = min.y;
        else if (position.y > max.y) position.y = max.y;
    }

    inline BoundingBox BoundingBox::createNull() {
        return BoundingBox(
            ruukku::GLFloatVec2(0.0f, 0.0f),
            ruukku::GLFloatVec2(0.0f, 0.0f)
        );
    }
};

#endif /* RUNRUN_BOUNDINGBOX_HPP */


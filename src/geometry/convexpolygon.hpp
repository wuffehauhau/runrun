/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun.
 *
 * File:    convexpolygon.hpp
 * Created: 2014-07-06
 * Authors: Jani Salo
 */

/*
 * A simple base class for convex polygons.
 */

#ifndef RUNRUN_CONVEXPOLYGON_HPP
#define RUNRUN_CONVEXPOLYGON_HPP

#include <vector>

#include "ruukku/opengl/gltypes.hpp"

#include "boundingbox.hpp"
#include "segment.hpp"
#include "surfaceindex.hpp"

namespace runrun {
    class ConvexPolygon {
        public:
            std::vector< ruukku::GLFloatVec2 > vertexList;
            std::vector< SurfaceIndex > surfaceIndexList;

            virtual ~ConvexPolygon() {}

            void computeBoundingBox();
            const BoundingBox& getBoundingBox() const;

        protected:
            BoundingBox boundingBox;

    };

    inline void ConvexPolygon::computeBoundingBox() { boundingBox = BoundingBox(vertexList); }
    inline const BoundingBox& ConvexPolygon::getBoundingBox() const { return boundingBox; }
};

#endif /* RUNRUN_CONVEXPOLYGON_HPP */


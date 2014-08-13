/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    polygonbuilder.hpp
 * Created: 2014-07-10
 * Authors: Jani Salo
 */

/*
 * A builder for polygons.
 */

#ifndef RUNRUN_POLYGONBUILDER_HPP
#define RUNRUN_POLYGONBUILDER_HPP

#include <vector>

#include "ruukku/opengl/gltypes.hpp"
#include "convexpolygon.hpp"

namespace runrun {
    class PolygonBuilder {
        public:
            void buildBox(
                ConvexPolygon& polygon,
                const ruukku::GLFloatVec2& origo,
                const GLfloat width,
                const GLfloat height
            ) const;

            void buildTriangle(
                ConvexPolygon& polygon,
                const ruukku::GLFloatVec2& a,
                const ruukku::GLFloatVec2& b,
                const ruukku::GLFloatVec2& c
            ) const;

            void buildPolygon(
                ConvexPolygon& polygon,
                const std::vector< ruukku::GLFloatVec2 > vertexList
            ) const;
    };
};

#endif /* RUNRUN_POLYGONBUILDER_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    polygonbuilder.cpp
 * Created: 2014-07-10
 * Authors: Jani Salo
 */

#include <cassert>
#include "polygonbuilder.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    void PolygonBuilder::buildBox(
        ConvexPolygon& polygon,
        const GLFloatVec2& origo,
        const GLfloat width,
        const GLfloat height
    ) const {
        polygon.vertexList = {
            origo,
            origo + GLFloatVec2(width, 0.0f),
            origo + GLFloatVec2(width, height),
            origo + GLFloatVec2(0.0f,  height)
        };

        polygon.surfaceIndexList = { SurfaceIndex(0, 1), SurfaceIndex(1, 2), SurfaceIndex(2, 3), SurfaceIndex(3, 0) };
        polygon.computeBoundingBox();
    }

    void PolygonBuilder::buildTriangle(
        ConvexPolygon& polygon,
        const GLFloatVec2& a,
        const GLFloatVec2& b,
        const GLFloatVec2& c
    ) const {
        polygon.vertexList = { a, b, c };

        polygon.surfaceIndexList = { SurfaceIndex(0, 1), SurfaceIndex(1, 2), SurfaceIndex(2, 0) };
        polygon.computeBoundingBox();
    }

    void PolygonBuilder::buildPolygon(
        ConvexPolygon& polygon,
        const std::vector< ruukku::GLFloatVec2 > vertexList
    ) const {
        if (vertexList.size() < 3) {
            assert(false);
            return;
        }

        polygon.vertexList = vertexList;
        polygon.surfaceIndexList.clear();
        for (size_t index = 0; index < vertexList.size(); index++) {
            polygon.surfaceIndexList.push_back(
                SurfaceIndex(index, (index + 1) < vertexList.size() ? (index + 1) : 0)
            );
        }

        polygon.computeBoundingBox();
    }
};


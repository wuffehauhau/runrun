/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilephysics.cpp
 * Created: 2014-07-13
 * Authors: Jani Salo
 */

#include "ruukku/opengl/gltypes.hpp"
#include "geometry/polygonbuilder.hpp"

#include "tilephysics.hpp"

using namespace ruukku;

namespace runrun {
    TilePhysics::TilePhysics() {
        PolygonBuilder polygonBuilder;
        polygonBuilder.buildBox(collisionPolygonBlock, GLFloatVec2(0.0f, 0.0f), 1.0f, 1.0f);

        const GLFloatVec2 v0(0.0f, 0.0f);
        const GLFloatVec2 v1(1.0f, 0.0f);
        const GLFloatVec2 v2(1.0f, 1.0f);
        const GLFloatVec2 v3(0.0f, 1.0f);

        polygonBuilder.buildTriangle(collisionPolygonSlopeList[0], v0, v1, v3);
        polygonBuilder.buildTriangle(collisionPolygonSlopeList[1], v1, v2, v0);
        polygonBuilder.buildTriangle(collisionPolygonSlopeList[2], v2, v3, v1);
        polygonBuilder.buildTriangle(collisionPolygonSlopeList[3], v3, v0, v2);

        collisionPolygonDefault = collisionPolygonBlock;
    }
};


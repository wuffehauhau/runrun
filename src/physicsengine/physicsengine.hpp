/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    physicsengine.hpp
 * Created: 2014-07-05
 * Authors: Jani Salo
 */

/*
 * Handles physics for the game world.
 */

#ifndef RUNRUN_PHYSICSENGINE_HPP
#define RUNRUN_PHYSICSENGINE_HPP

#include <functional>

#include "ruukku/math/ivec2.hpp"
#include "ruukku/misc/uncopyable.hpp"

#include "algorithm/staticarray2.hpp"
#include "geometry/boundingbox.hpp"
#include "geometry/convexpolygon.hpp"
#include "geometry/intersectionsolution.hpp"
#include "metrics/mapmetrics.hpp"
#include "object/object.hpp"
#include "tile/tilephysics.hpp"
#include "world/world.hpp"

#include "intersectiontype.hpp"
#include "objectphysicsentry.hpp"
#include "tileintersectionentry.hpp"
#include "wallintersectionentry.hpp"

namespace runrun {
    class PhysicsEngine {
        public:
            static GLfloat getMinimumStep()  { return 1.0f / 256.0f; }
            static GLfloat getMinimumTime()  { return 1.0f / 256.0f; }
            static GLfloat getMinimumSpeed() { return 1.0f / 256.0f; }
            static GLfloat getMaximumSpeed() { return 16.0f; }

            static GLfloat getMinimumSpeedSquare() { return getMinimumSpeed() * getMinimumSpeed(); }
            static GLfloat getMaximumSpeedSquare() { return getMaximumSpeed() * getMaximumSpeed(); }

            PhysicsEngine();

            void updateObjects(World* world, const GLfloat stepSize, const GLfloat time);

        private:
            typedef StaticArray2< std::vector< Object* > , MapMetrics::MAP_DIM_IN_CELLS, MapMetrics::MAP_DIM_IN_CELLS > ObjectPresenceMap;

            ObjectPresenceMap objectPresenceMap;
            std::vector< ObjectPhysicsEntry > movingObjectList;

            BoundingBox worldBox;
            std::vector< ConvexPolygon > worldWallList;

            std::vector< TileIntersectionEntry > tileIntersectionList;
            std::vector< WallIntersectionEntry > wallIntersectionList;
            std::vector< IntersectionSolution > intersectionSolutionList;

            TilePhysics tilePhysics;

            void clearObjectPresenceMap();
            void reportObjectPresence(Object* object);
            void removeObjectPresence(Object* object);

            void setWorldBox(const BoundingBox& box);

            bool stepObject(World* world, Object* object, const GLfloat timeConstant);
            ObjectPhysicsEntry computeObjectPhysicsEntry(Object* object, const GLfloat stepSize, const GLfloat time);
    };
};

#endif /* RUNRUN_PHYSICSENGINE_HPP */


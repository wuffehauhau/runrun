/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    physicsengine.cpp
 * Created: 2014-07-05
 * Authors: Jani Salo
 */

#include <algorithm>

#include "algorithm/vectorutil.hpp"
#include "metrics/mapmetrics.hpp"

#include "physicsengine.hpp"
#include "geometry/polygonbuilder.hpp"

// DEBUG
#include <iostream>

using namespace std;
using namespace ruukku;

namespace runrun {
    PhysicsEngine::PhysicsEngine() {}

    void PhysicsEngine::updateObjects(World* world, const GLfloat stepSize, const GLfloat time) {
        static const GLfloat MINIMUM_STEP  = getMinimumStep();
        static const GLfloat MINIMUM_TIME  = getMinimumTime();

        if (stepSize <= getMinimumStep() || time <= getMinimumTime()) {
            assert(false);
            return;
        }

        setWorldBox(world->getBoundingBox());

        clearObjectPresenceMap();
        movingObjectList.clear();

        const MapPhysics physics = world->getPhysics();
        const GLFloatVec2 gravity = GLFloatVec2(0.0f, -1.0f * time * physics.gravitation);

        world->findAllObjects([&](Object& object) {
            object.body().addImpulse(gravity);
            reportObjectPresence(&object);

            ObjectPhysicsEntry entry = computeObjectPhysicsEntry(&object, stepSize, time);
            if (entry.hasStopped()) return;

            movingObjectList.push_back(entry);
        });

        for (ObjectPhysicsEntry& entry : movingObjectList) {
            bool didIntersect = false;

            // Have some sort of hard limit for the number of steps to avoid infinite loops.
            static const int MAX_STEPS = 256 + 1;
            int stepCount = 0;

            while (!entry.hasStopped() && stepCount < MAX_STEPS) {
                didIntersect = stepObject(world, entry.getObject(), entry.getNextStepUpdateDelta());
                if (didIntersect) {
                    entry.payCollisionTime();
                    entry = computeObjectPhysicsEntry(entry.getObject(), stepSize, entry.getTimeLeft());
                }
                else entry.payStepTime();

                stepCount++;
            }

            assert(stepCount < MAX_STEPS);

            Body& body = entry.getObject()->body();
            body.setVelocity(physics.persistence * body.getVelocity());
        }
    }

    void PhysicsEngine::clearObjectPresenceMap() {
        for (vector< Object* >& list : objectPresenceMap.data) {
            list.clear();
        }
    }

    void PhysicsEngine::reportObjectPresence(Object* object) {
        const BoundingBox box = object->body().getCollisionHull().getBoundingBoxTransformed();
        MapMetrics::findIntersectingCellPositions(box, objectPresenceMap.getSize(), [&](const Int2& position) {
            objectPresenceMap[position].push_back(object);
        });
    }

    void PhysicsEngine::removeObjectPresence(Object* object) {
        const BoundingBox box = object->body().getCollisionHull().getBoundingBoxTransformed();
        MapMetrics::findIntersectingCellPositions(box, objectPresenceMap.getSize(), [&](const Int2& position) {
            vector< Object* >& list = objectPresenceMap[position];
            vector< Object* >::iterator it = find(list.begin(), list.end(), object);
            if (it != list.end()) VectorUtil::replaceErase(list, it);
        });
    }

    void PhysicsEngine::setWorldBox(const BoundingBox& box) {
        if (box != worldBox) {
            worldBox = box;

            const GLfloat xSize = 2.0f + box.getSize().x;
            const GLfloat ySize = 2.0f + box.getSize().y;

            const GLFloatVec2 origo(worldBox.min.x - 1.0f, worldBox.min.y - 1.0f);
            const GLFloatVec2 xEdge(worldBox.max.x,        worldBox.min.y - 1.0f);
            const GLFloatVec2 yEdge(worldBox.min.x - 1.0f, worldBox.max.y);

            worldWallList.clear();
            PolygonBuilder polygonBuilder;

            worldWallList.push_back(ConvexPolygon());
            polygonBuilder.buildBox(worldWallList.back(), origo, xSize, 1.0f);
            worldWallList.push_back(ConvexPolygon());
            polygonBuilder.buildBox(worldWallList.back(), origo, 1.0f, ySize);

            worldWallList.push_back(ConvexPolygon());
            polygonBuilder.buildBox(worldWallList.back(), yEdge, xSize, 1.0f);
            worldWallList.push_back(ConvexPolygon());
            polygonBuilder.buildBox(worldWallList.back(), xEdge, 1.0f, ySize);
        }
    }

    bool PhysicsEngine::stepObject(World* world, Object* object, const GLfloat timeConstant) {
        removeObjectPresence(object);
        Body& body = object->body();

        // Limit object speed.
        const GLfloat speedSquare = body.getVelocity().getDot(body.getVelocity());
        if (speedSquare > getMaximumSpeedSquare()) {
            const GLfloat speed = sqrt(speedSquare);
            body.setVelocity((getMaximumSpeed() / speed) * body.getVelocity());
        }

        const GLFloatVec2 oldPosition = body.getPosition();
        const GLfloat     oldRotation = body.getRotation();

        body.update(timeConstant);

        bool didIntersect = false;
        tileIntersectionList.clear();
        wallIntersectionList.clear();

        // DEBUG
        // cout << "Vertices after update: " << endl;
        // for (const CollisionHullEntry& entry : body.getCollisionHull().getEntryList()) {
        //     for (const ConvexPolygon& polygon : entry.convexPolygonList) {
        //         for (const GLFloatVec2& vertex : polygon.vertexList) {
        //             const GLFloatVec2 transformed = body.getTransformation().transform(vertex);
        //             cout << transformed.x << ", " << transformed.y << endl;
        //         }
        //     }
        // }

        world->findTiles(body.getCollisionHull().getBoundingBoxTransformed(), [&](const Int2& position, const Tile& tile) {
            if (!tile.getRecord().hasPhysics()) return;

            const GLFloatMat3 transformation = GLFloatMat3::getTranslation(static_cast< GLfloat >(position.x), static_cast< GLfloat >(position.y));
            const ConvexPolygon& tilePolygon = tilePhysics.getCollisionPolygon(tile.getRecord());

            if (body.getCollisionHull().testIntersection(tilePolygon, transformation)) {
                tileIntersectionList.push_back(TileIntersectionEntry(tile.getRecord(), transformation));
                didIntersect = true;
            }
        });

        for (const ConvexPolygon& polygon : worldWallList) {
            if (body.getCollisionHull().testIntersection(polygon, GLFloatMat3::getIdentity())) {
                wallIntersectionList.push_back(WallIntersectionEntry(polygon));
                didIntersect = true;
            }
        }

        if (didIntersect) {
            const GLFloatVec2 positionDelta = body.getPosition() - oldPosition;
            const GLfloat     rotationDelta = body.getRotation() - oldRotation;

            const GLFloatMat3 transformNew = body.getTransformation();
            const GLFloatMat3 deltaInverse = GLFloatMat3::getRotation(-rotationDelta) * GLFloatMat3::getTranslation(-positionDelta.x, -positionDelta.y);

            body.setPosition(oldPosition);
            body.setRotation(oldRotation);
            body.updateCollisionHullTransformation();

            intersectionSolutionList.clear();
            IntersectionType solutionType = IntersectionType::None;

            for (const TileIntersectionEntry& entry : tileIntersectionList) {
                const ConvexPolygon& tilePolygon = tilePhysics.getCollisionPolygon(entry.record);
                if (body.getCollisionHull().solveIntersection(
                    tilePolygon,
                    transformNew,
                    entry.transformation,
                    deltaInverse * entry.transformation,
                    intersectionSolutionList
                )) solutionType = IntersectionType::Tile;
            }

            for (const WallIntersectionEntry& entry : wallIntersectionList) {
                if (body.getCollisionHull().solveIntersection(
                    entry.wall,
                    transformNew,
                    GLFloatMat3::getIdentity(),
                    deltaInverse,
                    intersectionSolutionList
                )) solutionType = IntersectionType::Wall;
            }

            if (intersectionSolutionList.size() > 0) {
                const GLFloatVec2 collisionNormal = intersectionSolutionList[0].surface.getNormal();

                GLFloatVec2 impulse;
                switch (solutionType) {
                    case IntersectionType::Tile: {
                        impulse = 1.000f * fabs(collisionNormal.getDot(body.getVelocity())) * collisionNormal; break;
                    }
                    case IntersectionType::Wall: {
                        impulse = 1.125f * fabs(collisionNormal.getDot(body.getVelocity())) * collisionNormal; break;
                    }
                }

                body.addImpulse(impulse);
            }
            else {
                // DEBUG
                cout << "Couldn't solve intersection." << endl;

                // TODO Handle this situation.
                body.setVelocity(GLFloatVec2(0.0f, 0.0f));
                assert(false);
            }
        }

        reportObjectPresence(object);
        return didIntersect;
    }

    ObjectPhysicsEntry PhysicsEngine::computeObjectPhysicsEntry(Object* object, const GLfloat stepSize, const GLfloat time) {
        Body& body = object->body();

        const GLFloatVec2 velocity = body.getVelocity();
        const GLfloat speedSquare = velocity.getDot(velocity);
        if (speedSquare <= getMinimumSpeedSquare()) return ObjectPhysicsEntry(object, 0.0f, 1.0f);

        GLfloat speed = min(sqrt(speedSquare), getMaximumSpeed());
        const GLfloat stepTimeCost = stepSize / speed;
        return ObjectPhysicsEntry(object, time, stepTimeCost);
    }
};


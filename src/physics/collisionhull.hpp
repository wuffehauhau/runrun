/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    collisionhull.hpp
 * Created: 2014-07-08
 * Authors: Jani Salo
 */

/*
 * A single monolithic collision hull.
 */

#ifndef RUNRUN_COLLISIONHULL_HPP
#define RUNRUN_COLLISIONHULL_HPP

#include <vector>

#include "ruukku/opengl/gltypes.hpp"
#include "geometry/boundingbox.hpp"
#include "geometry/convexpolygon.hpp"
#include "geometry/intersectionsolution.hpp"
#include "geometry/intersectiontester.hpp"

#include "collisionhullentry.hpp"

namespace runrun {
    class CollisionHull {
        public:
            CollisionHull() : transformation(ruukku::GLFloatMat3::getIdentity()) {}
            virtual ~CollisionHull() {}

            bool isEmpty() const;

            void addEntry(const CollisionHullEntry& entry);
            const std::vector< CollisionHullEntry >& getEntryList() const;

            void computeBoundingBox();

            const BoundingBox& getBoundingBox()            const;
            const BoundingBox& getBoundingBoxTransformed() const;

            // Used in intersection tests.
            void setCurrentTransformation(const ruukku::GLFloatMat3& transformation);
            ruukku::GLFloatMat3 getCurrentTransformation() const;

            bool testIntersection(const ConvexPolygon& other, const ruukku::GLFloatMat3& transformationOther) const;
            bool testIntersection(const CollisionHull& other) const;

            bool solveIntersection(
                const ConvexPolygon& other,
                const ruukku::GLFloatMat3& transformNew,
                const ruukku::GLFloatMat3& transformOther,
                const ruukku::GLFloatMat3& transformOtherRelative,
                std::vector< IntersectionSolution >& solutionList
            ) const;

        private:
            static IntersectionTester intersectionTester;

            std::vector< CollisionHullEntry > entryList;
            ruukku::GLFloatMat3 transformation;

            BoundingBox boundingBox;
            BoundingBox boundingBoxTransformed;
    };

    inline bool CollisionHull::isEmpty() const { return entryList.size() == 0; }

    inline void CollisionHull::addEntry(const CollisionHullEntry& entry) { entryList.push_back(entry); }
    inline const std::vector< CollisionHullEntry >& CollisionHull::getEntryList() const { return entryList; }

    inline void CollisionHull::computeBoundingBox() {
        if (entryList.size() == 0) boundingBox = BoundingBox::createNull();
        else {
            boundingBox = entryList[0].getBoundingBox();
            for (std::size_t i = 1; i < entryList.size(); i++) {
                boundingBox += entryList[i].getBoundingBox();
            }
        }

        boundingBoxTransformed = boundingBox.getTransformed(transformation);
    }

    inline const BoundingBox& CollisionHull::getBoundingBox()            const { return boundingBox; }
    inline const BoundingBox& CollisionHull::getBoundingBoxTransformed() const { return boundingBoxTransformed; }

    inline void CollisionHull::setCurrentTransformation(const ruukku::GLFloatMat3& transformation) {
        this->transformation = transformation;
        boundingBoxTransformed = boundingBox.getTransformed(this->transformation);
    }

    inline ruukku::GLFloatMat3 CollisionHull::getCurrentTransformation() const { return transformation; }

    inline bool CollisionHull::testIntersection(const ConvexPolygon& other, const ruukku::GLFloatMat3& transformationOther) const {
        const BoundingBox otherBoundingBoxTransformed = other.getBoundingBox().getTransformed(transformationOther);
        if (!boundingBoxTransformed.intersect(otherBoundingBoxTransformed)) return false;

        for (const CollisionHullEntry& entry : entryList) {
            const BoundingBox entryBoundingBoxTransformed = entry.getBoundingBox().getTransformed(transformation);
            if (!entryBoundingBoxTransformed.intersect(otherBoundingBoxTransformed)) continue;

            for (const ConvexPolygon& polygon : entry.convexPolygonList) {
                const BoundingBox polygonBoundingBoxTransformed = polygon.getBoundingBox().getTransformed(transformation);

                if (!polygonBoundingBoxTransformed.intersect(otherBoundingBoxTransformed)) continue;
                else if (intersectionTester.testIntersection(polygon, other, transformation, transformationOther)) return true;
            }
        }

        return false;
    }

    inline bool CollisionHull::testIntersection(const CollisionHull& other) const {
        if (!boundingBoxTransformed.intersect(other.getBoundingBoxTransformed())) return false;

        for (const CollisionHullEntry& entry : other.getEntryList()) {
            for (const ConvexPolygon& polygon : entry.convexPolygonList) {
                if (testIntersection(polygon, other.getCurrentTransformation())) return true;
            }
        }

        return false;
    }

    inline bool CollisionHull::solveIntersection(
        const ConvexPolygon& other,
        const ruukku::GLFloatMat3& transformNew,
        const ruukku::GLFloatMat3& transformOther,
        const ruukku::GLFloatMat3& transformOtherRelative,
        std::vector< IntersectionSolution >& solutionList
    ) const {
        bool didIntersect = false;

        for (const CollisionHullEntry& entry : getEntryList()) {
            for (const ConvexPolygon& polygon : entry.convexPolygonList) {
                if (intersectionTester.solveIntersection(
                    polygon,
                    other,
                    transformation,
                    transformNew,
                    transformOther,
                    transformOtherRelative,
                    solutionList
                )) didIntersect = true;
            }
        }

        return didIntersect;
    }
};

#endif /* RUNRUN_COLLISIONHULL_HPP */


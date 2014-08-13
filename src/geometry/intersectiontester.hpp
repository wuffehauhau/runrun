/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    intersectiontester.hpp
 * Created: 2014-07-06
 * Authors: Jani Salo
 */

/*
 * Collection of static methods for testing intersections between shapes.
 */

#ifndef RUNRUN_INTERSECTIONTESTER_HPP
#define RUNRUN_INTERSECTIONTESTER_HPP

#include "ruukku/opengl/gltypes.hpp"

#include "convexpolygon.hpp"
#include "segment.hpp"
#include "surfaceindex.hpp"
#include "intersectionsolution.hpp"

namespace runrun {
    class IntersectionTester {
        public:
            bool testIntersection(
                const ConvexPolygon& polygonA,
                const ConvexPolygon& polygonB,
                const ruukku::GLFloatMat3& transformA,
                const ruukku::GLFloatMat3& transformB
            );

            bool solveIntersection(
                const ConvexPolygon& polygonA,
                const ConvexPolygon& polygonB,
                const ruukku::GLFloatMat3& transformOldA,
                const ruukku::GLFloatMat3& transformNewA,
                const ruukku::GLFloatMat3& transformB,
                const ruukku::GLFloatMat3& transformRelativeB,
                std::vector< IntersectionSolution >& solutionList
            );

        private:
            std::vector< ruukku::GLFloatVec2 > vertexCacheA;
            std::vector< ruukku::GLFloatVec2 > vertexCacheB;

            std::vector< Segment > segmentCacheA;
            std::vector< Segment > segmentCacheB;

            bool intersectVertexLists(
                const std::vector< ruukku::GLFloatVec2 >& vertexListA,
                const std::vector< ruukku::GLFloatVec2 >& vertexListB,
                const std::vector< SurfaceIndex >& surfaceList
            ) const;

            void projectVertexList(
                const std::vector< ruukku::GLFloatVec2 >& vertexList,
                const ruukku::GLFloatVec2& axis,
                GLfloat& projMin,
                GLfloat& projMax
            ) const;

            void buildRaysAndWalls(
                const std::vector< ruukku::GLFloatVec2 >& vertexList,
                const ConvexPolygon targetPolygon,
                const ruukku::GLFloatMat3& transformOld,
                const ruukku::GLFloatMat3& transformNew,
                const ruukku::GLFloatMat3& transformTargetPolygon,
                std::vector< Segment >& rayList,
                std::vector< Segment >& wallList
            );

            bool intersectRaysToWalls(
                const std::vector< Segment >& rayList,
                const std::vector< Segment >& wallList,
                std::vector< IntersectionSolution >& solutionList,
                const GLfloat surfaceDir
            ) const;
    };
};

#endif /* RUNRUN_INTERSECTIONTESTER_HPP */


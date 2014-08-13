/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    intersectiontester.cpp
 * Created: 2014-07-07
 * Authors: Jani Salo
 */

#include <algorithm>
#include "intersectiontester.hpp"

// DEBUG
// #include <iostream>

using namespace std;
using namespace ruukku;

namespace runrun {
    bool IntersectionTester::testIntersection(
        const ConvexPolygon& polygonA,
        const ConvexPolygon& polygonB,
        const GLFloatMat3& transformA,
        const GLFloatMat3& transformB
    ) {
        vertexCacheA.clear();
        vertexCacheB.clear();

        for (const GLFloatVec2& vertex : polygonA.vertexList) vertexCacheA.push_back(transformA.transform(vertex));
        for (const GLFloatVec2& vertex : polygonB.vertexList) vertexCacheB.push_back(transformB.transform(vertex));

        if (!intersectVertexLists(vertexCacheA, vertexCacheB, polygonA.surfaceIndexList)) return false;
        if (!intersectVertexLists(vertexCacheB, vertexCacheA, polygonB.surfaceIndexList)) return false;

        return true;
    }

    bool IntersectionTester::solveIntersection(
        const ConvexPolygon& polygonA,
        const ConvexPolygon& polygonB,
        const GLFloatMat3& transformOldA,
        const GLFloatMat3& transformNewA,
        const GLFloatMat3& transformB,
        const GLFloatMat3& transformRelativeB,
        vector< IntersectionSolution >& solutionList
    ) {
        bool didIntersect = false;

        segmentCacheA.clear();
        segmentCacheB.clear();

        buildRaysAndWalls(
            polygonA.vertexList,
            polygonB,
            transformOldA,
            transformNewA,
            transformB,
            segmentCacheA,
            segmentCacheB
        );

        if (intersectRaysToWalls(segmentCacheA, segmentCacheB, solutionList, 1.0f)) didIntersect = true;

        segmentCacheA.clear();
        segmentCacheB.clear();

        buildRaysAndWalls(
            polygonB.vertexList,
            polygonA,
            transformB,
            transformRelativeB,
            transformOldA,
            segmentCacheB,
            segmentCacheA
        );

        if (intersectRaysToWalls(segmentCacheB, segmentCacheA, solutionList, -1.0f)) didIntersect = true;

        return didIntersect;
    }

    bool IntersectionTester::intersectVertexLists(
        const vector< GLFloatVec2 >& vertexListA,
        const vector< GLFloatVec2 >& vertexListB,
        const vector< SurfaceIndex >& surfaceList
    ) const {
        for (const SurfaceIndex& surfaceIndex : surfaceList) {
            const Segment surface(vertexListA[surfaceIndex.a], vertexListA[surfaceIndex.b]);

            bool isInside = false;
            for (const GLFloatVec2 vertex : vertexListB) {
                if (surface.testPoint(vertex) <= 0.0f) {
                    isInside = true;
                    break;
                }
            }

            if (!isInside) return false;
        }

        return true;
    }

    void IntersectionTester::projectVertexList(
        const vector< GLFloatVec2 >& vertexList,
        const GLFloatVec2& axis,
        GLfloat& projMin,
        GLfloat& projMax
    ) const {
        for (const GLFloatVec2& vertex : vertexList) {
            const GLfloat p = axis.getDot(vertex);

            projMin = min(p, projMin);
            projMax = max(p, projMax);
        }
    }

    void IntersectionTester::buildRaysAndWalls(
        const vector< GLFloatVec2 >& vertexList,
        const ConvexPolygon targetPolygon,
        const GLFloatMat3& transformOld,
        const GLFloatMat3& transformNew,
        const GLFloatMat3& transformTargetPolygon,
        vector< Segment >& rayList,
        vector< Segment >& wallList
    ) {
        for (const GLFloatVec2& vertex : vertexList) {
            const GLFloatVec2 a = transformOld.transform(vertex);
            const GLFloatVec2 b = transformNew.transform(vertex);
            rayList.push_back(Segment(a, b));
        }

        vertexCacheB.clear();

        for (const GLFloatVec2& vertex : targetPolygon.vertexList) vertexCacheB.push_back(transformTargetPolygon.transform(vertex));
        for (const SurfaceIndex& surfaceIndex : targetPolygon.surfaceIndexList) {
            wallList.push_back(Segment(vertexCacheB[surfaceIndex.a], vertexCacheB[surfaceIndex.b]));
        }
    }

    bool IntersectionTester::intersectRaysToWalls(
        const vector< Segment >& rayList,
        const vector< Segment >& wallList,
        vector< IntersectionSolution >& solutionList,
        const GLfloat surfaceDir
    ) const {
        bool didIntersect = false;

        for (const Segment& wall : wallList) {
            for (const Segment& ray : rayList) {
                // DEBUG
                // cout << "Wall:" << wall.a.x << ", " << wall.a.y << "; " << wall.b.x << ", " << wall.b.y << endl;
                // cout << "Ray: " << ray.a.x << ", " << ray.a.y << "; " << ray.b.x << ", " << ray.b.y << endl;
                // cout << "Ray local: " << fmod(ray.a.x, 1.0f) << ", " << fmod(ray.a.y, 1.0f) << "; " << fmod(ray.b.x, 1.0f) << ", " << fmod(ray.b.y, 1.0f) << endl;
                // cout << "Ray manhattan: " << fmod(ray.a.x, 1.0f) + fmod(ray.a.y, 1.0f) << "; " << fmod(ray.b.x, 1.0f) + fmod(ray.b.y, 1.0f) << endl;

                // DEBUG
                // const GLfloat testA = wall.testPoint(ray.a);
                // const GLfloat testB = wall.testPoint(ray.b);
                // if (testA >= 0.0f && testB <= 0.0f) {
                //    cout << "Ray test: " << testA << ", " << testB << endl;
                // }

                const GLfloat relativeDistance = ray.intersect(wall);

                if (relativeDistance != -1.0f) {
                    didIntersect = true;

                    const GLFloatVec2 delta = relativeDistance * ray.getDelta();
                    const GLfloat squareOfDistance = delta.getDot(delta);

                    bool addSolution = false;
                    if (solutionList.size() == 0) {
                        addSolution = true;
                    }
                    else if (solutionList.front().squareOfDistance >= squareOfDistance) {
                        addSolution = true;
                        if (solutionList.front().squareOfDistance > squareOfDistance) {
                            solutionList.clear();
                        }
                    }

                    if (addSolution) {
                        solutionList.push_back(
                            IntersectionSolution(
                                squareOfDistance,
                                ray.a + delta * ray.b,
                                surfaceDir * wall.getOrthogonal()
                            )
                        );
                    }
                }
            }
        }

        return didIntersect;
    }
};


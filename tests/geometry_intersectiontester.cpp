/*
 * File:    segment.cpp
 * Created: 2014-07-06
 * Authors: Jani Salo
 */

#include <stdlib.h>
#include <iostream>

#include "src/geometry/polygonbuilder.hpp"
#include "src/geometry/intersectiontester.hpp"

void testIntersect() {
    runrun::PolygonBuilder polygonBuilder;

    runrun::ConvexPolygon square;
    polygonBuilder.buildBox(square, ruukku::GLFloatVec2(-1.0f, -1.0f), 2.0f, 2.0f);

    ruukku::GLFloatMat3 iMat  = ruukku::GLFloatMat3::getIdentity();
    ruukku::GLFloatMat3 tMatA = ruukku::GLFloatMat3::getTranslation( 2.1f,  0.0f);
    ruukku::GLFloatMat3 tMatB = ruukku::GLFloatMat3::getTranslation(-1.9f, -1.9f);
    ruukku::GLFloatMat3 rMat  = ruukku::GLFloatMat3::getRotation(45.0f);

    runrun::IntersectionTester intersectionTester;

    const bool resultA = intersectionTester.testIntersection(square, square, iMat, tMatA);
    const bool resultB = intersectionTester.testIntersection(square, square, iMat, tMatA * rMat);
    const bool resultC = intersectionTester.testIntersection(square, square, iMat, tMatB * rMat);

    if      (resultA != false) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_intersectiontester) message=resultA" << std::endl;
    else if (resultB != true)  std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_intersectiontester) message=resultB" << std::endl;
    else if (resultC != false) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_intersectiontester) message=resultC" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% geometry_intersectiontester" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testIntersect (geometry_intersectiontester)" << std::endl;
    testIntersect();
    std::cout << "%TEST_FINISHED% time=0 testIntersect (geometry_intersectiontester)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


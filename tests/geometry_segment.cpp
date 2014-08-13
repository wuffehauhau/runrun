/*
 * File:    segment.cpp
 * Created: 2014-07-04
 * Authors: Jani Salo
 */

#include <stdlib.h>
#include <iostream>

#include "src/geometry/segment.hpp"

void testIntersect() {
    const ruukku::GLFloatVec2 pointA( 0.0f,  0.0f);
    const ruukku::GLFloatVec2 pointB( 6.0f,  0.0f);
    const ruukku::GLFloatVec2 pointC( 6.0f,  4.0f);
    const ruukku::GLFloatVec2 pointD( 0.0f,  4.0f);
    const ruukku::GLFloatVec2 pointE(-3.0f, -2.0f);
    const ruukku::GLFloatVec2 pointF( 3.0f,  2.0f);

    runrun::Segment segmentA(pointA, pointC);
    runrun::Segment segmentB(pointB, pointD);
    runrun::Segment segmentC(pointD, pointA);
    runrun::Segment segmentD(pointB, pointC);
    runrun::Segment segmentE(pointE, pointF);

    const GLfloat resultA = segmentA.intersect(segmentB);
    const GLfloat resultB = segmentB.intersect(segmentA);
    const GLfloat resultC = segmentC.intersect(segmentD);
    const GLfloat resultD = segmentE.intersect(segmentC);
    const GLfloat resultE = segmentE.intersect(segmentB);
    const GLfloat resultF = segmentB.intersect(segmentE);
    const GLfloat resultG = segmentE.intersect(segmentA);
    const GLfloat resultH = segmentA.intersect(segmentC);

    if      (resultA !=  0.5f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultA: " << resultA << std::endl;
    else if (resultB !=  0.5f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultB: " << resultB << std::endl;
    else if (resultC != -1.0f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultC: " << resultC << std::endl;
    else if (resultD !=  0.5f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultD: " << resultD << std::endl;
    else if (resultE !=  1.0f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultE: " << resultE << std::endl;
    else if (resultF !=  0.5f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultF: " << resultF << std::endl;
    else if (resultG != -1.0f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultG: " << resultG << std::endl;
    else if (resultH !=  0.0f) std::cout << "%TEST_FAILED% time=0 testname=testIntersect (geometry_segment) message=resultH: " << resultH << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% geometry_segment" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testIntersect (geometry_segment)" << std::endl;
    testIntersect();
    std::cout << "%TEST_FINISHED% time=0 testIntersect (geometry_segment)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


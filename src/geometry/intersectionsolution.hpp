/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    intersectionsolution.hpp
 * Created: 2014-07-19
 * Authors: Jani Salo
 */

/*
 * A simple class for storing exact intersection information.
 */

#ifndef RUNRUN_INTERSECTIONSOLUTION_HPP
#define RUNRUN_INTERSECTIONSOLUTION_HPP

namespace runrun {
    class IntersectionSolution {
        public:
            GLfloat squareOfDistance;
            ruukku::GLFloatVec2 position;
            ruukku::GLFloatVec2 surface;

            IntersectionSolution() {}
            IntersectionSolution(
                const GLfloat squareOfDistance,
                const ruukku::GLFloatVec2& position,
                const ruukku::GLFloatVec2& surface
            );
    };

    inline IntersectionSolution::IntersectionSolution(
        const GLfloat squareOfDistance,
        const ruukku::GLFloatVec2& position,
        const ruukku::GLFloatVec2& surface
    ) :
        squareOfDistance (squareOfDistance),
        position         (position),
        surface          (surface)
    {}
};

#endif /* RUNRUN_INTERSECTIONSOLUTION_HPP */


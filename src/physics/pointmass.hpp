/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    pointmass.hpp
 * Created: 2014-06-13
 * Authors: Jani Salo
 */

/*
 * A simple representation of a point mass.
 * Impulse based or something, i.e. devoid of any fancy numeric integration.
 */

#ifndef RUNRUN_POINTMASS_HPP
#define RUNRUN_POINTMASS_HPP

#include "ruukku/opengl/gltypes.hpp"
#include "body.hpp"

namespace runrun {
    class PointMass : public Body {
        public:
            PointMass() { properties.set(Body::Property::PointMass); }
            PointMass(
                const GLfloat mass,
                const ruukku::GLFloatVec2 position,
                const ruukku::GLFloatVec2 velocity
            );

            void addImpulse(const ruukku::GLFloatVec2& impulse);

            ruukku::GLFloatVec2 getCenterOfMass() const;
            GLfloat getMomentOfInertia(const ruukku::GLFloatVec2& position) const;
    };

    inline PointMass::PointMass(
        const GLfloat mass,
        const ruukku::GLFloatVec2 position,
        const ruukku::GLFloatVec2 velocity
    ) : Body(mass, position, velocity) { properties.set(Body::Property::PointMass); }


    inline void PointMass::addImpulse(const ruukku::GLFloatVec2& impulse) { velocity += (1.0f / mass) * impulse; }
};

#endif /* RUNRUN_POINTMASS_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    material.hpp
 * Created: 2014-07-07
 * Authors: Jani Salo
 */

/*
 * Simple class describing properties of a material
 */

#ifndef RUNRUN_MATERIAL_HPP
#define RUNRUN_MATERIAL_HPP

namespace runrun {
    class Material {
        public:
            GLfloat restitution;
            GLfloat staticResistance;
            GLfloat dynamicFriction;

            Material() {}
            Material(
                const GLfloat restitution,
                const GLfloat staticResistance,
                const GLfloat dynamicFriction
            ) :
                restitution      (restitution),
                staticResistance (staticResistance),
                dynamicFriction  (dynamicFriction),
            {}
    };
};

#endif /* RUNRUN_MATERIAL_HPP */


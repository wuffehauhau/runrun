/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mapphysics.hpp
 * Created: 2014-07-27
 * Authors: Jani Salo
 */

/*
 * Simple description of physical constants for a map.
 */

#ifndef RUNRUN_MAPPHYSICS_HPP
#define RUNRUN_MAPPHYSICS_HPP

namespace runrun {
    class MapPhysics {
        public:
            GLfloat persistence;
            GLfloat gravitation;

            MapPhysics() {}
            MapPhysics(
                const GLfloat persistence,
                const GLfloat gravitation
            ) : persistence(persistence), gravitation(gravitation) {}
    };
};

#endif /* RUNRUN_MAPPHYSICS_HPP */


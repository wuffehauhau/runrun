/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    object.hpp
 * Created: 2014-06-10
 * Authors: Jani Salo
 */

/*
 * Base class for game objects.
 */

#ifndef RUNRUN_OBJECT_HPP
#define RUNRUN_OBJECT_HPP

#include "ruukku/misc/uncopyable.hpp"
#include "ruukku/opengl/gltypes.hpp"

#include "frame/objectframestate.hpp"
#include "geometry/boundingbox.hpp"
#include "physics/body.hpp"
#include "physics/collisionhull.hpp"

namespace runrun {
    class Object : public ruukku::Uncopyable {
        public:
            virtual ~Object() {}

        	virtual void updateState() = 0;
        	virtual void updateFrameState() = 0;

            virtual const ObjectFrameState& getFrameState() const = 0;

            virtual const Body& body() const = 0;
            virtual       Body& body() = 0;
    };
};

#endif /* RUNRUN_OBJECT_HPP */


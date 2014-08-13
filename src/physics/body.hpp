/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    body.hpp
 * Created: 2014-07-06
 * Authors: Jani Salo
 */

/*
 * Interface for physical bodies.
 */

#ifndef RUNRUN_BODY_HPP
#define RUNRUN_BODY_HPP

#include "ruukku/math/vec2.hpp"
#include "algorithm/flags.hpp"

#include "collisionhull.hpp"

namespace runrun {
    class Body {
        public:
            enum class Property {
                None      = 0,
                PointMass = 1
            };

            typedef Flags< Property > Properties;

            Body() {}
            Body(
                const GLfloat              mass,
                const ruukku::GLFloatVec2& position,
                const ruukku::GLFloatVec2& velocity,
                const GLfloat              rotation      = 0.0f,
                const GLfloat              rotationSpeed = 0.0f
            );

            virtual ~Body() {}

            Properties getProperties() const;
            void update(const GLfloat time);

            virtual void addImpulse(const ruukku::GLFloatVec2& impulse) = 0;

            // NOTE Left here for future implementation of bodies with rotational physics.
            // virtual ruukku::GLFloatVec2 getCenterOfMass() const;
            // virtual GLfloat getMomentOfInertia(const ruukku::GLFloatVec2& position) const;

            GLfloat             getMass()          const;
            ruukku::GLFloatVec2 getPosition()      const;
            ruukku::GLFloatVec2 getVelocity()      const;
            GLfloat             getRotation()      const;
            GLfloat             getRotationSpeed() const;

            void setMass          (const GLfloat              mass);
            void setPosition      (const ruukku::GLFloatVec2& position);
            void setVelocity      (const ruukku::GLFloatVec2& velocity);
            void setRotation      (const GLfloat              rotation);
            void setRotationSpeed (const GLfloat              rotationSpeed);

            GLfloat getSpeed() const;
            ruukku::GLFloatMat3 getTransformation() const;

            void setCollisionHull(const CollisionHull& hull);
            const CollisionHull& getCollisionHull() const;

            void updateCollisionHullTransformation();

        protected:
            Properties properties;

            GLfloat mass;
            ruukku::GLFloatVec2 position;
            ruukku::GLFloatVec2 velocity;

            GLfloat rotation;
            GLfloat rotationSpeed;

            CollisionHull collisionHull;
    };

    inline Body::Body(
        const GLfloat              mass,
        const ruukku::GLFloatVec2& position,
        const ruukku::GLFloatVec2& velocity,
        const GLfloat              rotation,
        const GLfloat              rotationSpeed
    ) :
        mass(mass),
        position(position),
        velocity(velocity),
        rotation(rotation),
        rotationSpeed(rotationSpeed)
    {
        updateCollisionHullTransformation();
    }

    inline Body::Properties Body::getProperties() const { return properties; }

    inline void Body::update(const GLfloat time) {
        position += time * velocity;
        rotation += time * rotationSpeed;
        updateCollisionHullTransformation();
    }

    // inline ruukku::GLFloatVec2 Body::getCenterOfMass() const { return position; }
    // inline GLfloat Body::getMomentOfInertia(const ruukku::GLFloatVec2& position) const { return mass; }

    inline GLfloat             Body::getMass()          const { return mass; }
    inline ruukku::GLFloatVec2 Body::getPosition()      const { return position; }
    inline ruukku::GLFloatVec2 Body::getVelocity()      const { return velocity; }
    inline GLfloat             Body::getRotation()      const { return rotation; }
    inline GLfloat             Body::getRotationSpeed() const { return rotationSpeed; }

    inline void Body::setMass          (const GLfloat mass)                  { this->mass          = mass; }
    inline void Body::setPosition      (const ruukku::GLFloatVec2& position) { this->position      = position; }
    inline void Body::setVelocity      (const ruukku::GLFloatVec2& velocity) { this->velocity      = velocity; }
    inline void Body::setRotation      (const GLfloat rotation)              { this->rotation      = rotation; }
    inline void Body::setRotationSpeed (const GLfloat rotationSpeed)         { this->rotationSpeed = rotationSpeed; }

    inline GLfloat Body::getSpeed() const { return velocity.getLength(); }

    inline ruukku::GLFloatMat3 Body::getTransformation() const {
        if (rotation == 0.0f) {
            return ruukku::GLFloatMat3::getTranslation(position.x, position.y);
        }
        else {
            return (
                ruukku::GLFloatMat3::getTranslation (position.x, position.y) *
                ruukku::GLFloatMat3::getRotation    (rotation)
            );
        }
    }

    inline void Body::setCollisionHull(const CollisionHull& hull) {
        collisionHull = hull;
        updateCollisionHullTransformation();
    }

    inline const CollisionHull& Body::getCollisionHull() const { return collisionHull; }

    inline void Body::updateCollisionHullTransformation() {
        collisionHull.setCurrentTransformation(getTransformation());
    }
};

#endif /* RUNRUN_BODY_HPP */


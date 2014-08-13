/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectphysicsentry.hpp
 * Created: 2014-07-11
 * Authors: Jani Salo
 */

/*
 * Contains a record of object information used for computing physics.
 */

#ifndef RUNRUN_OBJECTPHYSICSENTRY_HPP
#define RUNRUN_OBJECTPHYSICSENTRY_HPP

#include <cassert>
#include "object/object.hpp"

namespace runrun {
    class ObjectPhysicsEntry {
        public:
            ObjectPhysicsEntry(
                Object *object             = nullptr,
                const GLfloat timeLeft     = 0.0f,
                const GLfloat stepTimeCost = 1.0f
            );

            Object* getObject();

            GLfloat getTimeLeft() const;
            GLfloat getStepTimeCost() const;
            GLfloat getCollisionTimeCost() const;
            GLfloat getNextStepUpdateDelta() const;

            void setStepTimeCost(const GLfloat cost);

            bool hasStopped() const;
            void stop();

            void payStepTime();
            void payCollisionTime();

        private:
            Object* object;

            GLfloat timeLeft;
            GLfloat stepTimeCost;
            GLfloat stepUpdateDelta;
    };

    inline ObjectPhysicsEntry::ObjectPhysicsEntry(Object *object, const GLfloat time, const GLfloat stepTimeCost) :
        object(object), timeLeft(time), stepTimeCost(stepTimeCost)
    {}

    inline Object* ObjectPhysicsEntry::getObject() { return object; }

    inline GLfloat ObjectPhysicsEntry::getTimeLeft() const { return timeLeft; }
    inline GLfloat ObjectPhysicsEntry::getStepTimeCost() const { return stepTimeCost; }
    inline GLfloat ObjectPhysicsEntry::getCollisionTimeCost() const { return 1.0f / 16.0f; }
    inline GLfloat ObjectPhysicsEntry::getNextStepUpdateDelta() const { return timeLeft < stepTimeCost ? timeLeft : stepTimeCost; }

    inline void ObjectPhysicsEntry::setStepTimeCost(const GLfloat cost) { stepTimeCost = cost; }

    inline bool ObjectPhysicsEntry::hasStopped() const { return timeLeft <= 0.0f; }
    inline void ObjectPhysicsEntry::stop() { timeLeft = 0.0f; }

    inline void ObjectPhysicsEntry::payStepTime() { timeLeft -= getStepTimeCost(); }
    inline void ObjectPhysicsEntry::payCollisionTime() { timeLeft -= getCollisionTimeCost(); }
};

#endif /* RUNRUN_OBJECTPHYSICSENTRY_HPP */


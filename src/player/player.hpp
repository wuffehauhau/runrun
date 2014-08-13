/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    player.hpp
 * Created: 2014-06-10
 * Authors: Jani Salo
 */

/*
 * Class for the player object.
 */

#ifndef RUNRUN_PLAYER_HPP
#define RUNRUN_PLAYER_HPP

#include "frame/objectframeevent.hpp"
#include "object/object.hpp"
#include "physics/collisionhull.hpp"
#include "physics/pointmass.hpp"
#include "playeranimation.hpp"
#include "playerdirection.hpp"
#include "playerjump.hpp"
#include "playerstride.hpp"

namespace runrun {
    class Player : public Object {
        public:
            Player(const PlayerAnimation* animation);

            void setCurrentJump   (const PlayerJump   jump);
            void setCurrentStride (const PlayerStride stride);

        	void updateState();
        	void updateFrameState();

            const ObjectFrameState& getFrameState() const;

            const Body& body() const;
                  Body& body();

            void walkLeft();
            void walkRight();

        private:
            const PlayerAnimation* animation;
            ObjectFrameState frameState;

            PointMass centerOfMass;

            PlayerJump      currentJump, oldJump;
            PlayerStride    currentStride;
            PlayerDirection currentDirection;

            ObjectFrameEvent bodyAnimationState;
            ObjectFrameEvent legsAnimationState;
            ObjectFrameEvent headAnimationState;
            ObjectFrameEvent tailAnimationState;
    };

    inline const ObjectFrameState& Player::getFrameState() const { return frameState; }

    inline const Body& Player::body() const { return centerOfMass; }
    inline       Body& Player::body()       { return centerOfMass; }
};

#endif /* RUNRUN_PLAYER_HPP */


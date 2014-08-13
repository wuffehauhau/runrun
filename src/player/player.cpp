/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    player.cpp
 * Created: 2014-06-10
 * Authors: Jani Salo
 */

#include "geometry/convexpolygon.hpp"
#include "geometry/polygonbuilder.hpp"
#include "physics/collisionhull.hpp"
#include "time/worldtime.hpp"

#include "player.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    Player::Player(const PlayerAnimation* animation) :
        animation(animation),
        centerOfMass(1.0f, GLFloatVec2(0.0f, 0.0f), GLFloatVec2(0.0f, 0.0f)),
        currentDirection(PlayerDirection::Right),
        currentStride(PlayerStride::Idle),
        currentJump(PlayerJump::Idle)
    {
        // TODO Collision hull should probably be generated from a data file.
        ConvexPolygon box;
        PolygonBuilder polygonBuilder;
        polygonBuilder.buildBox(box, GLFloatVec2(-0.25f, -0.375f), 0.5f, 2.125f);

        CollisionHullEntry hullEntry;
        hullEntry.convexPolygonList.push_back(box);
        hullEntry.computeBoundingBox();

        CollisionHull hull;
        hull.addEntry(hullEntry);
        hull.computeBoundingBox();
        centerOfMass.setCollisionHull(hull);
    }

    void Player::setCurrentJump(const PlayerJump jump) {
        oldJump = currentJump;
        currentJump = jump;
    }

    void Player::setCurrentStride(const PlayerStride stride) {
        currentStride = stride;

        if      (currentStride == PlayerStride::WalkLeft)  currentDirection = PlayerDirection::Left;
        else if (currentStride == PlayerStride::WalkRight) currentDirection = PlayerDirection::Right;
    }

    void Player::updateState() {
        // TODO Implement this properly.
        static const GLfloat MAX_SPEED = 0.16f;

        if      (currentStride == PlayerStride::WalkLeft  && centerOfMass.getVelocity().x > -MAX_SPEED) centerOfMass.addImpulse(GLFloatVec2(-0.05f, 0.0f));
        else if (currentStride == PlayerStride::WalkRight && centerOfMass.getVelocity().x <  MAX_SPEED) centerOfMass.addImpulse(GLFloatVec2( 0.05f, 0.0f));

        if (currentJump == PlayerJump::Jump && oldJump == PlayerJump::Idle) centerOfMass.addImpulse(GLFloatVec2(0.0f, 0.48f));
    }

    void Player::updateFrameState() {
        PlayerAnimation::Body newBodyAnimation = PlayerAnimation::Body::Empty;
        PlayerAnimation::Legs newLegsAnimation = PlayerAnimation::Legs::Empty;
        PlayerAnimation::Head newHeadAnimation = PlayerAnimation::Head::Empty;
        PlayerAnimation::Tail newTailAnimation = PlayerAnimation::Tail::Empty;

        if (currentDirection == PlayerDirection::Left) {
            newBodyAnimation = PlayerAnimation::Body::DefaultLeft;
            newHeadAnimation = PlayerAnimation::Head::DefaultLeft;
            newTailAnimation = PlayerAnimation::Tail::DefaultLeft;
        }
        else if (currentDirection == PlayerDirection::Right) {
            newBodyAnimation = PlayerAnimation::Body::DefaultRight;
            newHeadAnimation = PlayerAnimation::Head::DefaultRight;
            newTailAnimation = PlayerAnimation::Tail::DefaultRight;
        }

        if      (currentStride == PlayerStride::WalkLeft)  newLegsAnimation = PlayerAnimation::Legs::WalkLeft;
        else if (currentStride == PlayerStride::WalkRight) newLegsAnimation = PlayerAnimation::Legs::WalkRight;
        else {
            if      (currentDirection == PlayerDirection::Left)  newLegsAnimation = PlayerAnimation::Legs::IdleLeft;
            else if (currentDirection == PlayerDirection::Right) newLegsAnimation = PlayerAnimation::Legs::IdleRight;
        }

        if (PlayerAnimation::getIndex(newBodyAnimation) != bodyAnimationState.id) {
            bodyAnimationState.id         = PlayerAnimation::getIndex(newBodyAnimation);
            bodyAnimationState.startFrame = WorldTime::getTime();
        }

        if (PlayerAnimation::getIndex(newLegsAnimation) != legsAnimationState.id) {
            legsAnimationState.id         = PlayerAnimation::getIndex(newLegsAnimation);
            legsAnimationState.startFrame = WorldTime::getTime();
        }

        if (PlayerAnimation::getIndex(newHeadAnimation) != headAnimationState.id) {
            headAnimationState.id         = PlayerAnimation::getIndex(newHeadAnimation);
            headAnimationState.startFrame = WorldTime::getTime();
        }

        if (PlayerAnimation::getIndex(newTailAnimation) != tailAnimationState.id) {
            tailAnimationState.id         = PlayerAnimation::getIndex(newTailAnimation);
            tailAnimationState.startFrame = WorldTime::getTime();
        }

        frameState.clear();
        animation->getFrameGenerator()->generateFrames(WorldTime::getTime(), bodyAnimationState, frameState);
        animation->getFrameGenerator()->generateFrames(WorldTime::getTime(), legsAnimationState, frameState);
        animation->getFrameGenerator()->generateFrames(WorldTime::getTime(), headAnimationState, frameState);
        animation->getFrameGenerator()->generateFrames(WorldTime::getTime(), tailAnimationState, frameState);
    }
};


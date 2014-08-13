/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    animationlibrary.cpp
 * Created: 2014-06-13
 * Authors: Jani Salo
 */

#include <vector>

#include "util/datafile.hpp"
#include "gameanimation.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    GameAnimation::GameAnimation(const string& dataPathPrefix) {
        loadPlayerAnimations(dataPathPrefix);
        playerAnimation = unique_ptr< PlayerAnimation >(new PlayerAnimation(playerAnimationLibrary.get()));
    }

    const ObjectFrameLibrary* GameAnimation::getPlayerAnimationLibrary() const { return playerAnimationLibrary.get(); }
    const PlayerAnimation*    GameAnimation::getPlayerAnimation()        const { return playerAnimation.get(); }

    GLFloatMat3 GameAnimation::getMirrorXMatrix() const {
        return GLFloatMat3(
            -1.0f, 0.0f, 0.0f,
             0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 1.0f
        );
    }

    void GameAnimation::loadPlayerAnimations(const string& dataPathPrefix) {
        playerAnimationLibrary = unique_ptr< ObjectFrameLibrary >(new ObjectFrameLibrary);

        DataFile data(dataPathPrefix + string("/actor/saluki.run"));

        vector< string > frameListNames = {{
            string("body_idle_right"),
            string("legs_idle_right"),
            string("legs_walk_right"),
            string("head_idle_right"),
            string("tail_idle_right")
        }};

        playerAnimationLibrary->loadFrameLists(frameListNames, data);

        playerAnimationLibrary->createCopy(string("body_idle_right"), string("body_idle_left"), getMirrorXMatrix());
        playerAnimationLibrary->createCopy(string("legs_idle_right"), string("legs_idle_left"), getMirrorXMatrix());
        playerAnimationLibrary->createCopy(string("legs_walk_right"), string("legs_walk_left"), getMirrorXMatrix());
        playerAnimationLibrary->createCopy(string("head_idle_right"), string("head_idle_left"), getMirrorXMatrix());
        playerAnimationLibrary->createCopy(string("tail_idle_right"), string("tail_idle_left"), getMirrorXMatrix());
    }
};


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    gameanimation.hpp
 * Created: 2014-06-13
 * Authors: Jani Salo
 */

/*
 * Loader and container for all game animation.
 */

#ifndef RUNRUN_GAMEANIMATION_HPP
#define RUNRUN_GAMEANIMATION_HPP

#include <memory>
#include <string>

#include "ruukku/opengl/gltypes.hpp"
#include "frame/objectframelibrary.hpp"
#include "player/playeranimation.hpp"

namespace runrun {
    class GameAnimation {
        public:
            GameAnimation(const std::string& dataPathPrefix);

            const ObjectFrameLibrary* getPlayerAnimationLibrary() const;
            const PlayerAnimation*    getPlayerAnimation()        const;

        private:
            std::unique_ptr< ObjectFrameLibrary > playerAnimationLibrary;
            std::unique_ptr< PlayerAnimation >    playerAnimation;

            ruukku::GLFloatMat3 getMirrorXMatrix() const;

            void loadPlayerAnimations(const std::string& dataPathPrefix);
    };
};

#endif /* RUNRUN_GAMEANIMATION_HPP */


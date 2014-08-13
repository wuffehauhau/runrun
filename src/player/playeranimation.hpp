/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    playeranimation.hpp
 * Created: 2014-06-13
 * Authors: Jani Salo
 */

/*
 * Player animations.
 */

#ifndef RUNRUN_PLAYERANIMATION_HPP
#define RUNRUN_PLAYERANIMATION_HPP

#include <memory>

#include "frame/objectframelibrary.hpp"
#include "frame/objectframegenerator.hpp"

namespace runrun {
    class PlayerAnimation {
        public:
            enum class Body : unsigned int {
                Empty        = 0,
                DefaultLeft  = 1,
                DefaultRight = 2
            };

            enum class Legs : unsigned int {
                Empty        = 0 + 128,
                IdleLeft     = 1 + 128,
                IdleRight    = 2 + 128,
                WalkLeft     = 3 + 128,
                WalkRight    = 4 + 128
            };

            enum class Head : unsigned int {
                Empty        = 0 + 256,
                DefaultLeft  = 1 + 256,
                DefaultRight = 2 + 256
            };

            enum class Tail : unsigned int {
                Empty        = 0 + 384,
                DefaultLeft  = 1 + 384,
                DefaultRight = 2 + 384
            };

            static unsigned int getIndex(const Body body);
            static unsigned int getIndex(const Legs legs);
            static unsigned int getIndex(const Head head);
            static unsigned int getIndex(const Tail tail);

            PlayerAnimation(const ObjectFrameLibrary* library);
            const ObjectFrameGenerator* getFrameGenerator() const;

        private:
            std::unique_ptr< ObjectFrameGenerator > frameGenerator;
    };

    inline unsigned int PlayerAnimation::getIndex(const Body body) { return static_cast< unsigned int >(body); }
    inline unsigned int PlayerAnimation::getIndex(const Legs legs) { return static_cast< unsigned int >(legs); }
    inline unsigned int PlayerAnimation::getIndex(const Head head) { return static_cast< unsigned int >(head); }
    inline unsigned int PlayerAnimation::getIndex(const Tail tail) { return static_cast< unsigned int >(tail); }

    inline const ObjectFrameGenerator* PlayerAnimation::getFrameGenerator() const { return frameGenerator.get(); }
};

#endif /* RUNRUN_PLAYERANIMATION_HPP */


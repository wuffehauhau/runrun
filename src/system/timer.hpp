/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    timer.hpp
 * Created: 2014-05-30
 * Authors: Jani Salo
 */

/*
 * Simple high precision timer.
 */

#include <cstdint>
#include "SDL2/SDL.h"

#ifndef RUNRUN_TIMER_HPP
#define RUNRUN_TIMER_HPP

namespace runrun {
    class Timer {
        public:
            Timer();
            void reset();

            double getSecondsElapsed() const;

        private:
            double scalar;
            std::uint64_t startTicks;
    };

    inline Timer::Timer() {
        scalar = 1.0 / static_cast< double >(SDL_GetPerformanceFrequency());
        reset();
    }

    inline void Timer::reset() {
        startTicks = SDL_GetPerformanceCounter();
    }

    inline double Timer::getSecondsElapsed() const {
        return scalar * static_cast< double >(SDL_GetPerformanceCounter() - startTicks);
    }
};

#endif /* RUNRUN_TIMER_HPP */


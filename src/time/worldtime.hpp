/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    globaltime.hpp
 * Created: 2014-06-14
 * Authors: Jani Salo
 */

/*
 * Global game engine time in frames.
 */

#ifndef RUNRUN_WORLDTIME_HPP
#define RUNRUN_WORLDTIME_HPP

namespace runrun {
    class WorldTime {
        public:
            static void reset();
            static void tick();

            static unsigned int getTime();
            static unsigned int getTimeSince(const unsigned int event);

        private:
            static unsigned int time;
    };

    inline void WorldTime::reset() { time = 0; }
    inline void WorldTime::tick()  { time++; }

    inline unsigned int WorldTime::getTime()                              { return time; }
    inline unsigned int WorldTime::getTimeSince(const unsigned int event) { return time - event; }
};

#endif /* RUNRUN_GLOBALTIME_HPP */


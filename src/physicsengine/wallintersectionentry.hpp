/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    wallintersectionentry.hpp
 * Created: 2014-07-28
 * Authors: Jani Salo
 */

/*
 * Stores information for a single wall intersection event.
 */

#ifndef RUNRUN_WALLINTERSECTIONENTRY_HPP
#define RUNRUN_WALLINTERSECTIONENTRY_HPP

#include "geometry/convexpolygon.hpp"

namespace runrun {
    class WallIntersectionEntry {
        public:
            ConvexPolygon wall;

            WallIntersectionEntry() {}
            WallIntersectionEntry(const ConvexPolygon& wall) : wall(wall) {}
    };
};

#endif /* RUNRUN_WALLINTERSECTIONENTRY_HPP */


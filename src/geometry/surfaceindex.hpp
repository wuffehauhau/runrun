/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    surfaceindex.hpp
 * Created: 2014-07-28
 * Authors: Jani Salo
 */

/*
 * Used to identify a pair of vertex indices making up a surface.
 */

#ifndef RUNRUN_SURFACEINDEX_HPP
#define RUNRUN_SURFACEINDEX_HPP

#include <cstddef>

namespace runrun {
    class SurfaceIndex {
        public:
            std::size_t a, b;

            SurfaceIndex() {}
            SurfaceIndex(const std::size_t a, const std::size_t b) : a(a), b(b) {}
    };
};

#endif /* RUNRUN_SURFACEINDEX_HPP */


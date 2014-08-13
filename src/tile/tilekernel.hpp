/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilekernel.hpp
 * Created: 2014-06-25
 * Authors: Jani Salo
 */

/*
 * A plus shaped kernel of tiles.
 */

#ifndef RUNRUN_TILEKERNEL_HPP
#define RUNRUN_TILEKERNEL_HPP

#include "ruukku/math/ivec2.hpp"
#include "kernel/pluskernel.hpp"

#include "tile.hpp"

namespace runrun {
    class TileKernel : public PlusKernel< Tile > {
        public:
            ruukku::Int2 position;

            TileKernel() {}
            TileKernel(
                const Tile& c,
                const Tile& l,
                const Tile& r,
                const Tile& d,
                const Tile& u,
                const ruukku::Int2& position
            ) : PlusKernel(c, l, r, d, u), position(position) {}
    };
};

#endif /* RUNRUN_TILEKERNEL_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilefactory.hpp
 * Created: 2014-06-18
 * Authors: Jani Salo
 */

/*
 * A factory for tiles.
 */

#ifndef RUNRUN_TILEFACTORY_HPP
#define RUNRUN_TILEFACTORY_HPP

#include <vector>

#include "ruukku/misc/uncopyable.hpp"
#include "tilerecord.hpp"
#include "tile.hpp"

namespace runrun {
    // Kept uncopyably to minimize traps created by copying this thing.
    class TileFactory : public ruukku::Uncopyable {
        public:
            Tile createTile(const TileRecord& record);

        private:
            std::vector< TileRecord > recordList;
    };

    inline Tile TileFactory::createTile(const TileRecord& record) {
        return Tile(record, &recordList);
    }
};

#endif /* RUNRUN_TILEFACTORY_HPP */


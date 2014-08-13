/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    map.hpp
 * Created: 2014-06-17
 * Authors: Jani Salo
 */

/*
 * Container for map data.
 */

#ifndef RUNRUN_MAP_HPP
#define RUNRUN_MAP_HPP

#include <functional>
#include <vector>

#include "ruukku/math/ivec2.hpp"
#include "ruukku/math/field2.hpp"

#include "metrics/mapmetrics.hpp"
#include "tile/tile.hpp"
#include "tile/tilefactory.hpp"
#include "tile/tilekernel.hpp"

namespace runrun {
    class Map {
        public:
            Map(const ruukku::Int2& sizeInCells);

            ruukku::Int2 getSizeInCells() const;
            ruukku::Int2 getSizeInTiles() const;

            TileFactory& getTileFactory();

            const Tile& tileAt(const ruukku::Int2& tilePosition) const;
                  Tile& tileAt(const ruukku::Int2& tilePosition);

            void loopTiles(std::function< void (const Tile& tile, const ruukku::Int2& position) > func) const;
            void loopTiles(std::function< void       (Tile& tile, const ruukku::Int2& position) > func);

        private:
            TileFactory tileFactory;
            ruukku::Field2< Tile > tileField;

            void validateSize() const;
    };

    inline const Tile& Map::tileAt(const ruukku::Int2& tilePosition) const { return tileField[tilePosition]; }
    inline       Tile& Map::tileAt(const ruukku::Int2& tilePosition)       { return tileField[tilePosition]; }

    inline TileFactory& Map::getTileFactory() { return tileFactory; }

    inline void Map::loopTiles(std::function< void (const Tile& tile, const ruukku::Int2& position) > func) const {
        for (int y = 0; y < tileField.getSize().y; y++) {
            for (int x = 0; x < tileField.getSize().x; x++) {
                const ruukku::Int2 position(x, y);
                func(tileAt(position), position);
            }
        }
    }

    inline void Map::loopTiles(std::function< void (Tile& tile, const ruukku::Int2& position) > func) {
        for (int y = 0; y < tileField.getSize().y; y++) {
            for (int x = 0; x < tileField.getSize().x; x++) {
                const ruukku::Int2 position(x, y);
                func(tileAt(position), position);
            }
        }
    }
};

#endif /* RUNRUN_MAP_HPP */


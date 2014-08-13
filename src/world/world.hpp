/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    world.hpp
 * Created: 2014-06-10
 * Authors: Jani Salo
 */

/*
 * Container for the game world.
 */

#ifndef RUNRUN_WORLD_HPP
#define RUNRUN_WORLD_HPP

#include <cassert>
#include <functional>
#include <memory>

#include "ruukku/math/ivec2.hpp"

#include "algorithm/staticarray2.hpp"
#include "biome/biome.hpp"
#include "camera/view.hpp"
#include "geometry/boundingbox.hpp"
#include "map/map.hpp"
#include "map/mapphysics.hpp"
#include "object/object.hpp"
#include "player/player.hpp"
#include "tile/tilefactory.hpp"
#include "tile/tilekernel.hpp"

#include "cell.hpp"

namespace runrun {
    class World {
        public:
            World();

            void loadMap(const Map& map);
            void setBiome(const Biome& biome);

            ruukku::Int2 getSizeInCells() const;
            ruukku::Int2 getSizeInTiles() const;

            BoundingBox getBoundingBox() const;

            const MapPhysics& getPhysics() const;
            void setPhysics(const MapPhysics& physics);

            void insertPlayer(Player* player);
            void removePlayer(Player* player);

            void findAllCells(std::function< void (const Cell& cell) > func) const;
            void findAllCells(std::function< void (Cell& cell) > func);

            void findVisibleCells(const View& view, std::function< void (const Cell& cell) > func) const;
            void findVisibleCells(const View& view, std::function< void (Cell& cell) > func);

            void findAllObjects(std::function< void (const Object& object) > func) const;
            void findAllObjects(std::function< void (Object& object) > func);

            void findVisibleObjects(const View& view, std::function< void (const Object& object) > func) const;
            void findVisibleObjects(const View& view, std::function< void (Object& object) > func);

            void findTiles(const BoundingBox& box, std::function< void (const ruukku::Int2& position, const Tile& tile) > func) const;
            void findTiles(const BoundingBox& box, std::function< void (const ruukku::Int2& position, Tile& tile) > func);

        private:
            typedef StaticArray2< Cell, MapMetrics::MAP_DIM_IN_CELLS, MapMetrics::MAP_DIM_IN_CELLS > CellArray;

            std::unique_ptr< CellArray > cellArray;
            ruukku::Int2 cellArraySize;

            TileFactory tileFactory;
            std::unique_ptr< Biome > biome;

            std::vector< Player* > playerList;

            MapPhysics physics;

            bool isTilePositionOK(const ruukku::Int2& position) const;
            bool isCellPositionOK(const ruukku::Int2& position) const;

            const Cell& cellAt(const ruukku::Int2& position) const;
                  Cell& cellAt(const ruukku::Int2& position);

            const Tile& tileAt(const ruukku::Int2& position) const;
                  Tile& tileAt(const ruukku::Int2& position);

            const TileStaticRenderInfo& tileStaticRenderInfo(const ruukku::Int2& position, TileStaticRenderData::Layer layer) const;
                  TileStaticRenderInfo& tileStaticRenderInfo(const ruukku::Int2& position, TileStaticRenderData::Layer layer);

            const TileDynamicRenderInfo& tileDynamicRenderInfo(const ruukku::Int2& position) const;
                  TileDynamicRenderInfo& tileDynamicRenderInfo(const ruukku::Int2& position);

            TileKernel getTileKernel(const ruukku::Int2 position) const;

            void loopActiveCells(std::function< void (const Cell& cell, const ruukku::Int2& position) > func) const;
            void loopActiveCells(std::function< void       (Cell& cell, const ruukku::Int2& position) > func);
    };

    inline ruukku::Int2 World::getSizeInCells() const { return cellArraySize; }

    inline ruukku::Int2 World::getSizeInTiles() const {
        return ruukku::Int2(
            cellArraySize.x * MapMetrics::CELL_DIM,
            cellArraySize.y * MapMetrics::CELL_DIM
        );
    }

    inline void World::findAllCells(std::function< void (const Cell& cell) > func) const {
        loopActiveCells([&](const Cell& cell, const ruukku::Int2& position) { func(cell); });
    }

    inline void World::findAllCells(std::function< void (Cell& cell) > func) {
        loopActiveCells([&](Cell& cell, const ruukku::Int2& position) { func(cell); });
    }

    inline void World::findVisibleCells(const View& view, std::function< void (const Cell& cell) > func) const {
        // TODO Implement recursive space subdivision to resolve visible cells faster.
        loopActiveCells([&](const Cell& cell, const ruukku::Int2& position) {
            if (view.isAASquareVisible(AASquare(cell.getPosition(), cell.getEdgeLength()))) {
                func(cell);
            }
        });
    }

    inline void World::findVisibleCells(const View& view, std::function< void (Cell& cell) > func) {
        // TODO Implement recursive space subdivision to resolve visible cells faster.
        loopActiveCells([&](Cell& cell, const ruukku::Int2& position) {
            if (view.isAASquareVisible(AASquare(cell.getPosition(), cell.getEdgeLength()))) {
                func(cell);
            }
        });
    }

    inline void World::findAllObjects(std::function< void (const Object& object) > func) const {
        for (const Player* player : playerList) func(*player);
    }

    inline void World::findAllObjects(std::function< void (Object& object) > func) {
        for (Player* player : playerList) func(*player);
    }

    inline void World::findVisibleObjects(const View& view, std::function< void (const Object& object) > func) const {
        // TODO Implement some sort of logic instead of just finding all objects.
        for (const Player* player : playerList) func(*player);
    }

    inline void World::findVisibleObjects(const View& view, std::function< void (Object& object) > func) {
        // TODO Implement some sort of logic instead of just finding all objects.
        for (Player* player : playerList) func(*player);
    }

    inline void World::findTiles(const BoundingBox& box, std::function< void (const ruukku::Int2& position, const Tile& tile) > func) const {
        MapMetrics::findIntersectingTilePositions(box, getSizeInTiles(), [&](const ruukku::Int2& position) {
            func(position, tileAt(position));
        });
    }

    inline void World::findTiles(const BoundingBox& box, std::function< void (const ruukku::Int2& position, Tile& tile) > func) {
        MapMetrics::findIntersectingTilePositions(box, getSizeInTiles(), [&](const ruukku::Int2& position) {
            func(position, tileAt(position));
        });
    }

    inline bool World::isTilePositionOK(const ruukku::Int2& position) const {
        return position.x >= 0 && position.y >= 0 && position.x < getSizeInTiles().x && position.y < getSizeInTiles().y;
    }

    inline bool World::isCellPositionOK(const ruukku::Int2& position) const {
        return position.x >= 0 && position.y >= 0 && position.x < getSizeInCells().x && position.y < getSizeInCells().y;
    }

    inline const Cell& World::cellAt(const ruukku::Int2& position) const {
        assert(isCellPositionOK(position));
        return (*cellArray)[position];
    }

    inline Cell& World::cellAt(const ruukku::Int2& position) {
        assert(isCellPositionOK(position));
        return (*cellArray)[position];
    }

    inline const Tile& World::tileAt(const ruukku::Int2& position) const {
        return cellAt(MapMetrics::getCellPositionFromTilePosition(position)).tile(MapMetrics::getTilePositionInsideCell(position));
    }

    inline Tile& World::tileAt(const ruukku::Int2& position) {
        return cellAt(MapMetrics::getCellPositionFromTilePosition(position)).tile(MapMetrics::getTilePositionInsideCell(position));
    }

    inline void World::loopActiveCells(std::function< void (const Cell& cell, const ruukku::Int2& position) > func) const {
        for (int y = 0; y < cellArraySize.y; y++) {
            for (int x = 0; x < cellArraySize.x; x++) {
                const ruukku::Int2 position(x, y);
                func((*cellArray)[position], position);
            }
        }
    }

    inline void World::loopActiveCells(std::function< void (Cell& cell, const ruukku::Int2& position) > func) {
        for (int y = 0; y < cellArraySize.y; y++) {
            for (int x = 0; x < cellArraySize.x; x++) {
                const ruukku::Int2 position(x, y);
                func((*cellArray)[position], position);
            }
        }
    }
};

#endif /* RUNRUN_WORLD_HPP */


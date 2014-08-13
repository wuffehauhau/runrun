/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    world.cpp
 * Created: 2014-06-10
 * Authors: Jani Salo
 */

#include <algorithm>

#include "algorithm/vectorutil.hpp"
#include "biome/defaultbiome.hpp"
#include "metrics/mapmetrics.hpp"

#include "world.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    World::World() :
        cellArray(unique_ptr< CellArray >(new CellArray)),
        cellArraySize(Int2(0, 0))
    {
        cellArray->loopElements([](Cell& cell, const Int2& position) { cell.setGridPosition(position); });
        biome = unique_ptr< Biome >(new DefaultBiome());
        physics = MapPhysics(1.0f, 0.0f);
    }

    void World::loadMap(const Map& map)
    {
        assert(map.getSizeInCells().x <= MapMetrics::MAP_DIM_IN_CELLS);
        assert(map.getSizeInCells().y <= MapMetrics::MAP_DIM_IN_CELLS);
        cellArraySize = map.getSizeInCells();

        // TODO Implement method for looping all tiles.
        loopActiveCells([&](Cell& cell, const Int2& cellPosition) {
            const Int2 origo = MapMetrics::getTilePositionFromCellPosition(cellPosition);

            Cell::loopPositions([&](const Int2& tilePositionInsideCell) {
                const Int2 position = MapMetrics::getTilePosition(cellPosition, tilePositionInsideCell);
                cell.tile(tilePositionInsideCell) = tileFactory.createTile(map.tileAt(position).getRecord());
            });
        });

        // TODO Make into separate method.
        loopActiveCells([&](Cell& cell, const Int2& cellPosition) {
            const Int2 origo = MapMetrics::getTilePositionFromCellPosition(cellPosition);
            Cell::loopPositions([&](const Int2& tilePositionInsideCell) {
                const Int2 position = MapMetrics::getTilePosition(cellPosition, tilePositionInsideCell);
                TileKernel tileKernel = getTileKernel(position);

                cell.tileStaticRenderInfo(tilePositionInsideCell, TileStaticRenderData::Layer::Front) = biome->getTileVisualizer()->getRenderInfo(getTileKernel(position), TileStaticRenderData::Layer::Front);
                cell.tileStaticRenderInfo(tilePositionInsideCell, TileStaticRenderData::Layer::Back)  = biome->getTileVisualizer()->getRenderInfo(getTileKernel(position), TileStaticRenderData::Layer::Back);

                // TODO Implement actual lighting.
                cell.tileDynamicRenderInfo(tilePositionInsideCell) = GLFloatRGBA(1.0f, 1.0f, 1.0f, 1.0f);

                cell.flags.set(CellFlags::UpdateStaticTileDataFront);
                cell.flags.set(CellFlags::UpdateStaticTileDataBack);
            });
        });
    }

    BoundingBox World::getBoundingBox() const {
        const Int2 tileSize = getSizeInTiles();

        return BoundingBox(
            GLFloatVec2(0.0f, 0.0f),
            GLFloatVec2(static_cast< GLfloat >(tileSize.x), static_cast< GLfloat >(tileSize.y))
        );
    }

    void World::setBiome(const Biome& biome) {
        this->biome = unique_ptr< Biome >(biome.createCopy());
    }

    const MapPhysics& World::getPhysics() const { return physics; }
    void World::setPhysics(const MapPhysics& physics) { this->physics = physics; }

    void World::insertPlayer(Player* player) {
        vector< Player* >::const_iterator it = find(playerList.cbegin(), playerList.cend(), player);
        if (it == playerList.cend()) playerList.push_back(player);
        else throw logic_error("Player already inserted into world.");
    }

    void World::removePlayer(Player* player) {
        vector< Player* >::iterator it = find(playerList.begin(), playerList.end(), player);
        if (it == playerList.end()) throw logic_error("No player to remove from world.");
        else VectorUtil::replaceErase(playerList, it);
    }

    const TileStaticRenderInfo& World::tileStaticRenderInfo(const Int2& position, TileStaticRenderData::Layer layer) const {
        return cellAt(MapMetrics::getCellPositionFromTilePosition(position)).tileStaticRenderInfo(MapMetrics::getTilePositionInsideCell(position), layer);
    }

    TileStaticRenderInfo& World::tileStaticRenderInfo(const Int2& position, TileStaticRenderData::Layer layer) {
        return cellAt(MapMetrics::getCellPositionFromTilePosition(position)).tileStaticRenderInfo(MapMetrics::getTilePositionInsideCell(position), layer);
    }

    const TileDynamicRenderInfo& World::tileDynamicRenderInfo(const Int2& position) const {
        return cellAt(MapMetrics::getCellPositionFromTilePosition(position)).tileDynamicRenderInfo(MapMetrics::getTilePositionInsideCell(position));
    }

    TileDynamicRenderInfo& World::tileDynamicRenderInfo(const Int2& position) {
        return cellAt(MapMetrics::getCellPositionFromTilePosition(position)).tileDynamicRenderInfo(MapMetrics::getTilePositionInsideCell(position));
    }

    TileKernel World::getTileKernel(const Int2 position) const {
        const Int2 positionL = position + Int2(-1,  0);
        const Int2 positionR = position + Int2( 1,  0);
        const Int2 positionD = position + Int2( 0, -1);
        const Int2 positionU = position + Int2( 0,  1);

        Tile center = isTilePositionOK(position) ? tileAt(position) : Tile();

        return TileKernel(
            center,
            isTilePositionOK(positionL) ? tileAt(positionL) : center,
            isTilePositionOK(positionR) ? tileAt(positionR) : center,
            isTilePositionOK(positionD) ? tileAt(positionD) : center,
            isTilePositionOK(positionU) ? tileAt(positionU) : center,
            position
        );
    }
};


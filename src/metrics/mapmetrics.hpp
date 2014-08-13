/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mapmetrics.hpp
 * Created: 2014-06-17
 * Authors: Jani Salo
 */

/*
 * Map metrics.
 */

#ifndef RUNRUN_MAPMETRICS_HPP
#define RUNRUN_MAPMETRICS_HPP

#include <algorithm>
#include <functional>

#include "ruukku/math/ivec2.hpp"
#include "geometry/boundingbox.hpp"

namespace runrun {
    class MapMetrics {
        public:
            static const unsigned int CELL_DIM  = 16;
            static const unsigned int CELL_AREA = CELL_DIM * CELL_DIM;

            static const unsigned int MAP_DIM_IN_CELLS = 64;
            static const unsigned int MAP_DIM_IN_TILES = CELL_DIM * MAP_DIM_IN_CELLS;

            static ruukku::Int2 getCellPositionFromTilePosition (const ruukku::Int2& tilePosition);
            static ruukku::Int2 getTilePositionFromCellPosition (const ruukku::Int2& cellPosition);
            static ruukku::Int2 getTilePositionInsideCell       (const ruukku::Int2& tilePosition);

            static ruukku::Int2 getTilePosition(
                const ruukku::Int2& cellPosition,
                const ruukku::Int2& tilePositionInsideCell
            );

            static ruukku::Int2 clampMapPosition(const ruukku::Int2& position, const ruukku::Int2& sizeInUnits);

            static void findIntersectingCellPositions(const BoundingBox& box, const ruukku::Int2& sizeInCells, std::function< void (const ruukku::Int2& position) > func);
            static void findIntersectingTilePositions(const BoundingBox& box, const ruukku::Int2& sizeInTiles, std::function< void (const ruukku::Int2& position) > func);
    };

    inline ruukku::Int2 MapMetrics::getCellPositionFromTilePosition(const ruukku::Int2& tilePosition) {
        return ruukku::Int2(
            tilePosition.x / CELL_DIM,
            tilePosition.y / CELL_DIM
        );
    }

    inline ruukku::Int2 MapMetrics::getTilePositionFromCellPosition(const ruukku::Int2& cellPosition) {
        return ruukku::Int2(
            cellPosition.x * MapMetrics::CELL_DIM,
            cellPosition.y * MapMetrics::CELL_DIM
        );
    }

    inline ruukku::Int2 MapMetrics::getTilePositionInsideCell(const ruukku::Int2& tilePosition) {
        return ruukku::Int2(
            tilePosition.x % CELL_DIM,
            tilePosition.y % CELL_DIM
        );
    }

    inline ruukku::Int2 MapMetrics::getTilePosition(
        const ruukku::Int2& cellPosition,
        const ruukku::Int2& tilePositionInsideCell
    ) {
        return ruukku::Int2(
            cellPosition.x * MapMetrics::CELL_DIM + tilePositionInsideCell.x,
            cellPosition.y * MapMetrics::CELL_DIM + tilePositionInsideCell.y
        );
    }

    inline ruukku::Int2 MapMetrics::clampMapPosition(const ruukku::Int2& position, const ruukku::Int2& sizeInUnits) {
        return ruukku::Int2(
            std::max(0, std::min(sizeInUnits.x - 1, position.x)),
            std::max(0, std::min(sizeInUnits.y - 1, position.y))
        );
    }

    inline void MapMetrics::findIntersectingCellPositions(const BoundingBox& box, const ruukku::Int2& sizeInCells, std::function< void (const ruukku::Int2& position) > func) {
        const ruukku::Int2 min = clampMapPosition(ruukku::Int2(static_cast< int >((1.0f / 16.0f) * box.min.x), static_cast< int >((1.0f / 16.0f) * box.min.y)), sizeInCells);
        const ruukku::Int2 max = clampMapPosition(ruukku::Int2(static_cast< int >((1.0f / 16.0f) * box.max.x), static_cast< int >((1.0f / 16.0f) * box.max.y)), sizeInCells);

        for (int y = min.y; y <= max.y; y++) {
            for (int x = min.x; x <= max.x; x++) {
                func(ruukku::Int2(x, y));
            }
        }
    }

    inline void MapMetrics::findIntersectingTilePositions(const BoundingBox& box, const ruukku::Int2& sizeInTiles, std::function< void (const ruukku::Int2& position) > func) {
        const ruukku::Int2 min = clampMapPosition(ruukku::Int2(static_cast< int >(box.min.x), static_cast< int >(box.min.y)), sizeInTiles);
        const ruukku::Int2 max = clampMapPosition(ruukku::Int2(static_cast< int >(box.max.x), static_cast< int >(box.max.y)), sizeInTiles);

        for (int y = min.y; y <= max.y; y++) {
            for (int x = min.x; x <= max.x; x++) {
                func(ruukku::Int2(x, y));
            }
        }
    }
};

#endif /* RUNRUN_MAPMETRICS_HPP */


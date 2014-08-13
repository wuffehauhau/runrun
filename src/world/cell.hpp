/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    cell.hpp
 * Created: 2014-06-10
 * Authors: Jani Salo
 */

/*
 * Game world cell.
 */

#ifndef RUNRUN_CELL_HPP
#define RUNRUN_CELL_HPP

#include "algorithm/flags.hpp"
#include "algorithm/staticarray2.hpp"
#include "glyph/tilestaticrenderdata.hpp"
#include "glyph/tiledynamicrenderdata.hpp"
#include "tile/tile.hpp"

#include "cellflags.hpp"

namespace runrun {
    class Cell {
        public:
            typedef StaticArray2< Tile, MapMetrics::CELL_DIM, MapMetrics::CELL_DIM > TileArray;

            static constexpr GLfloat getEdgeLength();

            TileArray tileArray;

            TileStaticRenderData  staticRenderData;
            TileDynamicRenderData dynamicRenderData;

            Flags< CellFlags > flags;

            Cell();

            const ruukku::Int2        getGridPosition() const;
            const ruukku::GLFloatVec2 getPosition()     const;

            void setGridPosition(const ruukku::Int2& gridPosition);

            const Tile& tile(const ruukku::Int2& position) const;
                  Tile& tile(const ruukku::Int2& position);

            const TileStaticRenderInfo& tileStaticRenderInfo(const ruukku::Int2& position, TileStaticRenderData::Layer layer) const;
                  TileStaticRenderInfo& tileStaticRenderInfo(const ruukku::Int2& position, TileStaticRenderData::Layer layer);

            const TileDynamicRenderInfo& tileDynamicRenderInfo(const ruukku::Int2& position) const;
                  TileDynamicRenderInfo& tileDynamicRenderInfo(const ruukku::Int2& position);

            static void loopPositions(std::function<void (const ruukku::Int2& pos)> func);

        private:
            ruukku::Int2    gridPosition;
            ruukku::GLFloatVec2 position;

            std::uint32_t statusFlags;
    };

    inline constexpr GLfloat Cell::getEdgeLength() { return static_cast< GLfloat >(MapMetrics::CELL_DIM); }

    inline Cell::Cell() : gridPosition(ruukku::Int2(0, 0)), position(ruukku::GLFloatVec2(0.0f, 0.0f)) {}

    inline const ruukku::Int2        Cell::getGridPosition() const { return gridPosition; }
    inline const ruukku::GLFloatVec2 Cell::getPosition()     const { return position; }

    inline void Cell::setGridPosition(const ruukku::Int2& gridPosition) {
        this->gridPosition = gridPosition;
        position = ruukku::GLFloatVec2(
            static_cast< GLfloat >(gridPosition.x * MapMetrics::CELL_DIM),
            static_cast< GLfloat >(gridPosition.y * MapMetrics::CELL_DIM)
        );
    }

    inline const Tile& Cell::tile(const ruukku::Int2& position) const { return tileArray[position]; }
    inline       Tile& Cell::tile(const ruukku::Int2& position)       { return tileArray[position]; }

    inline const TileStaticRenderInfo& Cell::tileStaticRenderInfo(const ruukku::Int2& position, TileStaticRenderData::Layer layer) const {
        return (staticRenderData.array(layer))[position];
    }

    inline TileStaticRenderInfo& Cell::tileStaticRenderInfo(const ruukku::Int2& position, TileStaticRenderData::Layer layer) {
        return (staticRenderData.array(layer))[position];
    }

    inline const TileDynamicRenderInfo& Cell::tileDynamicRenderInfo(const ruukku::Int2& position) const {
        return (dynamicRenderData.array())[position];
    }

    inline TileDynamicRenderInfo& Cell::tileDynamicRenderInfo(const ruukku::Int2& position) {
        return (dynamicRenderData.array())[position];
    }

    inline void Cell::loopPositions(std::function<void (const ruukku::Int2& pos)> func) {
        for (int y = 0; y < MapMetrics::CELL_DIM; y++) {
            for (int x = 0; x < MapMetrics::CELL_DIM; x++) {
                func(ruukku::Int2(x, y));
            }
        }
    }
};

#endif /* RUNRUN_CELL_HPP */


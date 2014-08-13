/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilestaticrenderdata.hpp
 * Created: 2014-06-08
 * Authors: Jani Salo
 */

/*
 * Stores static rendering data for a cell of tiles.
 */

#ifndef RUNRUN_TILESTATICRENDERDATA_HPP
#define RUNRUN_TILESTATICRENDERDATA_HPP

#include <array>

#include "algorithm/staticarray2.hpp"
#include "metrics/mapmetrics.hpp"
#include "tilestaticrenderinfo.hpp"

namespace runrun {
    class TileStaticRenderData {
        public:
            static const unsigned int LAYER_COUNT = 2;

            typedef StaticArray2< TileStaticRenderInfo, MapMetrics::CELL_DIM, MapMetrics::CELL_DIM > Array;

            enum class Layer : unsigned int {
                Front = 0,
                Back  = 1
            };

            const Array& array(const Layer layer) const;
                  Array& array(const Layer layer);

        private:
            std::array< Array, LAYER_COUNT > staticDataList;
    };

    inline const TileStaticRenderData::Array& TileStaticRenderData::array(const Layer layer) const {
        return staticDataList[static_cast< unsigned int >(layer)];
    }

    inline TileStaticRenderData::Array& TileStaticRenderData::array(const Layer layer) {
        return staticDataList[static_cast< unsigned int >(layer)];
    }
};

#endif /* RUNRUN_TILESTATICRENDERDATA_HPP */


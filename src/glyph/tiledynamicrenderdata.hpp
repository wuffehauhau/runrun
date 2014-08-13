/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tiledynamicrenderdata.hpp
 * Created: 2014-06-22
 * Authors: Jani Salo
 */

/*
 * Stores dynamic rendering data for a cell of tiles.
 */

#ifndef RUNRUN_TILEDYNAMICRENDERDATA_HPP
#define RUNRUN_TILEDYNAMICRENDERDATA_HPP

#include "algorithm/staticarray2.hpp"
#include "metrics/mapmetrics.hpp"
#include "tiledynamicrenderinfo.hpp"

namespace runrun {
    class TileDynamicRenderData {
        public:
            typedef StaticArray2< TileDynamicRenderInfo, MapMetrics::CELL_DIM, MapMetrics::CELL_DIM > Array;

            const Array& array() const;
                  Array& array();

        private:
            Array dynamicData;
    };

    inline const TileDynamicRenderData::Array& TileDynamicRenderData::array() const { return dynamicData; }
    inline       TileDynamicRenderData::Array& TileDynamicRenderData::array()       { return dynamicData; }
};

#endif /* RUNRUN_TILEDYNAMICRENDERDATA_HPP */


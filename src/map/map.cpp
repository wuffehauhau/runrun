/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    map.cpp
 * Created: 2014-06-17
 * Authors: Jani Salo
 */

#include <stdexcept>

#include "metrics/mapmetrics.hpp"
#include "map.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    Map::Map(const Int2& sizeInCells) : tileField(Int2(sizeInCells.x * MapMetrics::CELL_DIM, sizeInCells.y * MapMetrics::CELL_DIM)) {
        validateSize();
    }

    Int2 Map::getSizeInCells() const {
        return Int2(tileField.getSize().x / MapMetrics::CELL_DIM, tileField.getSize().y / MapMetrics::CELL_DIM);
    }

    Int2 Map::getSizeInTiles() const {
        return tileField.getSize();
    }

    void Map::validateSize() const {
        if (
            (tileField.getSize().x > MapMetrics::MAP_DIM_IN_TILES) ||
            (tileField.getSize().y > MapMetrics::MAP_DIM_IN_TILES) ||
            (tileField.getSize().x % MapMetrics::CELL_DIM != 0)    ||
            (tileField.getSize().y % MapMetrics::CELL_DIM != 0)
        ) {
            throw runtime_error(string("Invalid map size."));
        }
    }
};


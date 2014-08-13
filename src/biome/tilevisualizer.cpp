/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilevisualizer.cpp
 * Created: 2014-08-01
 * Authors: Jani Salo
 */

#include "tilevisualizer.hpp"

using namespace ruukku;

namespace runrun {
    TileVisualizer::TileVisualizer() {
        randomMap.resize(Int2(MapMetrics::MAP_DIM_IN_TILES, MapMetrics::MAP_DIM_IN_TILES));
        for (std::uint32_t& value : randomMap.getData()) value = rng.genUInt32();
    }

    RNG TileVisualizer::rng;
};


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tileintersectionentry.hpp
 * Created: 2014-07-23
 * Authors: Jani Salo
 */

/*
 * Stores information for a single tile intersection event.
 */

#ifndef RUNRUN_TILEINTERSECTIONENTRY_HPP
#define RUNRUN_TILEINTERSECTIONENTRY_HPP

#include "ruukku/opengl/gltypes.hpp"
#include "tile/tilerecord.hpp"

namespace runrun {
    class TileIntersectionEntry {
        public:
            TileRecord record;
            ruukku::GLFloatMat3 transformation;

            TileIntersectionEntry() {}
            TileIntersectionEntry(const TileRecord& record, const ruukku::GLFloatMat3& transformation) : record(record), transformation(transformation) {}
    };
};

#endif /* RUNRUN_TILEINTERSECTIONENTRY_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilephysics.hpp
 * Created: 2014-07-13
 * Authors: Jani Salo
 */

/*
 * A simple container for linking tile physics to collision hulls and materials.
 */

#ifndef RUNRUN_TILEPHYSICS_HPP
#define RUNRUN_TILEPHYSICS_HPP

#include <array>
#include <cassert>

#include "geometry/convexpolygon.hpp"
#include "tilerecord.hpp"

namespace runrun {
    class TilePhysics {
        public:
            TilePhysics();

            const ConvexPolygon& getCollisionPolygon(const TileRecord& record) const;

        private:
            ConvexPolygon collisionPolygonDefault;
            ConvexPolygon collisionPolygonBlock;

            std::array< ConvexPolygon, 4 > collisionPolygonSlopeList;
    };

    inline const ConvexPolygon& TilePhysics::getCollisionPolygon(const TileRecord& record) const {
        switch (record.attributes.generalType) {
            case TileAttributes::GeneralType::Block: return collisionPolygonBlock;
            case TileAttributes::GeneralType::Slope: {
                if (record.orientation != TileOrientation::Undefined) {
                    return collisionPolygonSlopeList[static_cast< unsigned int >(record.orientation)];
                }
            }
        }

        assert(false);
        return collisionPolygonDefault;
    }
};

#endif /* RUNRUN_TILEPHYSICS_HPP */


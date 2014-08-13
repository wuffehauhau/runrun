/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilerecord.hpp
 * Created: 2014-06-17
 * Authors: Jani Salo
 */

/*
 * A cached tile record.
 */

#ifndef RUNRUN_TILERECORD_HPP
#define RUNRUN_TILERECORD_HPP

#include "tileattributes.hpp"
#include "tileorientation.hpp"
#include "kernel/edgeflags.hpp"

namespace runrun {
    class TileRecord {
        public:
            TileAttributes attributes;
            TileOrientation orientation;

            TileRecord();
            TileRecord(const TileOrientation orientation, const TileAttributes& attributes);

            bool operator ==(const TileRecord& record) const;
            bool operator !=(const TileRecord& record) const;

            bool hasPhysics() const;

            EdgeFlags getCollidableEdges() const;
    };

    inline TileRecord::TileRecord() : orientation(TileOrientation::Undefined) {}
    inline TileRecord::TileRecord(const TileOrientation orientation, const TileAttributes& attributes) :
        orientation(orientation), attributes(attributes)
    {}

    inline bool TileRecord::operator ==(const TileRecord& record) const { return attributes == record.attributes && orientation == record.orientation; }
    inline bool TileRecord::operator !=(const TileRecord& record) const { return !((*this) == record); }

    inline bool TileRecord::hasPhysics() const { return attributes.generalType != TileAttributes::GeneralType::Space; }

    inline EdgeFlags TileRecord::getCollidableEdges() const {
        EdgeFlags edgeFlags;


        return edgeFlags;
    }
};

#endif /* RUNRUN_TILERECORD_HPP */


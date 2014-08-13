/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tileattributes.hpp
 * Created: 2014-07-08
 * Authors: Jani Salo
 */

/*
 * Stores attributes for a tile.
 */

#ifndef RUNRUN_TILEATTRIBUTES_HPP
#define RUNRUN_TILEATTRIBUTES_HPP

namespace runrun {
    class TileAttributes {
        public:
            enum class GeneralType {
                Space,
                Block,
                Slope
            };

            enum class PrimaryType {
                None,
                Soil,
                Rock,
                Plant
            };

            enum class SecondaryType {
                None,
                Foliage,
                Fungi
            };

            GeneralType   generalType;
            PrimaryType   primaryType;
            SecondaryType secondaryType;

            TileAttributes(
                const GeneralType   generalType   = GeneralType::Space,
                const PrimaryType   primaryType   = PrimaryType::None,
                const SecondaryType secondaryType = SecondaryType::None
            );

            bool operator ==(const TileAttributes& attributes) const;
            bool operator !=(const TileAttributes& attributes) const;
    };

    inline TileAttributes::TileAttributes(
        const TileAttributes::GeneralType generalType,
        const TileAttributes::PrimaryType primaryType,
        const TileAttributes::SecondaryType secondaryType
    ) :
        generalType(generalType),
        primaryType(primaryType),
        secondaryType(secondaryType)
    {}

    inline bool TileAttributes::operator ==(const TileAttributes& attributes) const {
        return (
            generalType   == attributes.generalType &&
            primaryType   == attributes.primaryType &&
            secondaryType == attributes.secondaryType
        );
    }

    inline bool TileAttributes::operator !=(const TileAttributes& attributes) const { return !((*this) == attributes); }
};

#endif /* RUNRUN_TILEATTRIBUTES_HPP*/


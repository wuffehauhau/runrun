/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tileinfo.hpp
 * Created: 2014-06-23
 * Authors: Jani Salo
 */

/*
 * Specifies a glyph for a tile and how it's drawn.
 */

#ifndef RUNRUN_TILEINFO_HPP
#define RUNRUN_TILEINFO_HPP

namespace runrun {
    class TileInfo {
        public:
            enum class Displacement : unsigned int {
                None     = 0,
                BaseLine = 1,
                Middle   = 2
            };

            enum class Orientation : unsigned int {
                Normal           = 0,
                CCW90            = 1,
                CCW180           = 2,
                CCW270           = 3,
                UpsideDown       = 4,
                UpsideDownCCW90  = 5,
                UpsideDownCCW180 = 6,
                UpsideDownCCW270 = 7
            };

            unsigned int glyphIndex;

            TileInfo(
                const unsigned int glyphIndex   = 0,
                const Displacement displacement = Displacement::None,
                const Orientation  orientation  = Orientation::Normal
            );

            void setDisplacement (const Displacement displacement);
            void setOrientation  (const Orientation  orientation);

            unsigned int getDisplacementIndex () const;
            unsigned int getOrientationIndex  () const;

        private:
            static const unsigned int DISPLACEMENT_MASK  = 0x3;
            static const unsigned int DISPLACEMENT_SHIFT = 0;
            static const unsigned int ORIENTATION_MASK   = 0x1C;
            static const unsigned int ORIENTATION_SHIFT  = 2;

            unsigned int flags;
    };

    inline TileInfo::TileInfo(
        const unsigned int glyphIndex,
        const Displacement displacement,
        const Orientation  orientation
    ) :
        glyphIndex(glyphIndex),
        flags(
            (static_cast< unsigned int >(displacement) << DISPLACEMENT_SHIFT) |
            (static_cast< unsigned int >(orientation)  << ORIENTATION_SHIFT)
        )
    {}

    inline unsigned int TileInfo::getDisplacementIndex () const { return (flags & DISPLACEMENT_MASK) >> DISPLACEMENT_SHIFT; }
    inline unsigned int TileInfo::getOrientationIndex  () const { return (flags & ORIENTATION_MASK)  >> ORIENTATION_SHIFT;  }

    inline void TileInfo::setDisplacement (const Displacement displacement) { flags = (flags & (~DISPLACEMENT_MASK)) | (static_cast< unsigned int >(displacement) << DISPLACEMENT_SHIFT); }
    inline void TileInfo::setOrientation  (const Orientation  orientation)  { flags = (flags & (~ORIENTATION_MASK))  | (static_cast< unsigned int >(orientation)  << ORIENTATION_SHIFT);  }
};

#endif /* RUNRUN_TILEINFO_HPP */


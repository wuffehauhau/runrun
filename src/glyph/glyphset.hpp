/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphset.hpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

/*
 * A storage unit for glyph sprite data.
 */

#ifndef RUNRUN_GLYPHSET_HPP
#define RUNRUN_GLYPHSET_HPP

#include <array>
#include <cassert>
#include <memory>

#include "ruukku/misc/uncopyable.hpp"
#include "ruukku/opengl/gltexture2d.hpp"
#include "ruukku/opengl/gltypes.hpp"
#include "ruukku/pixel/surface.hpp"

#include "tileinfo.hpp"

namespace runrun {
    class GlyphSet : public ruukku::Uncopyable {
        public:
            GlyphSet(const ruukku::Surface& surface);

            const ruukku::GLTexture2D* getGlyphSheet() const;
            const ruukku::GLTexture2D* getTileSheet()  const;

            // Returns lower left corner of given glyph in texture space.
            ruukku::GLFloatVec2 getGlyphOrigo (const unsigned int info) const;
            ruukku::GLFloatVec2 getTileOrigo  (const TileInfo& info) const;

            const ruukku::GLFloatVec2 getGlyphSpanOnTexture() const;

            // Again, use these compute offsets from tile origo in texture.
            const ruukku::GLFloatVec2& getTileUAxisSpan(const TileInfo& info) const;
            const ruukku::GLFloatVec2& getTileVAxisSpan(const TileInfo& info) const;

            static unsigned int getGlyphCount();

        private:
            static const unsigned int GLYPH_X_COUNT_PER_PAGE = 16;
            static const unsigned int GLYPH_Y_COUNT_PER_PAGE = 16;

            static const unsigned int GLYPH_PAGE_COUNT     = 2;
            static const unsigned int GLYPH_COUNT_PER_PAGE = GLYPH_X_COUNT_PER_PAGE * GLYPH_Y_COUNT_PER_PAGE;

            static const unsigned int GLYPH_X_COUNT = GLYPH_X_COUNT_PER_PAGE * GLYPH_PAGE_COUNT;
            static const unsigned int GLYPH_Y_COUNT = GLYPH_Y_COUNT_PER_PAGE;
            static const unsigned int GLYPH_COUNT   = GLYPH_X_COUNT * GLYPH_Y_COUNT;

            static const unsigned int TILE_DISPLACEMENT_COUNT  = 3;
            static const unsigned int TILE_ORIENTATION_COUNT   = 8;
            static const unsigned int TILE_CONFIGURATION_COUNT = TILE_DISPLACEMENT_COUNT * TILE_ORIENTATION_COUNT;

            ruukku::Int2 glyphPixelSize;
            ruukku::Int2 glyphPixelSizeOnTexture;
            ruukku::Int2 glyphTextureSize;

            ruukku::Int2 tilePixelSize;
            ruukku::Int2 tilePixelSizeOnTexture;
            ruukku::Int2 tileTextureSize;

            std::unique_ptr< ruukku::GLTexture2D > glyphTexture;
            std::unique_ptr< ruukku::GLTexture2D > tileTexture;

            std::array< ruukku::GLFloatVec2, GLYPH_COUNT > glyphOrigoList;
            std::array< ruukku::GLFloatVec2, GLYPH_COUNT > tileOrigoList;

            ruukku::GLFloatVec2 glyphSpanOnTexture;

            std::array< ruukku::GLFloatVec2, TILE_CONFIGURATION_COUNT > tileSubOrigoList;
            std::array< ruukku::GLFloatVec2, TILE_ORIENTATION_COUNT   > tileUAxisList;
            std::array< ruukku::GLFloatVec2, TILE_ORIENTATION_COUNT   > tileVAxisList;

            unsigned int getTileConfiguration(const TileInfo& info) const;

            void buildGlyphData(const ruukku::Surface& surface);
            void buildTileData(const ruukku::Surface& surface);

            void readGlyphToTexture(ruukku::Field2< std::uint8_t >& texture, const ruukku::Surface& source, const ruukku::Int2& where, const ruukku::IntRect& area) const;
    };

    inline const ruukku::GLTexture2D* GlyphSet::getGlyphSheet() const { return glyphTexture.get(); }
    inline const ruukku::GLTexture2D* GlyphSet::getTileSheet()  const { return tileTexture.get(); }

    inline ruukku::GLFloatVec2 GlyphSet::getGlyphOrigo(const unsigned int index) const {
        assert(index < glyphOrigoList.size());
        return glyphOrigoList[index];
    }

    inline ruukku::GLFloatVec2 GlyphSet::getTileOrigo(const TileInfo& info) const {
        assert(info.glyphIndex < glyphOrigoList.size());
        assert(info.getDisplacementIndex() < TILE_DISPLACEMENT_COUNT);
        assert(info.getOrientationIndex()  < TILE_ORIENTATION_COUNT);
        return tileOrigoList[info.glyphIndex] + tileSubOrigoList[getTileConfiguration(info)];
    }

    inline const ruukku::GLFloatVec2 GlyphSet::getGlyphSpanOnTexture() const { return glyphSpanOnTexture; }

    inline const ruukku::GLFloatVec2& GlyphSet::getTileUAxisSpan(const TileInfo& info) const {
        assert(info.getOrientationIndex() < TILE_ORIENTATION_COUNT);
        return tileUAxisList[info.getOrientationIndex()];
    }

    inline const ruukku::GLFloatVec2& GlyphSet::getTileVAxisSpan(const TileInfo& info) const {
        assert(info.getOrientationIndex() < TILE_ORIENTATION_COUNT);
        return tileVAxisList[info.getOrientationIndex()];
    }

    inline unsigned int GlyphSet::getGlyphCount() { return GLYPH_COUNT; }

    inline unsigned int GlyphSet::getTileConfiguration(const TileInfo& info) const { return info.getOrientationIndex() + info.getDisplacementIndex() * TILE_ORIENTATION_COUNT; }
};

#endif /* RUNRUN_GLYPHSET_HPP */


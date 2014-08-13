/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    foresttilevisualizer.hpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

/*
 * Concrete tile visualizer for forest biome.
 */

#ifndef RUNRUN_FORESTTILEVISUALIZER_HPP
#define RUNRUN_FORESTTILEVISUALIZER_HPP

#include "ruukku/opengl/gltypes.hpp"
#include "tilevisualizer.hpp"

namespace runrun {
    class ForestTileVisualizer : public TileVisualizer {
        public:
            TileVisualizer*      createCopy() const;
            TileStaticRenderInfo getRenderInfo(const TileKernel& kernel, const TileStaticRenderData::Layer layer) const;

        private:
            TileStaticRenderInfo getRenderInfoFront (const TileKernel& kernel) const;
            TileStaticRenderInfo getRenderInfoBack  (const TileKernel& kernel) const;

            ruukku::GLFloatRGBA getColorSoilA   () const;
            ruukku::GLFloatRGBA getColorSoilB   () const;
            ruukku::GLFloatRGBA getColorRockA   () const;
            ruukku::GLFloatRGBA getColorRockB   () const;
            ruukku::GLFloatRGBA getColorPlant   () const;
            ruukku::GLFloatRGBA getColorFoliage () const;
            ruukku::GLFloatRGBA getColorFungi   () const;
    };

    inline TileVisualizer* ForestTileVisualizer::createCopy() const { return new ForestTileVisualizer(*this); }
};

#endif /* RUNRUN_FORESTTILEVISUALIZER_HPP */


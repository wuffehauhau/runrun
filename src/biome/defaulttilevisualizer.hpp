/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    defaulttilevisualizer.hpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

/*
 * Default visualizer that outputs pink tiles.
 */

#ifndef RUNRUN_DEFAULTTILEVISUALIZER_HPP
#define RUNRUN_DEFAULTTILEVISUALIZER_HPP

#include "tilevisualizer.hpp"

namespace runrun {
    class DefaultTileVisualizer : public TileVisualizer {
        public:
            TileVisualizer*      createCopy() const;
            TileStaticRenderInfo getRenderInfo(const TileKernel& kernel, const TileStaticRenderData::Layer layer) const;
    };

    inline TileVisualizer* DefaultTileVisualizer::createCopy() const { return new DefaultTileVisualizer(*this); }

    inline TileStaticRenderInfo DefaultTileVisualizer::getRenderInfo(const TileKernel& kernel, const TileStaticRenderData::Layer layer) const {
        return TileStaticRenderInfo(TileInfo(219), ruukku::GLFloatRGBA(1.0f, 0.0f, 1.0f, 1.0f), ruukku::GLFloatRGBA(1.0f, 0.0f, 1.0f, 1.0f));
    }

};

#endif /* RUNRUN_DEFAULTTILEVISUALIZER_HPP */


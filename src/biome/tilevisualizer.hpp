/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilevisualizer.hpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

/*
 * An interface for converting tiles to rendering information.
 */

#ifndef RUNRUN_TILEVISUALIZER_HPP
#define RUNRUN_TILEVISUALIZER_HPP

#include "ruukku/math/rng.hpp"
#include "ruukku/math/field2.hpp"

#include "glyph/tilestaticrenderdata.hpp"
#include "glyph/tilestaticrenderinfo.hpp"
#include "metrics/mapmetrics.hpp"
#include "tile/tilekernel.hpp"

namespace runrun {
    class TileVisualizer {
        public:
            TileVisualizer();
            virtual ~TileVisualizer() {}

            virtual TileVisualizer*      createCopy() const = 0;
            virtual TileStaticRenderInfo getRenderInfo(const TileKernel& kernel, const TileStaticRenderData::Layer layer) const = 0;

        protected:
            std::uint32_t getRandomValue(const ruukku::Int2& position) const;

            ruukku::GLFloatRGBA getColorWhite() const;
            ruukku::GLFloatRGBA getColorBlack() const;
            ruukku::GLFloatRGBA getColorTransparent() const;

            ruukku::GLFloatRGBA getWithNoise(const ruukku::GLFloatRGBA& c, GLfloat noise) const;
            ruukku::GLFloatRGBA getWithAlpha(const ruukku::GLFloatRGBA& c, GLfloat alpha) const;

            TileInfo::Orientation getOrientation(const TileOrientation& orientation) const;

        private:
            ruukku::Field2< std::uint32_t > randomMap;

            static ruukku::RNG rng;
    };

    inline std::uint32_t TileVisualizer::getRandomValue(const ruukku::Int2& position) const {
        return randomMap[ruukku::Int2(position.x % MapMetrics::MAP_DIM_IN_TILES, position.y % MapMetrics::MAP_DIM_IN_TILES)];
    }

    inline ruukku::GLFloatRGBA TileVisualizer::getColorWhite()       const { return ruukku::GLFloatRGBA(1.0f, 1.0f, 1.0f, 1.0f); }
    inline ruukku::GLFloatRGBA TileVisualizer::getColorBlack()       const { return ruukku::GLFloatRGBA(0.0f, 0.0f, 0.0f, 1.0f); }
    inline ruukku::GLFloatRGBA TileVisualizer::getColorTransparent() const { return ruukku::GLFloatRGBA(0.0f, 0.0f, 0.0f, 0.0f); }

    inline ruukku::GLFloatRGBA TileVisualizer::getWithAlpha(const ruukku::GLFloatRGBA& c, const GLfloat alpha) const { return ruukku::GLFloatRGBA(c.r, c.g, c.b, alpha * c.a); }
    inline ruukku::GLFloatRGBA TileVisualizer::getWithNoise(const ruukku::GLFloatRGBA& c, const GLfloat noise) const {
        const GLfloat delta = 1.0f - noise * rng.genReal< GLfloat >();
        return ruukku::GLFloatRGBA(delta * c.r, delta * c.g, delta * c.b, c.a);
    }

    inline TileInfo::Orientation TileVisualizer::getOrientation(const TileOrientation& orientation) const {
        switch (orientation) {
            case TileOrientation::LeftBottom:  return TileInfo::Orientation::Normal;
            case TileOrientation::RightBottom: return TileInfo::Orientation::UpsideDownCCW180;
            case TileOrientation::LeftTop:     return TileInfo::Orientation::UpsideDown;
            case TileOrientation::RightTop:    return TileInfo::Orientation::CCW180;
        }

        return TileInfo::Orientation::Normal;
    }
};

#endif /* RUNRUN_TILEVISUALIZER_HPP */


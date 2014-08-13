/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilestaticrenderinfo.hpp
 * Created: 2014-06-07
 * Authors: Jani Salo
 */

/*
 * Stores tile glyph and color.
 */

#ifndef RUNRUN_TILESTATICRENDERINFO_HPP
#define RUNRUN_TILESTATICRENDERINFO_HPP

#include "ruukku/opengl/gltypes.hpp"
#include "tileinfo.hpp"

namespace runrun {
    class TileStaticRenderInfo {
        public:
            TileInfo tileInfo;

            ruukku::GLFloatRGBA colorFront;
            ruukku::GLFloatRGBA colorBack;

            TileStaticRenderInfo() {}
            TileStaticRenderInfo(
                const TileInfo             tileInfo,
                const ruukku::GLFloatRGBA& colorFront,
                const ruukku::GLFloatRGBA& colorBack
            ) :
                tileInfo   (tileInfo),
                colorFront (colorFront),
                colorBack  (colorBack)
            {}
    };
};

#endif /* RUNRUN_TILESTATICRENDERINFO_HPP */


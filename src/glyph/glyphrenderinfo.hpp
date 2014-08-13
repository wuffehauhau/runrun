/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphrenderinfo.hpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

/*
 * Stores information for rendering a single glyph.
 */

#ifndef RUNRUN_GLYPHRENDERINFO_HPP
#define RUNRUN_GLYPHRENDERINFO_HPP

#include "ruukku/opengl/gltypes.hpp"

namespace runrun {
    class GlyphRenderInfo {
        public:
            unsigned int glyphIndex;

            // Format: posXY
            ruukku::GLFloatVec2 pos00;
            ruukku::GLFloatVec2 pos10;
            ruukku::GLFloatVec2 pos11;
            ruukku::GLFloatVec2 pos01;

            ruukku::GLFloatRGBA color;

            GlyphRenderInfo() {}
            GlyphRenderInfo(
                const unsigned int glyphIndex,
                const ruukku::GLFloatVec2& pos00,
                const ruukku::GLFloatVec2& pos10,
                const ruukku::GLFloatVec2& pos11,
                const ruukku::GLFloatVec2& pos01,
                const ruukku::GLFloatRGBA& color
            ) :
                glyphIndex(glyphIndex),
                pos00(pos00),
                pos10(pos10),
                pos11(pos11),
                pos01(pos01),
                color(color)
            {}

            GlyphRenderInfo getTransformed(const ruukku::GLFloatMat3 tf) const;
    };
};

#endif /* RUNRUN_GLYPHRENDERINFO_HPP */


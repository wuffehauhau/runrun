/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframe.hpp
 * Created: 2014-05-30
 * Authors: Jani Salo
 */

/*
 * Encapsulates object frame data.
 */

#ifndef RUNRUN_OBJECTFRAME_HPP
#define RUNRUN_OBJECTFRAME_HPP

#include <vector>

#include "ruukku/opengl/gltypes.hpp"
#include "glyph/glyphrenderinfo.hpp"

namespace runrun {
    class ObjectFrame {
        public:
            ObjectFrame() : length(0) {}
            ObjectFrame(const unsigned int length, const std::vector< GlyphRenderInfo >& glyphList);

            unsigned int                          getLength()    const;
            const std::vector< GlyphRenderInfo >& getGlyphList() const;

            ObjectFrame getTransformed(const ruukku::GLFloatMat3 tf) const;

        private:
            unsigned int length;
            std::vector< GlyphRenderInfo > glyphList;
    };

    inline ObjectFrame::ObjectFrame(
        const unsigned int length,
        const std::vector< GlyphRenderInfo >& glyphList
    ) : length(length), glyphList(glyphList) {}

    inline unsigned int ObjectFrame::getLength() const { return length; }
    inline const std::vector< GlyphRenderInfo >& ObjectFrame::getGlyphList() const { return glyphList; }
};

#endif /* RUNRUN_OBJECTFRAME_HPP */


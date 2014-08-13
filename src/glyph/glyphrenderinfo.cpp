/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphrenderinfo.cpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

#include "glyphrenderinfo.hpp"

using namespace ruukku;

namespace runrun {
    GlyphRenderInfo GlyphRenderInfo::getTransformed(const GLFloatMat3 tf) const {
        return GlyphRenderInfo(
            glyphIndex,
            tf.transform(pos00),
            tf.transform(pos10),
            tf.transform(pos11),
            tf.transform(pos01),
            color
        );
    }
};


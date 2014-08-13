/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframe.cpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

#include "objectframe.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    ObjectFrame ObjectFrame::getTransformed(const GLFloatMat3 tf) const {
        vector< GlyphRenderInfo > newGlyphList;
        for (const GlyphRenderInfo& info : glyphList) {
            newGlyphList.push_back(info.getTransformed(tf));
        }

        return ObjectFrame(length, newGlyphList);
    }
};


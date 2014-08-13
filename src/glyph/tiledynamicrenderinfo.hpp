/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tiledynamicrenderinfo.hpp
 * Created: 2014-06-08
 * Authors: Jani Salo
 */

/*
 * Stores tile light.
 */

#ifndef RUNRUN_TILEDYNAMICRENDERINFO_HPP
#define RUNRUN_TILEDYNAMICRENDERINFO_HPP

#include "ruukku/opengl/gltypes.hpp"

namespace runrun {
    class TileDynamicRenderInfo {
        public:
            ruukku::GLFloatRGBA light;

            TileDynamicRenderInfo()                                                {}
            TileDynamicRenderInfo(const ruukku::GLFloatRGBA& light) : light(light) {}
    };
};

#endif /* RUNRUN_TILEDYNAMICRENDERINFO_HPP */


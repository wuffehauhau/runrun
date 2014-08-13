/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    maptemplatepixelkernel.hpp
 * Created: 2014-07-30
 * Authors: Jani Salo
 */

/*
 * A class for handling map template pixel data.
 */

#ifndef RUNRUN_MAPTEMPLATEPIXELKERNEL_HPP
#define RUNRUN_MAPTEMPLATEPIXELKERNEL_HPP

#include <array>
#include <functional>

#include "ruukku/pixel/rgba32.hpp"
#include "kernel/pluskernel.hpp"
#include "tile/tileorientation.hpp"

namespace runrun {
     class MapTemplatePixelKernel : public PlusKernel< ruukku::RGBA32 > {
        public:
            MapTemplatePixelKernel() {}
            MapTemplatePixelKernel(const ruukku::RGBA32& c, const ruukku::RGBA32& l, const ruukku::RGBA32& r, const ruukku::RGBA32& b, const ruukku::RGBA32& t) : PlusKernel(c, l, r, b, t) {}
    };
};

#endif /* RUNRUN_MAPTEMPLATEPIXELKERNEL_HPP */


/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    pixelvolume.hpp
 * Created: 2012-12-22
 * Authors: Jani Salo
 */

/*
 * A container for a RGBA volume.
 */

#ifndef RUUKKU_PIXELVOLUME_HPP
#define RUUKKU_PIXELVOLUME_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "../math/field3.hpp"
#include "rgba32.hpp"

namespace ruukku {
    class PixelVolume : public Field3< RGBA32 > {
        public:
            PixelVolume() {}
            PixelVolume(const Int3& size) : Field3< RGBA32 >(size) {}
    };
};

#endif /* RUUKKU_PIXELVOLUME_HPP */


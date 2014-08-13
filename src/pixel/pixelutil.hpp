/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    pixelutil.hpp
 * Created: 2014-08-03
 * Authors: Jani Salo
 */

/*
 * Collection of pixel utilities.
 */

#ifndef RUNRUN_PIXELUTIL_HPP
#define RUNRUN_PIXELUTIL_HPP

#include "ruukku/pixel/surface.hpp"

namespace runrun {
    class PixelUtil {
        public:
            // Copies a rectangle from source to target position on
            // destination, and then extends the borders of the copied
            // rectangle by one pixel in each direction.
            static void copyAndExtendedEdges(
                      ruukku::Surface& destination,
                const ruukku::Surface& source,
                const ruukku::Int2&    where,
                const ruukku::IntRect& area
            );
    };
};

#endif /* RUNRUN_PIXELUTIL_HPP */


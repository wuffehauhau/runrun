/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    pixelutil.cpp
 * Created: 2014-08-03
 * Authors: Jani Salo
 */

#include "pixelutil.hpp"
#include "ruukku/math/field2.hpp"

using namespace ruukku;

namespace runrun {
    void PixelUtil::copyAndExtendedEdges(
              Surface& destination,
        const Surface& source,
        const Int2&    where,
        const IntRect& area
    ) {
        destination.copy(where, source, area);

        for (int x = 0; x < area.sizeX; x++) {
            destination[where + Int2(x, -1)]         = destination[where + Int2(x, 0)];
            destination[where + Int2(x, area.sizeY)] = destination[where + Int2(x, area.sizeY - 1)];
        }

        for (int y = 0; y < area.sizeY; y++) {
            destination[where + Int2(-1, y)]         = destination[where + Int2(0, y)];
            destination[where + Int2(area.sizeX, y)] = destination[where + Int2(area.sizeX - 1, y)];
        }

        destination[where + Int2(-1, -1)]                 = destination[where];
        destination[where + Int2(area.sizeX, -1)]         = destination[where + Int2(area.sizeX - 1, 0)];
        destination[where + Int2(-1, area.sizeY)]         = destination[where + Int2(0, area.sizeY - 1)];
        destination[where + Int2(area.sizeX, area.sizeY)] = destination[where + Int2(area.sizeX - 1, area.sizeY - 1)];
    }
};


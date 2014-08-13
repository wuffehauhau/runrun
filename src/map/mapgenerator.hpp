/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mapgenerator.hpp
 * Created: 2014-07-01
 * Authors: Jani Salo
 */

/*
 * A generator for map data.
 */

#ifndef RUNRUN_MAPGENERATOR_HPP
#define RUNRUN_MAPGENERATOR_HPP

#include <string>

#include "ruukku/pixel/surface.hpp"
#include "tile/tileattributes.hpp"
#include "tile/tileorientation.hpp"

#include "maptemplatepixelkernel.hpp"
#include "map.hpp"

namespace runrun {
    class MapGenerator {
        public:
            Map* newMapFromTemplate(const std::string& path) const;

        private:
            MapTemplatePixelKernel getKernel(const ruukku::Surface& surface, const ruukku::Int2& position) const;

            TileAttributes::GeneralType   getGeneralType   (const ruukku::RGBA32& pixel) const;
            TileAttributes::PrimaryType   getPrimaryType   (const ruukku::RGBA32& pixel) const;
            TileAttributes::SecondaryType getSecondaryType (const ruukku::RGBA32& pixel) const;

            TileOrientation getOrientation(const EdgeFlags flags) const;
    };
};

#endif /* RUNRUN_MAPGENERATOR_HPP */


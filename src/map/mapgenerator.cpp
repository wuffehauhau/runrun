/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mapgenerator.cpp
 * Created: 2014-07-01
 * Authors: Jani Salo
 */

#include <memory>

#include "ruukku/pixel/surface.hpp"
#include "metrics/mapmetrics.hpp"

#include "mapgenerator.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    Map* MapGenerator::newMapFromTemplate(const string& path) const {
        Surface terrain;

        terrain.readPNG(path + string("/terrain.png"));
        const Int2 sizeInTiles(terrain.getSize());
        terrain.flip(false, true);

        if (
            (sizeInTiles.x > MapMetrics::MAP_DIM_IN_TILES) ||
            (sizeInTiles.y > MapMetrics::MAP_DIM_IN_TILES) ||
            (sizeInTiles.x % MapMetrics::CELL_DIM != 0)    ||
            (sizeInTiles.y % MapMetrics::CELL_DIM != 0)
        ) {
            throw runtime_error(string("Invalid map size in map template."));
        }

        const Int2 sizeInCells(sizeInTiles.x / MapMetrics::CELL_DIM, sizeInTiles.y / MapMetrics::CELL_DIM);
        unique_ptr< Map > map = unique_ptr< Map >(new Map(sizeInCells));

        // First pass to read tiles.
        map->loopTiles([&](Tile& tile, const Int2& position) {
            const MapTemplatePixelKernel kernel = getKernel(terrain, position);
            TileRecord tileRecord;

            tileRecord.attributes.generalType = getGeneralType(kernel.c);
            if (tileRecord.attributes.generalType == TileAttributes::GeneralType::Slope) {
                EdgeFlags info =  kernel.read([&](const RGBA32& pixel, const KernelTestType type) {
                    switch (type) {
                        case KernelTestType::TestIn:  return getGeneralType(pixel) != TileAttributes::GeneralType::Block;
                        case KernelTestType::TestOut: return getGeneralType(pixel) == TileAttributes::GeneralType::Block;
                        default: return false;
                    }
                });

                tileRecord.orientation = getOrientation(info);
            }

            tileRecord.attributes.primaryType   = getPrimaryType(kernel.c);
            tileRecord.attributes.secondaryType = getSecondaryType(kernel.c);

            tile = map->getTileFactory().createTile(tileRecord);
        });

        return map.release();
    }

    MapTemplatePixelKernel MapGenerator::getKernel(const Surface& surface, const ::Int2& position) const {
        const Int2 positionL = position + Int2(-1,  0);
        const Int2 positionR = position + Int2( 1,  0);
        const Int2 positionD = position + Int2( 0, -1);
        const Int2 positionU = position + Int2( 0,  1);

        return MapTemplatePixelKernel(
            surface[position],
            surface.isInside(positionL) ? surface[positionL] : RGBA32(0, 0, 0, 0),
            surface.isInside(positionR) ? surface[positionR] : RGBA32(0, 0, 0, 0),
            surface.isInside(positionD) ? surface[positionD] : RGBA32(0, 0, 0, 0),
            surface.isInside(positionU) ? surface[positionU] : RGBA32(0, 0, 0, 0)
        );
    }

    TileAttributes::GeneralType MapGenerator::getGeneralType(const ruukku::RGBA32& pixel) const {
        switch (pixel.r) {
            case 0xF0: return TileAttributes::GeneralType::Block;
            case 0xE0: return TileAttributes::GeneralType::Slope;
        }

        return TileAttributes::GeneralType::Space;
    }

    TileAttributes::PrimaryType MapGenerator::getPrimaryType(const ruukku::RGBA32& pixel) const {
        switch (pixel.g) {
            case 0xF0: return TileAttributes::PrimaryType::Soil;
            case 0xE0: return TileAttributes::PrimaryType::Rock;
            case 0xD0: return TileAttributes::PrimaryType::Plant;
        }

        return TileAttributes::PrimaryType::None;
    }

    TileAttributes::SecondaryType MapGenerator::getSecondaryType(const ruukku::RGBA32& pixel) const {
        switch (pixel.b) {
            case 0xF0: return TileAttributes::SecondaryType::Foliage;
            case 0xE0: return TileAttributes::SecondaryType::Fungi;
        }

        return TileAttributes::SecondaryType::None;
    }

    TileOrientation MapGenerator::getOrientation(const EdgeFlags flags) const {
        switch (flags.getBits()) {
            case static_cast< uint32_t >(EdgeFlag::LeftBottom):  return TileOrientation::LeftBottom;
            case static_cast< uint32_t >(EdgeFlag::RightBottom): return TileOrientation::RightBottom;
            case static_cast< uint32_t >(EdgeFlag::LeftTop):     return TileOrientation::LeftTop;
            case static_cast< uint32_t >(EdgeFlag::RightTop):    return TileOrientation::RightTop;
        }

        return TileOrientation::Undefined;
    }
};


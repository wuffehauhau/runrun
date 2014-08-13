/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    foresttilevisualizer.cpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

#include <cassert>
#include "foresttilevisualizer.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    TileStaticRenderInfo ForestTileVisualizer::getRenderInfo(const TileKernel& kernel, const TileStaticRenderData::Layer layer) const {
        switch (layer) {
            case TileStaticRenderData::Layer::Front: return getRenderInfoFront(kernel);
            case TileStaticRenderData::Layer::Back: return getRenderInfoBack(kernel);
            default: assert(false);
        }
    }

    inline TileStaticRenderInfo ForestTileVisualizer::getRenderInfoFront(const TileKernel& kernel) const {
        TileStaticRenderInfo info(TileInfo(0), getColorTransparent(), getColorTransparent());

        const TileRecord& record = kernel.c.getRecord();
        const uint32_t randomValue = getRandomValue(kernel.position);

        switch (record.attributes.generalType) {
            case TileAttributes::GeneralType::Space: {                          // General type: space
                switch (record.attributes.primaryType) {
                    case TileAttributes::PrimaryType::Plant: {                  // Primary type: plant
                        EdgeFlags edgeFlags = kernel.read([&](const Tile& tile, const KernelTestType type) {
                            switch (type) {
                                case KernelTestType::TestIn: {
                                    return (
                                        tile.getRecord().attributes.primaryType == TileAttributes::PrimaryType::Plant ||
                                        tile.getRecord().attributes.generalType == TileAttributes::GeneralType::Block
                                    );
                                }
                                case KernelTestType::TestOut: {
                                    return (
                                        tile.getRecord().attributes.primaryType != TileAttributes::PrimaryType::Plant &&
                                        tile.getRecord().attributes.generalType != TileAttributes::GeneralType::Block
                                    );
                                }
                                default: return false;
                            }
                        });

                        switch (edgeFlags.getBits()) {
                            case static_cast< uint32_t >(EdgeFlag::Top):
                            case static_cast< uint32_t >(EdgeFlag::LeftTop):
                            case static_cast< uint32_t >(EdgeFlag::RightTop):
                            case static_cast< uint32_t >(EdgeFlag::TopHalf): {
                                info.tileInfo = TileInfo(99, TileInfo::Displacement::BaseLine);
                                info.colorFront = getColorPlant();
                                break;
                            }
                            case static_cast< uint32_t >(EdgeFlag::Bottom):
                            case static_cast< uint32_t >(EdgeFlag::LeftBottom):
                            case static_cast< uint32_t >(EdgeFlag::RightBottom):
                            case static_cast< uint32_t >(EdgeFlag::BottomHalf): {
                                info.tileInfo = TileInfo(114, TileInfo::Displacement::BaseLine);
                                info.colorFront = getColorPlant();
                                break;
                            }
                            default: {
                                info.tileInfo = TileInfo(110, TileInfo::Displacement::BaseLine);
                                info.colorFront = getColorPlant();
                                break;
                            }
                        }

                        break;
                    }
                }

                break;
            }
            case TileAttributes::GeneralType::Block: {                          // General type: block
                EdgeFlags edgeFlags = kernel.read([&](const Tile& tile, const KernelTestType type) {
                    switch (type) {
                        case KernelTestType::TestIn:  return tile.getRecord().attributes.generalType == TileAttributes::GeneralType::Block;
                        case KernelTestType::TestOut: return tile.getRecord().attributes.generalType == TileAttributes::GeneralType::Space;
                        default: return false;
                    }
                });

                bool isDeepBlock = false;
                switch (edgeFlags.getBits()) {
                    case static_cast< uint32_t >(EdgeFlag::Top):
                    case static_cast< uint32_t >(EdgeFlag::TopHalf): {
                        info.tileInfo = TileInfo(34, TileInfo::Displacement::Middle);
                        break;
                    }
                    case static_cast< uint32_t >(EdgeFlag::LeftTop):
                    case static_cast< uint32_t >(EdgeFlag::RightTop):
                    case static_cast< uint32_t >(EdgeFlag::LeftBottom):
                    case static_cast< uint32_t >(EdgeFlag::RightBottom): {
                        info.tileInfo = TileInfo(43, TileInfo::Displacement::BaseLine);
                        break;
                    }
                    case static_cast< uint32_t >(EdgeFlag::Bottom):
                    case static_cast< uint32_t >(EdgeFlag::BottomHalf): {
                        info.tileInfo = TileInfo(126, TileInfo::Displacement::Middle, TileInfo::Orientation::UpsideDown);
                        break;
                    }
                    case static_cast< uint32_t >(EdgeFlag::LeftHalf):
                    case static_cast< uint32_t >(EdgeFlag::RightHalf): {
                        info.tileInfo = TileInfo(42, TileInfo::Displacement::BaseLine);
                        break;
                    }
                    default: {
                        isDeepBlock = true;
                        if (randomValue % 32 == 0) info.tileInfo = TileInfo(46);
                        else                       info.tileInfo = TileInfo(32);

                        break;
                    }
                }

                switch (record.attributes.primaryType) {
                    case TileAttributes::PrimaryType::Soil: {                   // Primary type: soil
                        if (isDeepBlock) info.colorFront = getColorRockA();
                        else             info.colorFront = getColorSoilB();

                        info.colorBack  = getColorSoilA();
                        break;
                    }
                    case TileAttributes::PrimaryType::Rock: {                   // Primary type: rock
                        if (isDeepBlock) info.colorFront = getColorSoilA();
                        else             info.colorFront = getColorRockB();
                        info.colorBack  = getColorRockA();
                        break;
                    }
                }

                break;
            }
            case TileAttributes::GeneralType::Slope: {                          // General type: slope
                info.tileInfo = TileInfo(22, TileInfo::Displacement::BaseLine, getOrientation(record.orientation));

                switch (record.attributes.primaryType) {
                    case TileAttributes::PrimaryType::Soil: {                   // Primary type: soil
                        info.colorFront = getColorSoilB();
                        break;
                    }
                    case TileAttributes::PrimaryType::Rock: {                   // Primary type: rock
                        info.colorFront = getColorRockB();
                        break;
                    }
                } break;
            }
        }

        return info;
    }

    inline TileStaticRenderInfo ForestTileVisualizer::getRenderInfoBack(const TileKernel& kernel) const {
        TileStaticRenderInfo info(TileInfo(0), getColorTransparent(), getColorTransparent());
        const TileRecord& record = kernel.c.getRecord();

        switch (record.attributes.secondaryType) {
            case TileAttributes::SecondaryType::Foliage: {                      // Secondary type: foliage
                info.tileInfo = TileInfo(145, TileInfo::Displacement::BaseLine);
                info.colorFront = getColorFoliage();
                break;
            }
            case TileAttributes::SecondaryType::Fungi: {                        // Secondary type: fungi
                EdgeFlags edgeFlags = kernel.read([&](const Tile& tile, const KernelTestType type) {
                    switch (type) {
                        case KernelTestType::TestIn: {
                            return (
                                tile.getRecord().attributes.secondaryType == TileAttributes::SecondaryType::Fungi ||
                                tile.getRecord().attributes.generalType   == TileAttributes::GeneralType::Block
                            );
                        }
                        case KernelTestType::TestOut: {
                            return (
                                tile.getRecord().attributes.secondaryType != TileAttributes::SecondaryType::Fungi &&
                                tile.getRecord().attributes.generalType   != TileAttributes::GeneralType::Block
                            );
                        }
                        default: return false;
                    }
                });

                switch (edgeFlags.getBits()) {
                    case static_cast< uint32_t >(EdgeFlag::Top):
                    case static_cast< uint32_t >(EdgeFlag::LeftTop):
                    case static_cast< uint32_t >(EdgeFlag::RightTop):
                    case static_cast< uint32_t >(EdgeFlag::TopHalf): {
                        info.tileInfo = TileInfo(84, TileInfo::Displacement::Middle);
                        info.colorFront = getColorFungi();
                        break;
                    }
                    case static_cast< uint32_t >(EdgeFlag::Bottom):
                    case static_cast< uint32_t >(EdgeFlag::LeftBottom):
                    case static_cast< uint32_t >(EdgeFlag::RightBottom):
                    case static_cast< uint32_t >(EdgeFlag::BottomHalf): {
                        info.tileInfo = TileInfo(84, TileInfo::Displacement::Middle, TileInfo::Orientation::UpsideDown);
                        info.colorFront = getColorFungi();
                        break;
                    }
                    default: {
                        info.tileInfo = TileInfo(73, TileInfo::Displacement::BaseLine);
                        info.colorFront = getColorFungi();
                        break;
                    }
                }

                break;
            }
        }

        info.colorFront = 0.75f * info.colorFront + 0.25f * info.colorBack;
        return info;
    }

    GLFloatRGBA ForestTileVisualizer::getColorSoilA   () const { return GLFloatRGBA(204.0f / 255.0f, 140.0f / 255.0f, 76.0f / 255.0f, 1.0f); }
    GLFloatRGBA ForestTileVisualizer::getColorSoilB   () const { return GLFloatRGBA(224.0f / 255.0f, 185.0f / 255.0f, 90.0f / 255.0f, 1.0f); }
    GLFloatRGBA ForestTileVisualizer::getColorRockA   () const { return GLFloatRGBA(156.0f / 255.0f,  93.0f / 255.0f, 40.0f / 255.0f, 1.0f); }
    GLFloatRGBA ForestTileVisualizer::getColorRockB   () const { return GLFloatRGBA(112.0f / 255.0f,  66.0f / 255.0f, 29.0f / 255.0f, 1.0f); }
    GLFloatRGBA ForestTileVisualizer::getColorPlant   () const { return GLFloatRGBA(150.0f / 255.0f, 167.0f / 255.0f, 61.0f / 255.0f, 1.0f); }
    GLFloatRGBA ForestTileVisualizer::getColorFoliage () const { return GLFloatRGBA(141.0f / 255.0f, 144.0f / 255.0f, 57.0f / 255.0f, 1.0f); }
    GLFloatRGBA ForestTileVisualizer::getColorFungi   () const { return GLFloatRGBA(145.0f / 255.0f, 131.0f / 255.0f, 92.0f / 255.0f, 1.0f); }
};

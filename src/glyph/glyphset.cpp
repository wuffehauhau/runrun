/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphset.cpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

#include <iostream>

#include "ruukku/opengl/glerror.hpp"
#include "algorithm/powersoftwo.hpp"
#include "geometry/transformations.hpp"

#include "glyphset.hpp"
#include "pixel/pixelutil.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    GlyphSet::GlyphSet(const ruukku::Surface& surface) {
        if (surface.getSize().x % GLYPH_X_COUNT != 0 || surface.getSize().y % GLYPH_Y_COUNT != 0) {
            throw runtime_error("Invalid glyph map dimensions, size must be evenly divisible by horizontal and vertical glyph counts.");
        }

        if (
            surface.getSize().x < 2 * GLYPH_X_COUNT || surface.getSize().x > 32 * GLYPH_X_COUNT ||
            surface.getSize().y < 4 * GLYPH_Y_COUNT || surface.getSize().y > 64 * GLYPH_Y_COUNT
        ) {
            throw runtime_error("Invalid glyph map dimensions, minimum size is 2x4 pixels per glyph and maximum 32x64 pixels per glyph.");
        }

        glyphPixelSize = Int2(surface.getSize().x / GLYPH_X_COUNT, surface.getSize().y / GLYPH_Y_COUNT);
        glyphPixelSizeOnTexture = glyphPixelSize + Int2(2, 2);

        if (glyphPixelSize.y != 2 * glyphPixelSize.x) throw runtime_error("Invalid glyph map dimensions, glyph height must be exactly twice the glyph width.");
        if (glyphPixelSize.y % 4 != 0)                throw runtime_error("Invalid glyph map dimensions, glyph height must be divisible by four.");

        tilePixelSize = Int2(surface.getSize().x / GLYPH_X_COUNT, surface.getSize().y / GLYPH_Y_COUNT / 2);
        tilePixelSizeOnTexture = tilePixelSize + Int2(2, 2);

        glyphTextureSize = Int2(
            PowersOfTwo(GLYPH_X_COUNT * glyphPixelSizeOnTexture.x).getLeastGreaterOrEqual(),
            PowersOfTwo(GLYPH_Y_COUNT * glyphPixelSizeOnTexture.y).getLeastGreaterOrEqual()
        );

        tileTextureSize = Int2(
            PowersOfTwo(GLYPH_X_COUNT * tilePixelSizeOnTexture.x).getLeastGreaterOrEqual(),
            PowersOfTwo(GLYPH_Y_COUNT * tilePixelSizeOnTexture.y * TILE_DISPLACEMENT_COUNT).getLeastGreaterOrEqual()
        );

        // DEBUG
        // cout << "Glyph values: " << glyphPixelSize.x << ", " << glyphPixelSize.y << "; " << glyphPixelSizeOnTexture.x << ", " << glyphPixelSizeOnTexture.y << "; " << glyphTextureSize.x << ", " << glyphTextureSize.y << endl;
        // cout << "Tile values:  " << tilePixelSize.x  << ", " << tilePixelSize.y  << "; " << tilePixelSizeOnTexture.x  << ", " << tilePixelSizeOnTexture.y  << "; " << tileTextureSize.x << ", "  << tileTextureSize.y << endl;

        buildGlyphData(surface);
        buildTileData(surface);
    }

    void GlyphSet::buildGlyphData(const Surface& surface) {
        Field2< uint8_t > alphaMap;
        alphaMap.resize(glyphTextureSize);

        Surface buffer;
        buffer.resize(glyphPixelSizeOnTexture);

        for (unsigned int y = 0; y < GLYPH_Y_COUNT; y++) {
            for (unsigned int x = 0; x < GLYPH_X_COUNT; x++) {
                const Int2 sPos(x * glyphPixelSize.x, y * glyphPixelSize.y);
                const Int2 dPos(x * glyphPixelSizeOnTexture.x, y * glyphPixelSizeOnTexture.y);

                PixelUtil::copyAndExtendedEdges(buffer, surface, Int2(1, 1), IntRect(sPos.x, sPos.y, glyphPixelSize.x, glyphPixelSize.y));
                readGlyphToTexture(alphaMap, buffer, dPos, IntRect(0, 0, buffer.getSize().x, buffer.getSize().y));
            }
        }

        // DEBUG
        // Surface temp(alphaMap.getSize());
        // alphaMap.loop([&](const uint8_t value, const Int2& position) { temp[position] = RGBA32(value, value, value, 255); });
        // temp.writePNG(string("c:/tmp/glyph_alpha_map.png"));

        glyphTexture = unique_ptr< GLTexture2D >(new GLTexture2D());
        glyphTexture->bind();

        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            alphaMap.getSize().x,
            alphaMap.getSize().y,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            alphaMap.getData().data()
        );

        glEnable(GL_TEXTURE_2D);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        const GLFloatVec2 pixelSizeInTexCoord(
            1.0f / static_cast< GLfloat >(glyphTextureSize.x),
            1.0f / static_cast< GLfloat >(glyphTextureSize.y)
        );

        const GLFloatVec2 glyphSizeInTexCoord(
            static_cast< GLfloat >(glyphPixelSizeOnTexture.x) / static_cast< GLfloat >(glyphTextureSize.x),
            static_cast< GLfloat >(glyphPixelSizeOnTexture.y) / static_cast< GLfloat >(glyphTextureSize.y)
        );

        // Populate glyph origo table.
        for (unsigned int page = 0; page < GLYPH_PAGE_COUNT; page++) {
            for (unsigned int y = 0; y < GLYPH_Y_COUNT_PER_PAGE; y++) {
                for (unsigned int x = 0; x < GLYPH_X_COUNT_PER_PAGE; x++) {
                    const GLFloatVec2 origo(static_cast< GLfloat >(x + page * GLYPH_X_COUNT_PER_PAGE), static_cast< GLfloat >(y));
                    glyphOrigoList[x + y * GLYPH_X_COUNT_PER_PAGE + page * GLYPH_COUNT_PER_PAGE] = pixelSizeInTexCoord + glyphSizeInTexCoord * origo;
                }
            }
        }

        glyphSpanOnTexture = GLFloatVec2(
            static_cast< GLfloat >(glyphPixelSize.x) / static_cast< GLfloat >(glyphTextureSize.x),
            static_cast< GLfloat >(glyphPixelSize.y) / static_cast< GLfloat >(glyphTextureSize.y)
        );
    }

    void GlyphSet::buildTileData(const Surface& surface) {
        Field2< uint8_t > alphaMap;
        alphaMap.resize(tileTextureSize);

        Surface buffer;
        buffer.resize(tilePixelSizeOnTexture);
        const unsigned int tileYDisplacementInPixels = tilePixelSize.y / 2;

        for (unsigned int y = 0; y < GLYPH_Y_COUNT; y++) {
            for (unsigned int x = 0; x < GLYPH_X_COUNT; x++) {
                for (unsigned int displacement = 0; displacement < TILE_DISPLACEMENT_COUNT; displacement++) {
                    const Int2 sPos(x * glyphPixelSize.x, y * glyphPixelSize.y + (TILE_DISPLACEMENT_COUNT - 1 - displacement) * tileYDisplacementInPixels);
                    const Int2 dPos(x * tilePixelSizeOnTexture.x, (y * TILE_DISPLACEMENT_COUNT + displacement) * tilePixelSizeOnTexture.y);

                    PixelUtil::copyAndExtendedEdges(buffer, surface, Int2(1, 1), IntRect(sPos.x, sPos.y, tilePixelSize.x, tilePixelSize.y));
                    readGlyphToTexture(alphaMap, buffer, dPos, IntRect(0, 0, buffer.getSize().x, buffer.getSize().y));
                }
            }
        }

        // DEBUG
        // Surface temp(alphaMap.getSize());
        // alphaMap.loop([&](const uint8_t value, const Int2& position) { temp[position] = RGBA32(value, value, value, 255); });
        // temp.writePNG(string("c:/tmp/tile_alpha_map.png"));

        tileTexture = unique_ptr< GLTexture2D >(new GLTexture2D());
        tileTexture->bind();

        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            alphaMap.getSize().x,
            alphaMap.getSize().y,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            alphaMap.getData().data()
        );

        glEnable(GL_TEXTURE_2D);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        const GLFloatVec2 pixelSizeInTexCoord(
            1.0f / static_cast< GLfloat >(tileTextureSize.x),
            1.0f / static_cast< GLfloat >(tileTextureSize.y)
        );

        const GLFloatVec2 tileEntrySizeInTexCoord(
            static_cast< GLfloat >(tilePixelSizeOnTexture.x)                           / static_cast< GLfloat >(tileTextureSize.x),
            static_cast< GLfloat >(tilePixelSizeOnTexture.y * TILE_DISPLACEMENT_COUNT) / static_cast< GLfloat >(tileTextureSize.y)
        );

        // Populate tile origo table.
        for (unsigned int page = 0; page < GLYPH_PAGE_COUNT; page++) {
            for (unsigned int y = 0; y < GLYPH_Y_COUNT_PER_PAGE; y++) {
                for (unsigned int x = 0; x < GLYPH_X_COUNT_PER_PAGE; x++) {
                    const GLFloatVec2 origo(static_cast< GLfloat >(x + page * GLYPH_X_COUNT_PER_PAGE), static_cast< GLfloat >(y));
                    tileOrigoList[x + y * GLYPH_X_COUNT_PER_PAGE + page * GLYPH_COUNT_PER_PAGE] = pixelSizeInTexCoord + tileEntrySizeInTexCoord * origo;
                }
            }
        }

        const unsigned int ROTATION_COUNT = 4;
        const array< Transformations::Rotation, ROTATION_COUNT > rotationList = {
            Transformations::Rotation::None, Transformations::Rotation::CW90, Transformations::Rotation::CW180, Transformations::Rotation::CW270
        };

        // Populate tile configuration list with normalized coordinates.
        for (unsigned int displacement = 0; displacement < TILE_DISPLACEMENT_COUNT; displacement++) {
            const GLFloatVec2 subOrigo = GLFloatVec2(0.0f, static_cast< GLfloat >(displacement));
            const GLFloatVec2 center   = subOrigo + GLFloatVec2(0.5f, 0.5f);

            for (unsigned int rotation = 0; rotation < ROTATION_COUNT; rotation++) {
                tileSubOrigoList[rotation + 0              + displacement * TILE_ORIENTATION_COUNT] = Transformations::RotateAndFlip(subOrigo, center, rotationList[rotation], Transformations::Direction::Normal);
                tileSubOrigoList[rotation + ROTATION_COUNT + displacement * TILE_ORIENTATION_COUNT] = Transformations::RotateAndFlip(subOrigo, center, rotationList[rotation], Transformations::Direction::MirrorY);
            }
        }

        const GLFloatVec2 tileSizeOnTextureInTexCoord(
            static_cast< GLfloat >(tilePixelSizeOnTexture.x) / static_cast< GLfloat >(tileTextureSize.x),
            static_cast< GLfloat >(tilePixelSizeOnTexture.y) / static_cast< GLfloat >(tileTextureSize.y)
        );

        // Transform tile configuration list into texture space.
        for (GLFloatVec2& subOrigo : tileSubOrigoList) subOrigo *= tileSizeOnTextureInTexCoord;

        // Populate tile texture axis lists with normalized coordinates.
        for (unsigned int rotation = 0; rotation < ROTATION_COUNT; rotation++) {
            tileUAxisList[rotation + 0]              = Transformations::RotateAndFlip(GLFloatVec2(1.0f, 0.0f), GLFloatVec2(0.0f, 0.0f), rotationList[rotation], Transformations::Direction::Normal);
            tileVAxisList[rotation + 0]              = Transformations::RotateAndFlip(GLFloatVec2(0.0f, 1.0f), GLFloatVec2(0.0f, 0.0f), rotationList[rotation], Transformations::Direction::Normal);
            tileUAxisList[rotation + ROTATION_COUNT] = Transformations::RotateAndFlip(GLFloatVec2(1.0f, 0.0f), GLFloatVec2(0.0f, 0.0f), rotationList[rotation], Transformations::Direction::MirrorY);
            tileVAxisList[rotation + ROTATION_COUNT] = Transformations::RotateAndFlip(GLFloatVec2(0.0f, 1.0f), GLFloatVec2(0.0f, 0.0f), rotationList[rotation], Transformations::Direction::MirrorY);
        }

        const GLFloatVec2 tileSpanOnTexture(
            static_cast< GLfloat >(tilePixelSize.x) / static_cast< GLfloat >(tileTextureSize.x),
            static_cast< GLfloat >(tilePixelSize.y) / static_cast< GLfloat >(tileTextureSize.y)
        );

        // Transform texture axis lists into texture space.
        for (GLFloatVec2& uAxis : tileUAxisList) uAxis *= tileSpanOnTexture;
        for (GLFloatVec2& vAxis : tileVAxisList) vAxis *= tileSpanOnTexture;
    }

    void GlyphSet::readGlyphToTexture(Field2< uint8_t >& texture, const Surface& source, const Int2& where, const IntRect& area) const {
        for (int y = 0; y < area.sizeY; y++) {
            for (int x = 0; x < area.sizeX; x++) {
                const Int2 pos(x, y);
                texture[where + Int2(x, y)] = source[Int2(area.posX, area.posY) + Int2(x, area.sizeY - 1 - y)].r;
            }
        }
    }
};


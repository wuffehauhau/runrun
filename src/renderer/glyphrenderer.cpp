/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphrenderer.cpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

#include <cassert>

#include "ruukku/mesh/indexedprimitivelist.hpp"
#include "glyphrenderer.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    GlyphRenderer::GlyphRenderer(const GlyphShader* shader, const GlyphSet* set) :
        bufferIndex(0),
        glyphCount(0),
        shader(shader), set(set),
        isActive(false)
    {
        vector< GLushort > indexData;

        // Generate static index data for the index buffers.
        for (unsigned int i = 0; i < BATCH_SIZE; i++) {
            indexData.push_back(static_cast< GLushort >(4 * i + 0));
            indexData.push_back(static_cast< GLushort >(4 * i + 1));
            indexData.push_back(static_cast< GLushort >(4 * i + 2));
            indexData.push_back(static_cast< GLushort >(4 * i + 2));
            indexData.push_back(static_cast< GLushort >(4 * i + 3));
            indexData.push_back(static_cast< GLushort >(4 * i + 0));
        }

        for (unsigned int i = 0; i < BUFFER_COUNT; i++) {
            vertexArrayList[i].bind();

            vertexBufferList[i] = unique_ptr< IndexedVertexBuffer >(new IndexedVertexBuffer(shader->getVertexBufferInfo(), GL_UNSIGNED_SHORT));
            vertexBufferList[i]->bindBuffer();
            vertexBufferList[i]->bindIndexBuffer();

            // Use shader properties to setup the vertex buffer.
            shader->getVertexBufferInfo().setAttributePointers();
            shader->getVertexBufferInfo().enableAttributes();

            vertexBufferList[i]->writeIndexData(indexData);
        }
    }

    const GlyphShader* GlyphRenderer::getShader() const {
        return shader;
    }

    void GlyphRenderer::begin(
        const GLFloatMat4& projection,
        const GLFloatMat4& modelView
    ) {
        assert(!isActive);
        isActive = true;

        shader->getProgram()->use();
        shader->setPositionMatrix(projection * modelView);

        glEnable(GL_TEXTURE_2D);
        set->getGlyphSheet()->bind();

        glActiveTexture(GL_TEXTURE0);
        shader->setTextureSampler(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void GlyphRenderer::end() {
        assert(isActive);
        isActive = false;

        drawCurrentBuffer();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }

    void GlyphRenderer::drawGlyph(const GlyphRenderInfo& info, const GLFloatVec2& position) {
        assert(isActive);

        const GLFloatVec2 pos00 = info.pos00 + position;
        const GLFloatVec2 pos10 = info.pos10 + position;
        const GLFloatVec2 pos11 = info.pos11 + position;
        const GLFloatVec2 pos01 = info.pos01 + position;

        const GLFloatVec2 glyphOrigo = set->getGlyphOrigo(info.glyphIndex);

        const GLFloatVec2 texUV00 = GLFloatVec2(glyphOrigo.x,                                  glyphOrigo.y);
        const GLFloatVec2 texUV10 = GLFloatVec2(glyphOrigo.x + set->getGlyphSpanOnTexture().x, glyphOrigo.y);
        const GLFloatVec2 texUV11 = GLFloatVec2(glyphOrigo.x + set->getGlyphSpanOnTexture().x, glyphOrigo.y + set->getGlyphSpanOnTexture().y);
        const GLFloatVec2 texUV01 = GLFloatVec2(glyphOrigo.x,                                  glyphOrigo.y + set->getGlyphSpanOnTexture().y);

        // Probably the most efficient "simple" way of doing this.
        packVertexToCache(pos00, texUV00, info.color);
        packVertexToCache(pos10, texUV10, info.color);
        packVertexToCache(pos11, texUV11, info.color);
        packVertexToCache(pos01, texUV01, info.color);

        glyphCount++;

        // Draw the glyphs if we've collected enough of them.
        if (glyphCount >= BATCH_SIZE) {
            drawCurrentBuffer();
        }
    }

    void GlyphRenderer::drawCurrentBuffer() {
        if (glyphCount == 0) return;

        // Dump cache into current vertex buffer.
        vertexBufferList[bufferIndex]->writeVertexData(vertexCacheList[bufferIndex], GL_DYNAMIC_DRAW);
        vertexCacheList[bufferIndex].clear();

        const int verticesPerGlyph = 4;
        const int indicesPerGlyph  = 6;

        IndexedPrimitiveList list(PrimitiveList(0, glyphCount * verticesPerGlyph - 1, GL_TRIANGLES), 0, glyphCount * indicesPerGlyph - 1);
        glyphCount = 0;

        vertexArrayList[bufferIndex].bind();
        IndexedPrimitiveList::drawElements(list, GL_UNSIGNED_SHORT);

        bufferIndex++;
        if (bufferIndex >= BUFFER_COUNT) {
            bufferIndex = 0;
        }
    }

    void GlyphRenderer::packVertexToCache(
        const GLFloatVec2& pos,
        const GLFloatVec2& texUV,
        const GLFloatRGBA& color
    ) {
        vertexCacheList[bufferIndex].push_back(pos.x);
        vertexCacheList[bufferIndex].push_back(pos.y);
        vertexCacheList[bufferIndex].push_back(texUV.x);
        vertexCacheList[bufferIndex].push_back(texUV.y);
        vertexCacheList[bufferIndex].push_back(color.r);
        vertexCacheList[bufferIndex].push_back(color.g);
        vertexCacheList[bufferIndex].push_back(color.b);
        vertexCacheList[bufferIndex].push_back(color.a);
    }
};


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilerenderer.cpp
 * Created: 2014-06-06
 * Authors: Jani Salo
 */

#include <cassert>

#include "ruukku/mesh/indexedprimitivelist.hpp"
#include "metrics/mapmetrics.hpp"
#include "tilerenderer.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    TileRenderer::TileRenderer(const TileShader* shader, const GlyphSet* set) :
        shader(shader), set(set),
        indexBufferLayerByteSize(6 * sizeof(GLushort) * MapMetrics::CELL_AREA),
        staticBufferLayerByteSize(4 * shader->getStaticBufferInfo().getByteStride() * MapMetrics::CELL_AREA),
        dynamicBufferByteSize(4 * shader->getDynamicBufferInfo().getByteStride() * MapMetrics::CELL_AREA),
        staticBufferIndex(0), dynamicBufferIndex(0),
        isActive(false)
    {
        if (sizeof(TileDynamicRenderInfo) != shader->getDynamicBufferInfo().getByteStride()) {
            throw logic_error(string("TileDynamicRenderInfo bytesize doesn't match buffer stride."));
        }
    }

    const TileShader* TileRenderer::getShader() const {
        return shader;
    }

    TileRenderBuffer* TileRenderer::createTileRenderBuffer(const GLFloatMat3& tf) {
        vector< GLfloat > positionData;

        for (unsigned int y = 0; y < MapMetrics::CELL_DIM; y++) {
            for (unsigned int x = 0; x < MapMetrics::CELL_DIM; x++) {
                const GLfloat fx = static_cast< GLfloat >(x);
                const GLfloat fy = static_cast< GLfloat >(y);

                const GLFloatVec2 pa = tf.transform(GLFloatVec2(fx + 0.0, fy + 0.0));
                const GLFloatVec2 pb = tf.transform(GLFloatVec2(fx + 1.0, fy + 0.0));
                const GLFloatVec2 pc = tf.transform(GLFloatVec2(fx + 1.0, fy + 1.0));
                const GLFloatVec2 pd = tf.transform(GLFloatVec2(fx + 0.0, fy + 1.0));

                positionData.push_back(pa.x);
                positionData.push_back(pa.y);
                positionData.push_back(pb.x);
                positionData.push_back(pb.y);
                positionData.push_back(pc.x);
                positionData.push_back(pc.y);
                positionData.push_back(pd.x);
                positionData.push_back(pd.y);
            }
        }

        array< GLVertexArray*, TileStaticRenderData::LAYER_COUNT > vertexArrayList;
        array< IndexedPrimitiveList, TileStaticRenderData::LAYER_COUNT > renderInfoList;
        for (unsigned int i = 0; i < TileStaticRenderData::LAYER_COUNT; i++) {
            vertexArrayList[i] = nullptr;
            renderInfoList[i] = IndexedPrimitiveList(PrimitiveList(0, -1, GL_TRIANGLES), 0, -1);
        }

        IndexedVertexBuffer* positionBuffer = nullptr;
        VertexBuffer* staticBuffer  = nullptr;
        VertexBuffer* dynamicBuffer = nullptr;

        TileRenderBuffer* tileRenderBuffer = nullptr;

        try {
            positionBuffer = new IndexedVertexBuffer(shader->getPositionBufferInfo(), GL_UNSIGNED_SHORT);
            staticBuffer  = new VertexBuffer(shader->getStaticBufferInfo());
            dynamicBuffer = new VertexBuffer(shader->getDynamicBufferInfo());

            for (unsigned int i = 0; i < TileStaticRenderData::LAYER_COUNT; i++) {
                vertexArrayList[i] = new GLVertexArray();
                vertexArrayList[i]->bind();

                positionBuffer->bindBuffer();
                positionBuffer->bindIndexBuffer();
                shader->getPositionBufferInfo().setAttributePointers();
                shader->getPositionBufferInfo().enableAttributes();

                staticBuffer->bindBuffer();
                shader->getStaticBufferInfo().setAttributePointers(static_cast< size_t >(i) * staticBufferLayerByteSize);
                shader->getStaticBufferInfo().enableAttributes();

                dynamicBuffer->bindBuffer();
                shader->getDynamicBufferInfo().setAttributePointers();
                shader->getDynamicBufferInfo().enableAttributes();
            }

            positionBuffer->writeVertexData(positionData);
            positionBuffer->resizeIndexBuffer(TileStaticRenderData::LAYER_COUNT * indexBufferLayerByteSize, GL_STATIC_DRAW);
            staticBuffer->resizeBuffer(TileStaticRenderData::LAYER_COUNT * staticBufferLayerByteSize, GL_STATIC_DRAW);
            dynamicBuffer->resizeBuffer(dynamicBufferByteSize, GL_STATIC_DRAW);

            tileRenderBuffer = new TileRenderBuffer(renderInfoList, vertexArrayList, positionBuffer, staticBuffer, dynamicBuffer);
        }
        catch (exception& e) {
            delete tileRenderBuffer;
            for (GLVertexArray* array : vertexArrayList) delete array;

            delete dynamicBuffer;
            delete staticBuffer;
            delete positionBuffer;
            throw;
        }

        return tileRenderBuffer;
    }

    void TileRenderer::updateTileRenderBufferDynamicData(TileRenderBuffer* buffer, const TileDynamicRenderData& data) {
        dynamicDataUploadBufferArray[dynamicBufferIndex].clear();

        // Kind of extra ugly, but it works.
        for (const TileDynamicRenderInfo& info : data.array().data) {
            dynamicDataUploadBufferArray[dynamicBufferIndex].push_back(info);
            dynamicDataUploadBufferArray[dynamicBufferIndex].push_back(info);
            dynamicDataUploadBufferArray[dynamicBufferIndex].push_back(info);
            dynamicDataUploadBufferArray[dynamicBufferIndex].push_back(info);
        }

        // The constructor for this class checks that it's ok to do this.
        buffer->dynamicBuffer->writeVertexData(dynamicDataUploadBufferArray[dynamicBufferIndex], GL_DYNAMIC_DRAW);

        dynamicBufferIndex++;
        if (dynamicBufferIndex >= BUFFER_COUNT) dynamicBufferIndex = 0;
    }

    void TileRenderer::updateTileRenderBufferStaticData(TileRenderBuffer* buffer, const TileStaticRenderData& data, const TileStaticRenderData::Layer layer) {
        staticDataUploadBufferArray[staticBufferIndex].clear();
        indexDataUploadBufferArray[staticBufferIndex].clear();


        int indexCount = 0;
        data.array(layer).loopElements([&](const TileStaticRenderInfo& info, const Int2& pos) {
            if (info.tileInfo.glyphIndex != 0) {
                const GLFloatVec2 baseUV = set->getTileOrigo(info.tileInfo);
                const GLFloatVec2 uAxis  = set->getTileUAxisSpan(info.tileInfo);
                const GLFloatVec2 vAxis  = set->getTileVAxisSpan(info.tileInfo);

                packVertexToStaticDataUploadBuffer(baseUV,                 info.colorFront, info.colorBack);
                packVertexToStaticDataUploadBuffer(baseUV + uAxis,         info.colorFront, info.colorBack);
                packVertexToStaticDataUploadBuffer(baseUV + uAxis + vAxis, info.colorFront, info.colorBack);
                packVertexToStaticDataUploadBuffer(baseUV +         vAxis, info.colorFront, info.colorBack);

                const GLushort tileMapBaseIndex = 4 * static_cast< GLushort >(pos.x + pos.y * MapMetrics::CELL_DIM);

                indexDataUploadBufferArray[staticBufferIndex].push_back(tileMapBaseIndex + 0);
                indexDataUploadBufferArray[staticBufferIndex].push_back(tileMapBaseIndex + 1);
                indexDataUploadBufferArray[staticBufferIndex].push_back(tileMapBaseIndex + 2);
                indexDataUploadBufferArray[staticBufferIndex].push_back(tileMapBaseIndex + 2);
                indexDataUploadBufferArray[staticBufferIndex].push_back(tileMapBaseIndex + 3);
                indexDataUploadBufferArray[staticBufferIndex].push_back(tileMapBaseIndex + 0);

                indexCount += 6;
            }
            else {
                for (int i = 0; i < 4; i++) {
                    packVertexToStaticDataUploadBuffer(GLFloatVec2(0.0f, 0.0f), GLFloatRGBA(0.0f, 0.0f, 0.0f, 0.0f), GLFloatRGBA(0.0f, 0.0f, 0.0f, 0.0f));
                }
            }
        });

        const GLsizeiptr staticBufferByteOffset = static_cast< unsigned int >(layer) * staticBufferLayerByteSize;
        const GLsizeiptr indexBufferByteOffset = static_cast< unsigned int >(layer) * indexBufferLayerByteSize;

        // Necessary, since GL_ELEMENT_ARRAY_BUFFER is saved by VAO.
        glBindVertexArray(0);

        buffer->staticBuffer->writeVertexSubData(staticDataUploadBufferArray[staticBufferIndex], staticBufferByteOffset);
        buffer->positionBuffer->writeIndexSubData(indexDataUploadBufferArray[staticBufferIndex], indexBufferByteOffset);

        const int indexOffset = static_cast< unsigned int >(layer) * 6 * MapMetrics::CELL_AREA;
        const int vertexCount = 4 * MapMetrics::CELL_AREA;

        buffer->renderInfoList[static_cast< unsigned int >(layer)] = IndexedPrimitiveList(PrimitiveList(0, vertexCount - 1, GL_TRIANGLES), indexOffset, indexOffset + indexCount - 1);

        staticBufferIndex++;
        if (staticBufferIndex >= BUFFER_COUNT) staticBufferIndex = 0;
    }

    void TileRenderer::begin(
        const GLFloatMat4& projection,
        const GLFloatMat4& modelView
    ) {
        assert(!isActive);
        isActive = true;

        shader->getProgram()->use();
        shader->setPositionMatrix(projection * modelView);

        glEnable(GL_TEXTURE_2D);
        set->getTileSheet()->bind();

        glActiveTexture(GL_TEXTURE0);
        shader->setTextureSampler(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void TileRenderer::end() {
        assert(isActive);
        isActive = false;

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }

    void TileRenderer::renderTiles(const TileRenderBuffer* renderBuffer, const TileStaticRenderData::Layer layer) const {
        if (renderBuffer->renderInfoList[static_cast< unsigned int >(layer)].getIndexCount() == 0) return;
        renderBuffer->vertexArrayList[static_cast< unsigned int >(layer)]->bind();
        IndexedPrimitiveList::drawElements(renderBuffer->renderInfoList[static_cast< unsigned int >(layer)], GL_UNSIGNED_SHORT);
    }

    void TileRenderer::packVertexToStaticDataUploadBuffer(
        const GLFloatVec2& texUV,
        const GLFloatRGBA& colorFront,
        const GLFloatRGBA& colorBack
    ) {
        staticDataUploadBufferArray[staticBufferIndex].push_back(texUV.x);
        staticDataUploadBufferArray[staticBufferIndex].push_back(texUV.y);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorFront.r);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorFront.g);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorFront.b);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorFront.a);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorBack.r);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorBack.g);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorBack.b);
        staticDataUploadBufferArray[staticBufferIndex].push_back(colorBack.a);
    }
};


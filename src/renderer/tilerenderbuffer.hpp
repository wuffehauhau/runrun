/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilerenderbuffer.hpp
 * Created: 2014-06-08
 * Authors: Jani Salo
 */

/*
 * Stores vertex buffers and a vertex array for rendering a square of tiles.
 */

#ifndef RUNRUN_TILERENDERBUFFER_HPP
#define RUNRUN_TILERENDERBUFFER_HPP

#include <array>
#include <memory>

#include "ruukku/mesh/indexedprimitivelist.hpp"
#include "ruukku/mesh/indexedvertexbuffer.hpp"
#include "ruukku/mesh/vertexbuffer.hpp"
#include "ruukku/misc/uncopyable.hpp"
#include "ruukku/opengl/glvertexarray.hpp"

#include "glyph/tilestaticrenderdata.hpp"

namespace runrun {
    class TileRenderBuffer : public ruukku::Uncopyable {
        friend class TileRenderer;

        private:
            std::array< ruukku::IndexedPrimitiveList, TileStaticRenderData::LAYER_COUNT > renderInfoList;
            std::array< std::unique_ptr< ruukku::GLVertexArray >, TileStaticRenderData::LAYER_COUNT > vertexArrayList;

            std::unique_ptr< ruukku::IndexedVertexBuffer > positionBuffer;
            std::unique_ptr< ruukku::VertexBuffer > staticBuffer;
            std::unique_ptr< ruukku::VertexBuffer > dynamicBuffer;

            TileRenderBuffer(
                const std::array< ruukku::IndexedPrimitiveList, TileStaticRenderData::LAYER_COUNT >& renderInfoList,
                const std::array< ruukku::GLVertexArray*, TileStaticRenderData::LAYER_COUNT >& vertexArrayList,
                ruukku::IndexedVertexBuffer* positionBuffer,
                ruukku::VertexBuffer* staticBuffer,
                ruukku::VertexBuffer* dynamicBuffer
            );
    };

    inline TileRenderBuffer::TileRenderBuffer(
        const std::array< ruukku::IndexedPrimitiveList, TileStaticRenderData::LAYER_COUNT >& renderInfoList,
        const std::array< ruukku::GLVertexArray*, TileStaticRenderData::LAYER_COUNT >& vertexArrayList,
        ruukku::IndexedVertexBuffer* positionBuffer,
        ruukku::VertexBuffer* staticBuffer,
        ruukku::VertexBuffer* dynamicBuffer
    ) :
        renderInfoList(renderInfoList),
        positionBuffer(positionBuffer),
        staticBuffer(staticBuffer),
        dynamicBuffer(dynamicBuffer)
    {
        for (unsigned int i = 0; i < TileStaticRenderData::LAYER_COUNT; i++) {
            this->vertexArrayList[i] = std::unique_ptr< ruukku::GLVertexArray >(vertexArrayList[i]);
        }
    }
};

#endif /* RUNRUN_TILERENDERBUFFER_HPP */


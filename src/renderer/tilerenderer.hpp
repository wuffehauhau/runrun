/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tilerenderer.hpp
 * Created: 2014-06-06
 * Authors: Jani Salo
 */

/*
 * The renderer used for rendering game tiles.
 */

#ifndef RUNRUN_TILERENDERER_HPP
#define RUNRUN_TILERENDERER_HPP

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "ruukku/misc/uncopyable.hpp"

#include "glyph/glyphset.hpp"
#include "glyph/tiledynamicrenderdata.hpp"
#include "glyph/tilestaticrenderdata.hpp"
#include "shader/tileshader.hpp"
#include "tilerenderbuffer.hpp"

namespace runrun {
    class TileRenderer : public ruukku::Uncopyable {
        public:
            TileRenderer(const TileShader* shader, const GlyphSet* set);

            const TileShader* getShader() const;

            TileRenderBuffer* createTileRenderBuffer(const ruukku::GLFloatMat3& tf);

            void updateTileRenderBufferDynamicData (TileRenderBuffer* buffer, const TileDynamicRenderData& data);
            void updateTileRenderBufferStaticData  (TileRenderBuffer* buffer, const TileStaticRenderData&  data, const TileStaticRenderData::Layer layer);

            void begin(
                const ruukku::GLFloatMat4& projection,
                const ruukku::GLFloatMat4& modelView
            );

            void end();

            void renderTiles(const TileRenderBuffer* renderBuffer, const TileStaticRenderData::Layer layer) const;

        private:
            static const unsigned int BUFFER_COUNT = 2;

            const TileShader* shader;
            const GlyphSet*   set;

            const GLsizeiptr indexBufferLayerByteSize;
            const GLsizeiptr staticBufferLayerByteSize;
            const GLsizeiptr dynamicBufferByteSize;

            unsigned int staticBufferIndex;
            unsigned int dynamicBufferIndex;

            bool isActive;

            std::array< std::vector< GLushort              >, BUFFER_COUNT > indexDataUploadBufferArray;
            std::array< std::vector< GLfloat               >, BUFFER_COUNT > staticDataUploadBufferArray;
            std::array< std::vector< TileDynamicRenderInfo >, BUFFER_COUNT > dynamicDataUploadBufferArray;

            void packVertexToStaticDataUploadBuffer(
                const ruukku::GLFloatVec2& texUV,
                const ruukku::GLFloatRGBA& colorFront,
                const ruukku::GLFloatRGBA& colorBack
            );
    };
};

#endif /* RUNRUN_TILERENDERER_HPP */


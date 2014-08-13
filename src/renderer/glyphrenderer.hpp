/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphrenderer.hpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

/*
 * The renderer used for rendering glyph sprites.
 */

#ifndef RUNRUN_GLYPHRENDERER_HPP
#define RUNRUN_GLYPHRENDERER_HPP

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "ruukku/mesh/indexedvertexbuffer.hpp"
#include "ruukku/misc/uncopyable.hpp"
#include "ruukku/opengl/glvertexarray.hpp"

#include "glyph/glyphset.hpp"
#include "glyph/glyphrenderinfo.hpp"
#include "shader/glyphshader.hpp"

namespace runrun {
    class GlyphRenderer : public ruukku::Uncopyable {
        public:
            GlyphRenderer(const GlyphShader* shader, const GlyphSet* set);

            const GlyphShader* getShader() const;

            // Makes changes to the OpenGL state to enable rendering:
            // - Binds the glyph shader to current shader and initializes it.
            // - Binds the texture from current glyph set to slot 0.
            // - Enables 2D texturing.
            // - Enables blending and sets the blend function.
            void begin(
                const ruukku::GLFloatMat4& projection,
                const ruukku::GLFloatMat4& modelView
            );

            // Sends any remaining glyphs in the render queue for drawing.
            // Changes made to the OpenGL state:
            // - Disables blending.
            // - Disables 2D texturing.
            void end();

            // Adds a glyph to the render queue.
            // Should only be called between begin and end.
            void drawGlyph(const GlyphRenderInfo& info, const ruukku::GLFloatVec2& position);

        private:
            // Batch size should be kept small enough to keep
            // the vertex data indexable with unsigned short integers.
            static const unsigned int BATCH_SIZE = 128;
            static const unsigned int BUFFER_COUNT = 2;

            unsigned int bufferIndex;
            unsigned int glyphCount;

            std::array< std::vector< GLfloat >,                           BUFFER_COUNT > vertexCacheList;
            std::array< ruukku::GLVertexArray,                            BUFFER_COUNT > vertexArrayList;
            std::array< std::unique_ptr < ruukku::IndexedVertexBuffer  >, BUFFER_COUNT > vertexBufferList;

            const GlyphShader* shader;
            const GlyphSet*    set;

            // Used for assertions.
            bool isActive;

            void drawCurrentBuffer();
            void packVertexToCache(
                const ruukku::GLFloatVec2& pos,
                const ruukku::GLFloatVec2& texUV,
                const ruukku::GLFloatRGBA& color
            );
    };
};

#endif /* RUNRUN_GLYPHRENDERER_HPP */


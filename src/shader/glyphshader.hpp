/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphshader.hpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

/*
 * The shader used for rendering glyph sprites.
 */

#ifndef RUNRUN_GLYPHSHADER_HPP
#define RUNRUN_GLYPHSHADER_HPP

#include <string>
#include <vector>

#include "ruukku/opengl/gltypes.hpp"
#include "ruukku/mesh/vertexbuffer.hpp"
#include "ruukku/mesh/shaderprogram.hpp"
#include "ruukku/mesh/vertexbufferinfo.hpp"
#include "ruukku/mesh/vertexarrayinfo.hpp"

namespace runrun {
    class GlyphShader : public ruukku::ShaderProgram {
        public:
            GlyphShader(
                const ruukku::GLVertexShader&   vertexShader,
                const ruukku::GLFragmentShader& fragmentShader
            );

            void setPositionMatrix(const ruukku::GLFloatMat4& m) const;
            void setTextureSampler(const GLuint index)           const;

            static std::vector< std::string > getOutputNameList();
            static ruukku::VertexBufferInfo getVertexBufferInfo();
            static ruukku::VertexArrayInfo getVertexArrayInfo();

        private:
            GLuint posMatrix;
            GLuint texSampler;
    };

    inline void GlyphShader::setPositionMatrix(const ruukku::GLFloatMat4& m) const { glUniformMatrix4fv(posMatrix, 1, false, m.getData()); }
    inline void GlyphShader::setTextureSampler(const GLuint index)           const { glUniform1i(texSampler, index); }
};

#endif /* RUNRUN_GLYPHSHADER_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tileshader.hpp
 * Created: 2014-06-06
 * Authors: Jani Salo
 */

/*
 * The shader used for rendering game tiles.
 */

#ifndef RUNRUN_TILESHADER_HPP
#define RUNRUN_TILESHADER_HPP

#include <string>
#include <vector>

#include "ruukku/opengl/gltypes.hpp"
#include "ruukku/mesh/vertexbuffer.hpp"
#include "ruukku/mesh/shaderprogram.hpp"
#include "ruukku/mesh/vertexbufferinfo.hpp"
#include "ruukku/mesh/vertexarrayinfo.hpp"

namespace runrun {
    class TileShader : public ruukku::ShaderProgram {
        public:
            TileShader(
                const ruukku::GLVertexShader&   vertexShader,
                const ruukku::GLFragmentShader& fragmentShader
            );

            void setPositionMatrix(const ruukku::GLFloatMat4& m) const;
            void setTextureSampler(const GLuint index)           const;

            static std::vector< std::string > getOutputNameList();
            static ruukku::VertexBufferInfo getPositionBufferInfo();
            static ruukku::VertexBufferInfo getDynamicBufferInfo();
            static ruukku::VertexBufferInfo getStaticBufferInfo();
            static ruukku::VertexArrayInfo getVertexArrayInfo();

        private:
            GLuint posMatrix;
            GLuint texSampler;
    };

    inline void TileShader::setPositionMatrix(const ruukku::GLFloatMat4& m) const { glUniformMatrix4fv(posMatrix, 1, false, m.getData()); }
    inline void TileShader::setTextureSampler(const GLuint index)           const { glUniform1i(texSampler, index); }
};

#endif /* RUNRUN_TILESHADER_HPP */


/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    shaderprogram.hpp
 * Created: 2013-02-04
 * Authors: Jani Salo
 */

/*
 * A non-abstract base class for shader programs.
 */

#ifndef RUUKKU_SHADERPROGRAM_HPP
#define RUUKKU_SHADERPROGRAM_HPP

#include <string>

#include "../misc/uncopyable.hpp"
#include "../opengl/glvertexshader.hpp"
#include "../opengl/glfragmentshader.hpp"
#include "../opengl/glprogram.hpp"

#include "vertexarrayinfo.hpp"

namespace ruukku {
    class ShaderProgram : public Uncopyable {
        public:
            ShaderProgram(
                const GLVertexShader&             vertexShader,
                const GLFragmentShader&           fragmentShader,
                const VertexArrayInfo&            vertexArrayInfo,
                const std::vector< std::string >& outputNameList
            );

            virtual ~ShaderProgram();

        public:
            const GLProgram*       getProgram()     const { return program_; }
            const VertexArrayInfo& getArrayFormat() const { return vertexArrayInfo_; }

        public:
            // This method is only for statically fetching the
            // uniform names and shouldn't be relied to be very fast.
            GLuint getUniformLocation(const std::string& name) const { return program_->getUniformLocation(name); }

        private:
            GLProgram*      program_;
            VertexArrayInfo vertexArrayInfo_;
    };
};

#endif /* RUUKKU_SHADERPROGRAM_HPP */


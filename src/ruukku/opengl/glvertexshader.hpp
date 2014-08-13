/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glvertexshader.hpp
 * Created: 2012-08-16
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL vertex shader.
 */

#ifndef RUUKKU_GLVERTEXSHADER_HPP
#define RUUKKU_GLVERTEXSHADER_HPP

#include "glshader.hpp"

namespace ruukku {
    class GLVertexShader : public GLShader {
        public:
            GLVertexShader() : GLShader(GL_VERTEX_SHADER) {}
            virtual ~GLVertexShader() {}
    };
};

#endif /* RUUKKU_GLVERTEXSHADER_HPP */


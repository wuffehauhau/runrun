/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glfragmentshader.hpp
 * Created: 2012-08-16
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL fragment shader.
 */

#ifndef RUUKKU_GLFRAGMENTSHADER_HPP
#define RUUKKU_GLFRAGMENTSHADER_HPP

#include "glshader.hpp"

namespace ruukku {
    class GLFragmentShader : public GLShader  {
        public:
            GLFragmentShader() : GLShader(GL_FRAGMENT_SHADER) {}
            virtual ~GLFragmentShader() {}
    };
};

#endif /* RUUKKU_GLFRAGMENTSHADER_HPP */


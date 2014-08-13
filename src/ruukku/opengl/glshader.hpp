/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glshader.hpp
 * Created: 2012-08-10
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL shader object.
 */

#ifndef RUUKKU_GLSHADER_HPP
#define RUUKKU_GLSHADER_HPP

#include <iostream>
#include <string>

#include "glresource.hpp"

namespace ruukku {
    class GLShader : public GLResource {
        public:
            GLShader(const GLuint type);
            virtual ~GLShader();

        public:
            GLint getType() const;

            bool isVertexShader()   const { return (getType() == GL_VERTEX_SHADER);   }
            bool isFragmentShader() const { return (getType() == GL_FRAGMENT_SHADER); }

        public:
            void compile()    const;
            bool isCompiled() const;

            std::string getInfoLog() const;

        public:
            void setSourceFromString(const std::string& source) const;
            void setSourceFromStream(std::istream& is)          const;
            void setSourceFromFile(const std::string& filename) const;
    };
};

#endif /* RUUKKU_GLSHADER_HPP */


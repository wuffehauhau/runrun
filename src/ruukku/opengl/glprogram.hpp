/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glprogram.hpp
 * Created: 2012-08-10
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL program object.
 */

#ifndef RUUKKU_GLPROGRAM_HPP
#define RUUKKU_GLPROGRAM_HPP

#include <string>
#include <vector>

#include "glresource.hpp"
#include "glshader.hpp"

namespace ruukku {
    class GLProgram : public GLResource {
        public:
             GLProgram();
            ~GLProgram();

        public:
            void use() const { glUseProgram(getID()); }

        public:
            GLuint getUniformLocation   (const std::string& name) const;
            GLuint getAttributeLocation (const std::string& name) const;

        public:
            void bindAttributeLocation    (const std::string& name, const GLuint index) const;
            void bindFragmentDataLocation (const std::string& name, const GLuint index) const;

        public:
            void link()     const;
            bool isLinked() const;

            std::string getInfoLog() const;

        public:
            void attachShader(const GLuint    shader) const;
            void attachShader(const GLShader& shader) const { attachShader(getID()); }

            void detachShader(const GLuint    shader) const;
            void detachShader(const GLShader& shader) const { detachShader(getID()); }

            void detachAllShaders() const;

            std::vector< GLuint > getShaderList() const;
    };
};

#endif /* RUUKKU_GLPROGRAM_HPP */


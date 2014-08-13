/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltypetraits.hpp
 * Created: 2013-01-24
 * Authors: Jani Salo
 */

/*
 * A traits class for common OpenGL types.
 */

#ifndef RUUKKU_GLTYPETRAITS_HPP
#define RUUKKU_GLTYPETRAITS_HPP

#include <GL/glew.h>

namespace ruukku {
    template < typename T >
    class GLTypeTraits {
        public:
            static const GLenum ENUM = GL_NONE;
            static const int    SIZE = 0;
    };

    template <>
    class GLTypeTraits< GLbyte > {
        public:
            static const GLenum ENUM = GL_BYTE;
            static const int    SIZE = sizeof(GLbyte);
    };

    template <>
    class GLTypeTraits< GLubyte > {
        public:
            static const GLenum ENUM = GL_UNSIGNED_BYTE;
            static const int    SIZE = sizeof(GLubyte);
    };

    template <>
    class GLTypeTraits< GLshort > {
        public:
            static const GLenum ENUM = GL_SHORT;
            static const int    SIZE = sizeof(GLshort);
    };

    template <>
    class GLTypeTraits< GLushort > {
        public:
            static const GLenum ENUM = GL_UNSIGNED_SHORT;
            static const int    SIZE = sizeof(GLushort);
    };

    template <>
    class GLTypeTraits< GLint > {
        public:
            static const GLenum ENUM = GL_INT;
            static const int    SIZE = sizeof(GLint);
    };

    template <>
    class GLTypeTraits< GLuint > {
        public:
            static const GLenum ENUM = GL_UNSIGNED_INT;
            static const int    SIZE = sizeof(GLuint);
    };

    template <>
    class GLTypeTraits< GLfloat > {
        public:
            static const GLenum ENUM = GL_FLOAT;
            static const int    SIZE = sizeof(GLfloat);
    };

    template <>
    class GLTypeTraits< GLdouble > {
        public:
            static const GLenum ENUM = GL_DOUBLE;
            static const int    SIZE = sizeof(GLdouble);
    };
};

#endif /* RUUKKU_GLTYPETRAITS_HPP */


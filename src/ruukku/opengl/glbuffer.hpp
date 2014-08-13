/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glbuffer.hpp
 * Created: 2012-12-10
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL buffer object.
 */

#ifndef RUUKKU_GLBUFFER_HPP
#define RUUKKU_GLBUFFER_HPP

#include <vector>
#include "glresource.hpp"

namespace ruukku {
    class GLBuffer : public GLResource {
        public:
                     GLBuffer();
            virtual ~GLBuffer();

        public:
            virtual GLenum getType() const = 0;

        public:
            void bind()   const { glBindBuffer(getType(), getID()); }
            void unbind() const { glBindBuffer(getType(), 0);       }

        public:
            template < typename T >
            void writeData(const T* data, const std::size_t n, const GLenum usage = GL_STATIC_DRAW) const;

            template < typename T >
            void writeSubData(const T* data, const std::size_t n, const GLintptr offset) const;
    };

    template < typename T >
    void GLBuffer::writeData(const T* data, const std::size_t n, const GLenum usage) const {
        bind();
        glBufferData(
            getType(),
            sizeof(T) * n,
            data,
            usage
        );
    }

    template < typename T >
    void GLBuffer::writeSubData(const T* data, const std::size_t n, const GLintptr offset) const {
        bind();
        glBufferSubData(
            getType(),
            offset,
            sizeof(T) * n,
            data
        );
    }
};

#endif /* RUUKKU_GLBUFFER_HPP */


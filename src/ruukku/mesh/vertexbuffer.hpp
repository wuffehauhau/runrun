/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexbuffer.hpp
 * Created: 2013-02-09
 * Authors: Jani Salo
 */

/*
 * A class for buffering vertex data.
 */

#ifndef RUUKKU_VERTEXBUFFER_HPP
#define RUUKKU_VERTEXBUFFER_HPP

#include <GL/glew.h>
#include <cassert>
#include <memory>

#include "../misc/uncopyable.hpp"
#include "../opengl/glarraybuffer.hpp"

#include "vertexbufferinfo.hpp"

namespace ruukku {
    class VertexBuffer : public Uncopyable {
        public:
            VertexBuffer(const VertexBufferInfo& bufferInfo);
            virtual ~VertexBuffer() {}

        public:
            const VertexBufferInfo& getBufferInfo()     const { return bufferInfo_; }
            const GLArrayBuffer*    getBuffer()         const { return buffer_.get(); }
            const size_t            getBufferByteSize() const { return bufferSize_; }

        public:
            void resizeBuffer(const GLsizeiptr byteSize, const GLenum usage = GL_STATIC_DRAW);

            template < typename T >
            void writeVertexData(const std::vector< T >& data, const GLenum usage = GL_STATIC_DRAW);

            template < typename T >
            void writeVertexData(const T* data, const std::size_t n, const GLenum usage = GL_STATIC_DRAW);

            template < typename T >
            void writeVertexSubData(const std::vector< T >& data, const GLsizeiptr byteOffset);

            template < typename T >
            void writeVertexSubData(const T* data, const std::size_t n, const GLsizeiptr byteOffset);

        public:
            void bindBuffer() const { buffer_->bind(); }

        private:
            VertexBufferInfo bufferInfo_;
            std::unique_ptr< GLArrayBuffer > buffer_;

        private:
            size_t bufferSize_;
    };

    template < typename T >
    void VertexBuffer::writeVertexData(const std::vector< T >& data, const GLenum usage) {
        writeVertexData(data.data(), data.size(), usage);
    }

    template < typename T >
    void VertexBuffer::writeVertexData(const T* data, const std::size_t n, const GLenum usage) {
        if (bufferSize_ >= n * sizeof(T)) {
            buffer_->writeSubData(data, n, 0);
        }
        else {
            bufferSize_ = n * sizeof(T);
            buffer_->writeData(data, n, usage);
        }
    }

    template < typename T >
    void VertexBuffer::writeVertexSubData(const std::vector< T >& data, const GLsizeiptr byteOffset) {
        writeVertexSubData(data.data(), data.size(), byteOffset);
    }

    template < typename T >
    void VertexBuffer::writeVertexSubData(const T* data, const std::size_t n, const GLsizeiptr byteOffset) {
        assert(n + byteOffset <= bufferSize_);
        buffer_->writeSubData(data, n, byteOffset);
    }
};

#endif /* RUUKKU_VERTEXBUFFER_HPP */


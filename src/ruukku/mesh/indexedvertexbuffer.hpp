/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    indexedvertexbuffer.hpp
 * Created: 2013-02-15
 * Authors: Jani Salo
 */

/*
 * A class for buffering vertex and index data.
 */

#ifndef RUUKKU_INDEXEDVERTEXBUFFER_HPP
#define RUUKKU_INDEXEDVERTEXBUFFER_HPP

#include <GL/glew.h>
#include <cassert>
#include <memory>

#include "../opengl/glelementarraybuffer.hpp"

#include "vertexbuffer.hpp"

namespace ruukku {
    class IndexedVertexBuffer : public VertexBuffer {
        public:
            IndexedVertexBuffer(const VertexBufferInfo& bufferInfo, const GLenum indexType);
            virtual ~IndexedVertexBuffer() {}

        public:
            const GLenum                getIndexType()           const { return indexType_; }
            const GLElementArrayBuffer* getindexBuffer()         const { return indexBuffer_.get(); }
            const size_t                getIndexBufferByteSize() const { return indexBufferSize_; }

        public:
            void bindIndexBuffer() const { indexBuffer_->bind(); }

        public:
            void resizeIndexBuffer(const GLsizeiptr byteSize, const GLenum usage = GL_STATIC_DRAW);

            template < typename T >
            void writeIndexData(const std::vector< T >& data, const GLenum usage = GL_STATIC_DRAW);

            template < typename T >
            void writeIndexData(const T* data, const std::size_t n, const GLenum usage = GL_STATIC_DRAW);

            template < typename T >
            void writeIndexSubData(const std::vector< T >& data, const GLsizeiptr byteOffset);

            template < typename T >
            void writeIndexSubData(const T* data, const std::size_t n, const GLsizeiptr byteOffset);

        private:
            GLenum indexType_;
            std::unique_ptr< GLElementArrayBuffer > indexBuffer_;

        private:
            size_t indexBufferSize_;

    };

    template < typename T >
    void IndexedVertexBuffer::writeIndexData(const std::vector< T >& data, const GLenum usage) {
        writeIndexData(data.data(), data.size(), usage);
    }

    template < typename T >
    void IndexedVertexBuffer::writeIndexData(const T* data, const std::size_t n, const GLenum usage) {
        if (indexBufferSize_ >= n * sizeof(T)) {
            indexBuffer_->writeSubData(data, n, 0);
        }
        else {
            indexBufferSize_ = n * sizeof(T);
            indexBuffer_->writeData(data, n, usage);
        }
    }

    template < typename T >
    void IndexedVertexBuffer::writeIndexSubData(const std::vector< T >& data, const GLsizeiptr byteOffset) {
        writeIndexSubData(data.data(), data.size(), byteOffset);
    }

    template < typename T >
    void IndexedVertexBuffer::writeIndexSubData(const T* data, const std::size_t n, const GLsizeiptr byteOffset) {
        assert(n + byteOffset <= indexBufferSize_);
        indexBuffer_->writeSubData(data, n, byteOffset);
    }
};

#endif /* RUUKKU_INDEXEDVERTEXBUFFER_HPP */


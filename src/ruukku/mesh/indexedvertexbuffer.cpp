/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    indexedvertexbuffer.cpp
 * Created: 2013-02-15
 * Authors: Jani Salo
 */

#include "indexedvertexbuffer.hpp"

using namespace std;

namespace ruukku {
    IndexedVertexBuffer::IndexedVertexBuffer(const VertexBufferInfo& bufferInfo, const GLenum indexType) :
        VertexBuffer(bufferInfo), indexType_(indexType), indexBufferSize_(0)
    {
        indexBuffer_ = unique_ptr< GLElementArrayBuffer >(new GLElementArrayBuffer());
    }

    void IndexedVertexBuffer::resizeIndexBuffer(const GLsizeiptr byteSize, const GLenum usage) {
        indexBufferSize_ = byteSize;
        bindIndexBuffer();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, nullptr, usage);
    }
};


/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexbuffer.cpp
 * Created: 2013-02-09
 * Authors: Jani Salo
 */

#include "vertexbuffer.hpp"

using namespace std;

namespace ruukku {
    VertexBuffer::VertexBuffer(const VertexBufferInfo& bufferInfo) : bufferInfo_(bufferInfo), bufferSize_(0) {
        buffer_ = unique_ptr< GLArrayBuffer >(new GLArrayBuffer());
    }

    void VertexBuffer::resizeBuffer(const GLsizeiptr byteSize, const GLenum usage) {
        bufferSize_ = byteSize;
        bindBuffer();

        glBufferData(GL_ARRAY_BUFFER, byteSize, nullptr, usage);
    }
};


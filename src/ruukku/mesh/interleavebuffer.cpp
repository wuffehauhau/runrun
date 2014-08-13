/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    interleavebuffer.cpp
 * Created: 2013-02-02
 * Authors: Jani Salo
 */

#include "interleavebuffer.hpp"

namespace ruukku {
    void InterleaveBuffer::setVertexCount(const size_t count) {
        vertexCount_ = count;
        buffer_.resize(bufferInfo_.getByteStride() * vertexCount_);
    }
};


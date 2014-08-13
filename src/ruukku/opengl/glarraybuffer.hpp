/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glarraybuffer.hpp
 * Created: 2013-01-19
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL buffer intended as an array buffer.
 */

#ifndef RUUKKU_GLARRAYBUFFER_HPP
#define RUUKKU_GLARRAYBUFFER_HPP

#include "glbuffer.hpp"

namespace ruukku {
    class GLArrayBuffer : public GLBuffer {
        public:
            virtual ~GLArrayBuffer() {}

        public:
            GLenum getType() const { return GL_ARRAY_BUFFER; }
    };
};

#endif /* RUUKKU_GLARRAYBUFFER_HPP */


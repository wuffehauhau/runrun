/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glelementarraybuffer.hpp
 * Created: 2013-01-19
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL buffer intended as an element array buffer.
 */

#ifndef RUUKKU_GLELEMENTARRAYBUFFER_HPP
#define RUUKKU_GLELEMENTARRAYBUFFER_HPP

#include "glbuffer.hpp"

namespace ruukku {
    class GLElementArrayBuffer : public GLBuffer {
        public:
            virtual ~GLElementArrayBuffer() {}

        public:
            GLenum getType() const { return GL_ELEMENT_ARRAY_BUFFER; }
    };
};

#endif /* RUUKKU_GLELEMENTARRAYBUFFER_HPP */


/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glvertexarray.hpp
 * Created: 2013-02-07
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL vertex array object.
 */

#ifndef RUUKKU_GLVERTEXARRAY_HPP
#define RUUKKU_GLVERTEXARRAY_HPP

#include "glresource.hpp"

namespace ruukku {
    class GLVertexArray : public GLResource {
        public:
                     GLVertexArray();
            virtual ~GLVertexArray();

        public:
            void bind()   const { glBindVertexArray(getID()); }
            void unbind() const { glBindVertexArray(0);       }
    };
};

#endif /* RUUKKU_GLVERTEXARRAY_HPP */


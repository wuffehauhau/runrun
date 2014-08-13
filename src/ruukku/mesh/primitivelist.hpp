/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    primitivelist.hpp
 * Created: 2013-02-14
 * Authors: Jani Salo
 */

/*
 * A container for listing a range of primitives in vertex data.
 */

#ifndef RUUKKU_PRIMITIVELIST_HPP
#define RUUKKU_PRIMITIVELIST_HPP

#include <GL/glew.h>
#include <cstdint>

namespace ruukku {
    class PrimitiveList {
        public:
            PrimitiveList() {}
            PrimitiveList(
                const int firstVertex,
                const int lastVertex,
                const GLenum type
            ) :
                firstVertex_ (firstVertex),
                lastVertex_  (lastVertex),
                type_        (type)
            {}

        public:
            int getFirstVertex() const { return firstVertex_; }
            int getLastVertex()  const { return lastVertex_;  }

            int getVertexCount() const { return lastVertex_ - firstVertex_ + 1; }

        public:
            GLenum getType() const { return type_; }

        public:
            // Simple call to OpenGL API.
            static void drawArrays(const PrimitiveList& list);

            // NOTE Removed for compatibility with OpenGL 3.1
            // static void drawArraysInstanced(const PrimitiveList& list, const std::size_t count);

        private:
            int firstVertex_;
            int lastVertex_;

            GLenum type_;
    };
};

#endif /* RUUKKU_PRIMITIVELIST_HPP */


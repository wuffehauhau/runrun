/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    indexedprimitivelist.hpp
 * Created: 2013-02-02
 * Authors: Jani Salo
 */

/*
 * A container for listing a range of primitives in indexed vertex data.
 */

#ifndef RUUKKU_INDEXEDPRIMITIVELIST_HPP
#define RUUKKU_INDEXEDPRIMITIVELIST_HPP

#include <GL/glew.h>

#include "primitivelist.hpp"

namespace ruukku {
    class IndexedPrimitiveList : public PrimitiveList {
        public:
            IndexedPrimitiveList() {}
            IndexedPrimitiveList(
                const PrimitiveList& list,
                const int firstIndex,
                const int lastIndex
            ) :
                PrimitiveList (list),
                firstIndex_   (firstIndex),
                lastIndex_    (lastIndex)
            {}

        public:
            int getFirstIndex() const { return firstIndex_; }
            int getLastIndex()  const { return lastIndex_;  }

            int getIndexCount() const { return lastIndex_ - firstIndex_ + 1; }

        public:
            // Simple call to OpenGL API.
            static void drawElements(const IndexedPrimitiveList& list, const GLenum type);

            // NOTE Removed for compatibility with OpenGL 3.1
            // static void drawElementsInstanced (const IndexedPrimitiveList& list, const GLenum type, const std::size_t count);

        private:
            int firstIndex_;
            int lastIndex_;
    };
};

#endif /* RUUKKU_INDEXEDPRIMITIVELIST_HPP */


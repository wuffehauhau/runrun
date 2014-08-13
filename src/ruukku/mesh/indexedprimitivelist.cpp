/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    indexedprimitivelist.cpp
 * Created: 2014-01-11
 * Authors: Jani Salo
 */

#include "../opengl/glutil.hpp"

#include "indexedprimitivelist.hpp"

namespace ruukku {
    void IndexedPrimitiveList::drawElements(const IndexedPrimitiveList& list, const GLenum type) {
        glDrawRangeElements(
            list.getType(),
            list.getFirstVertex(),
            list.getLastVertex(),
            list.getIndexCount(),
            type,
            reinterpret_cast< void* >(static_cast< size_t >(GLUtil::getByteSizefromEnum(type) * list.getFirstIndex()))
        );
    }

    /*
    void IndexedPrimitiveList::drawElementsInstanced(const IndexedPrimitiveList& list, const GLenum type, const size_t count) {
        glDrawElementsInstanced(
            list.getType(),
            list.getIndexCount(),
            type,
            reinterpret_cast< void* >(static_cast< size_t >(GLUtil::getByteSizefromEnum(type) * list.getFirstIndex())),
            count
        );
    }
    */
};


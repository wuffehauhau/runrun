/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    primitivelist.cpp
 * Created: 2014-01-11
 * Authors: Jani Salo
 */

#include "primitivelist.hpp"

namespace ruukku {
    void PrimitiveList::drawArrays(const PrimitiveList& list) {
        glDrawArrays(list.getType(), list.getFirstVertex(), list.getVertexCount());
    }

    /*
    void PrimitiveList::drawArraysInstanced(const PrimitiveList& list, const size_t count) {
        glDrawArraysInstanced(list.getType(), list.getFirstVertex(), list.getVertexCount(), count);
    }
    */
};


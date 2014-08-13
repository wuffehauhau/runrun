/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexarrayinfo.hpp
 * Created: 2013-02-09
 * Authors: Jani Salo
 */

/*
 * A container for vertex array properties.
 */

#ifndef RUUKKU_VERTEXARRAYINFO_HPP
#define RUUKKU_VERTEXARRAYINFO_HPP

#include <initializer_list>
#include <functional>
#include <vector>

#include "vertexbufferinfo.hpp"

namespace ruukku {
    class VertexArrayInfo {
        public:
            VertexArrayInfo(std::initializer_list < VertexBufferInfo > list) : bufferInfoList_(list) {}
            VertexArrayInfo(const std::vector< VertexBufferInfo >&     list) : bufferInfoList_(list) {}

        public:
            const std::vector< VertexBufferInfo >& getBufferInfoList()  const { return bufferInfoList_; }

        public:
            std::size_t             getBufferCount()                       const { return bufferInfoList_.size(); }
            const VertexBufferInfo& getBufferInfo(const std::size_t index) const { return bufferInfoList_[index]; }

        public:
            bool operator ==(const VertexArrayInfo& info) const;
            bool operator !=(const VertexArrayInfo& info) const { return !(*this == info); }

        private:
            std::vector< VertexBufferInfo > bufferInfoList_;
    };
};

#endif /* RUUKKU_VERTEXARRAYINFO_HPP */


/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexbufferinfo.hpp
 * Created: 2013-02-02
 * Authors: Jani Salo
 */

/*
 * A container for vertex buffer properties.
 */

#ifndef RUUKKU_VERTEXBUFFERINFO_HPP
#define RUUKKU_VERTEXBUFFERINFO_HPP

#include <initializer_list>
#include <functional>
#include <vector>

#include "vertexattributeinfo.hpp"

namespace ruukku {
    class VertexBufferInfo {
        public:
            VertexBufferInfo(std::initializer_list < VertexAttributeInfo > list, const std::size_t byteAlignment = 4) : attributeInfoList_(list) { build(byteAlignment); }
            VertexBufferInfo(const std::vector< VertexAttributeInfo >&     list, const std::size_t byteAlignment = 4) : attributeInfoList_(list) { build(byteAlignment); }

        public:
            const std::vector< VertexAttributeInfo >& getAttributeInfoList()       const { return attributeInfoList_; }
            const std::vector< std::size_t >&         getAttributeByteOffsetList() const { return attributeByteOffsetList_; }

        public:
            std::size_t getAttributeCount() const { return attributeInfoList_.size(); }

            const VertexAttributeInfo& getAttributeInfo       (const std::size_t index) const { return attributeInfoList_[index]; }
            std::size_t                getAttributeByteOffset (const std::size_t index) const { return attributeByteOffsetList_[index]; }

        public:
            std::size_t getByteStride()  const { return byteStride_; }
            std::size_t getBytePadding() const { return bytePadding_; }

        public:
            void loopAttributes           (std::function< void (const VertexAttributeInfo& info) >                           func) const;
            void loopAttributesWithOffset (std::function< void (const VertexAttributeInfo& info, const std::size_t byteOffset ) > func) const;

        public:
            // Assumes an array buffer is bound to buffer target
            void setAttributePointers(const std::size_t bufferByteOffset = 0) const;

        public:
            void enableAttributes()  const;
            void disableAttributes() const;

        public:
            bool operator ==(const VertexBufferInfo& info) const;
            bool operator !=(const VertexBufferInfo& info) const { return !(*this == info); }

        private:
            void build(const std::size_t byteAlignment);

        private:
            std::vector< VertexAttributeInfo > attributeInfoList_;
            std::vector< std::size_t >         attributeByteOffsetList_;

            std::size_t byteStride_;
            std::size_t bytePadding_;
    };
};

#endif /* RUUKKU_VERTEXBUFFERINFO_HPP */


/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexbufferinfo.cpp
 * Created: 2013-02-02
 * Authors: Jani Salo
 */

#include "vertexbufferinfo.hpp"

using namespace std;

namespace ruukku {
    void VertexBufferInfo::build(const size_t byteAlignment) {
        byteStride_ = 0;

        // Compute attribute byte offsets and buffer stride.
        for (const VertexAttributeInfo& info : attributeInfoList_) {
            attributeByteOffsetList_.push_back(byteStride_);
            byteStride_ += info.getByteSize();
        }

        const size_t remainder = byteStride_ % byteAlignment;
        bytePadding_ = (byteAlignment - remainder) % byteAlignment;
        byteStride_ += bytePadding_;
    }

    void VertexBufferInfo::loopAttributes(function< void (const VertexAttributeInfo& info) > func) const {
        for (const VertexAttributeInfo& info : attributeInfoList_) func(info);
    }

    void VertexBufferInfo::loopAttributesWithOffset(function< void (const VertexAttributeInfo& info, const size_t byteOffset) > func) const {
        size_t index = 0;

        for (const VertexAttributeInfo& info : attributeInfoList_) {
            func(info, attributeByteOffsetList_.at(index++));
        }
    }

    void VertexBufferInfo::setAttributePointers(const size_t bufferByteOffset) const {
        loopAttributesWithOffset([&](const VertexAttributeInfo info, const size_t byteOffset)  {
            glVertexAttribPointer(
                info.getIndex(),
                info.getSize(),
                info.getType(),
                GL_FALSE,
                getByteStride(),
                reinterpret_cast< void* >(static_cast< size_t >(byteOffset) + bufferByteOffset)
            );
        });
    }

    void VertexBufferInfo::enableAttributes() const {
        loopAttributes([&](const VertexAttributeInfo info)  {
            glEnableVertexAttribArray(info.getIndex());
        });
    }

    void VertexBufferInfo::disableAttributes() const {
        loopAttributes([&](const VertexAttributeInfo info)  {
            glDisableVertexAttribArray(info.getIndex());
        });
    }

    bool VertexBufferInfo::operator ==(const VertexBufferInfo& info) const {
        if (byteStride_ != info.byteStride_) return false;
        if (bytePadding_ != info.bytePadding_) return false;

        if (attributeInfoList_.size() != info.attributeInfoList_.size()) return false;
        for (size_t i = 0; i < attributeInfoList_.size(); i ++) {
            if (attributeInfoList_[i] != info.attributeInfoList_[i]) return false;
        }

        if (attributeByteOffsetList_.size() != info.attributeByteOffsetList_.size()) return false;
        for (size_t i = 0; i < attributeByteOffsetList_.size(); i ++) {
            if (attributeByteOffsetList_[i] != info.attributeByteOffsetList_[i]) return false;
        }

        return true;
    }
};


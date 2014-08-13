/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexarrayinfo.cpp
 * Created: 2013-12-15
 * Authors: Jani Salo
 */

#include "vertexarrayinfo.hpp"

namespace ruukku {
    bool VertexArrayInfo::operator ==(const VertexArrayInfo& info) const {
        if (bufferInfoList_.size() != info.bufferInfoList_.size()) return false;
        for (size_t i = 0; i < bufferInfoList_.size(); i ++) {
            if (bufferInfoList_[i] != info.bufferInfoList_[i]) return false;
        }

        return true;
    }
};


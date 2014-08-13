/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframelist.hpp
 * Created: 2014-05-30
 * Authors: Jani Salo
 */

/*
 * An encapsulation of objects frames with meta information.
 */

#ifndef RUNRUN_OBJECTFRAMELIST_HPP
#define RUNRUN_OBJECTFRAMELIST_HPP

#include <string>
#include <vector>

#include "ruukku/opengl/gltypes.hpp"

#include "util/datafile.hpp"
#include "objectframe.hpp"

namespace runrun {
    class ObjectFrameList {
        public:
            ObjectFrameList();
            ObjectFrameList(const std::string& name, const std::vector< ObjectFrame >& frameList);

            const std::string& getName() const;
            const ObjectFrame& getFrame(const unsigned int time) const;

            // Looks for a frame list with given name in the stream.
            static ObjectFrameList constructFromDataFile(const std::string& name, const DataFile& data);

            ObjectFrameList getTransformed(const std::string& name, const ruukku::GLFloatMat3& tf) const;

        private:
            std::string name;
            std::vector< ObjectFrame > frameList;

            unsigned int totalLength;

            static ruukku::GLFloatVec2 readOrigo(DataFile::ConstListIt& it, const DataFile::ConstListIt& end);
            static ObjectFrame         readFrame(DataFile::ConstListIt& it, const DataFile::ConstListIt& end, const ruukku::GLFloatVec2& origo);

            static unsigned int readFrameLength(DataFile::ConstListIt& it, const DataFile::ConstListIt& end);
            static bool         readFrameGlyph (DataFile::ConstListIt& it, const DataFile::ConstListIt& end, const ruukku::GLFloatVec2& origo, GlyphRenderInfo& glyphInfoOut);
    };

    inline const std::string& ObjectFrameList::getName() const { return name; }
};

#endif /* RUNRUN_OBJECTFRAMELIST_HPP */


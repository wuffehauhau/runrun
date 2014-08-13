/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframelibrary.hpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

/*
 * A container for multiple object frame lists.
 */

#ifndef RUNRUN_OBJECTFRAMELIBRARY_HPP
#define RUNRUN_OBJECTFRAMELIBRARY_HPP

#include <string>
#include <vector>

#include "ruukku/misc/uncopyable.hpp"
#include "ruukku/opengl/gltypes.hpp"

#include "util/datafile.hpp"
#include "objectframelist.hpp"

namespace runrun {
    class ObjectFrameLibrary : public ruukku::Uncopyable {
        public:
            void  addFrameList  (const ObjectFrameList& frameList);
            void loadFrameLists (const std::vector< std::string >& nameList, const DataFile& data);

            void createCopy(
                const std::string& name,
                const std::string& copyName,
                const ruukku::GLFloatMat3& tf
            );

            const std::vector< ObjectFrameList >& getFrameListCollection() const;

            // Any collection indexes obtainable from the iterator are
            // guaranteed to remain valid over the lifetime of the object.
            std::vector< ObjectFrameList >::const_iterator findFrameList(const std::string& name) const;

        private:
            std::vector< ObjectFrameList > frameListCollection;
    };

    inline const std::vector< ObjectFrameList >& ObjectFrameLibrary::getFrameListCollection() const { return frameListCollection; }
};

#endif /* RUNRUN_OBJECTFRAMELIBRARY_HPP */


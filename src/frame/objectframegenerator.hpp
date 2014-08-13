/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframegenerator.hpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

/*
 * A class for generating object frame states from object actions.
 */

#ifndef RUNRUN_OBJECTFRAMEGENERATOR_HPP
#define RUNRUN_OBJECTFRAMEGENERATOR_HPP

#include <array>

#include "frame/objectframelibrary.hpp"
#include "objectframestate.hpp"
#include "objectframeevent.hpp"

namespace runrun {
    class ObjectFrameGenerator {
        public:
            static const unsigned int ACTION_ID_TABLE_SIZE = 1024;

            ObjectFrameGenerator(const ObjectFrameLibrary* library);

            void linkActionIDToFrameList(const unsigned int id, const std::string name);
            void generateFrames(const unsigned int currentFrame, const ObjectFrameEvent& event, ObjectFrameState& state) const;

       private:
           const ObjectFrameLibrary* library;
           std::vector< std::vector< std::size_t > > actionIDToFrameListIndexMap;
    };
};

#endif /* RUNRUN_OBJECTFRAMEGENERATOR_HPP */


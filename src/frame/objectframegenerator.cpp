/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframegenerator.cpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

#include <cassert>
#include <stdexcept>

#include "objectframegenerator.hpp"

using namespace std;

namespace runrun {
    ObjectFrameGenerator::ObjectFrameGenerator(const ObjectFrameLibrary* library) : library(library) {
        actionIDToFrameListIndexMap.resize(ACTION_ID_TABLE_SIZE);
        const unsigned int INITIAL_ENTRY_CAPACITY = 16;

        // Reserve space for all vectors in one pass in hopes of some cache locality.
        for (vector< size_t >& pointerList : actionIDToFrameListIndexMap) {
            pointerList.reserve(INITIAL_ENTRY_CAPACITY);
        }
    }

    void ObjectFrameGenerator::linkActionIDToFrameList(const unsigned int id, const std::string name) {
        if (id >= ACTION_ID_TABLE_SIZE) {
            throw logic_error("Object action ID out of range.");
        }

        const size_t index = library->findFrameList(name) - library->getFrameListCollection().cbegin();
        actionIDToFrameListIndexMap[id].push_back(index);
    }

    void ObjectFrameGenerator::generateFrames(const unsigned int currentFrame, const ObjectFrameEvent& event, ObjectFrameState& state) const {
        assert(event.id < ACTION_ID_TABLE_SIZE);

        const unsigned int frameDelta = currentFrame - event.startFrame;
        const std::vector< ObjectFrameList >& collection = library->getFrameListCollection();

        for (const size_t index : actionIDToFrameListIndexMap[event.id]) {
            state.getFrameList().push_back(&(collection[index].getFrame(frameDelta)));
        }
    }
};


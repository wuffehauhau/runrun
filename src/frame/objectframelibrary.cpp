/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframelibrary.cpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

#include <algorithm>

#include "objectframelibrary.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    void ObjectFrameLibrary::addFrameList(const ObjectFrameList& frameList) {
        if (findFrameList(frameList.getName()) != frameListCollection.cend()) {
            throw runtime_error(string("Duplicate object frame list: ") + frameList.getName());
        }

        frameListCollection.push_back(frameList);
    }

    void ObjectFrameLibrary::loadFrameLists(const vector< string >& nameList, const DataFile& data) {
        for (const string& name : nameList) {
            ObjectFrameList newFrameList = ObjectFrameList::constructFromDataFile(name, data);
            addFrameList(newFrameList);
        }
    }

    void ObjectFrameLibrary::createCopy(
        const string& name,
        const string& copyName,
        const GLFloatMat3& tf
    ) {
        vector< ObjectFrameList >::const_iterator original = findFrameList(name);
        if (original == frameListCollection.cend()) {
            throw runtime_error(string("Couldn't find object frame list: ") + name);
        }

        addFrameList(original->getTransformed(copyName, tf));
    }

    vector< ObjectFrameList >::const_iterator ObjectFrameLibrary::findFrameList(const string& name) const {
        return find_if(
            frameListCollection.cbegin(),
            frameListCollection.cend(),
            [&](const ObjectFrameList& list
        ) {
            if (list.getName() == name) {
                return true;
            } return false;
        });
    }
};


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    playeranimation.cpp
 * Created: 2014-06-13
 * Authors: Jani Salo
 */

#include "playeranimation.hpp"

using namespace std;

namespace runrun {
    PlayerAnimation::PlayerAnimation(const ObjectFrameLibrary* library) {
        frameGenerator = unique_ptr< ObjectFrameGenerator >(new ObjectFrameGenerator(library));

        frameGenerator->linkActionIDToFrameList(getIndex(Body::DefaultLeft),  string("body_idle_left"));
        frameGenerator->linkActionIDToFrameList(getIndex(Body::DefaultRight), string("body_idle_right"));

        frameGenerator->linkActionIDToFrameList(getIndex(Legs::IdleLeft),     string("legs_idle_left"));
        frameGenerator->linkActionIDToFrameList(getIndex(Legs::IdleRight),    string("legs_idle_right"));
        frameGenerator->linkActionIDToFrameList(getIndex(Legs::WalkLeft),     string("legs_walk_left"));
        frameGenerator->linkActionIDToFrameList(getIndex(Legs::WalkRight),    string("legs_walk_right"));

        frameGenerator->linkActionIDToFrameList(getIndex(Head::DefaultLeft),  string("head_idle_left"));
        frameGenerator->linkActionIDToFrameList(getIndex(Head::DefaultRight), string("head_idle_right"));

        frameGenerator->linkActionIDToFrameList(getIndex(Tail::DefaultLeft),  string("tail_idle_left"));
        frameGenerator->linkActionIDToFrameList(getIndex(Tail::DefaultRight), string("tail_idle_right"));
    }
};


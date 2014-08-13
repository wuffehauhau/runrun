/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframeevent.hpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

/*
 * Very simple container for frame event id and start frame.
 */

#ifndef RUNRUN_OBJECTFRAMEEVENT_HPP
#define RUNRUN_OBJECTFRAMEEVENT_HPP

namespace runrun {
    class ObjectFrameEvent {
        public:
            unsigned int id;
            unsigned int startFrame;

            ObjectFrameEvent() {}
            ObjectFrameEvent(const unsigned int id, const unsigned int startFrame) : id(id), startFrame(startFrame) {}
    };
};

#endif /* RUNRUN_OBJECTFRAMEEVENT_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframestate.hpp
 * Created: 2014-06-03
 * Authors: Jani Salo
 */

/*
 * A lightweight "wrapper" for passing current object frame state around.
 */

#ifndef RUNRUN_OBJECTFRAMESTATE_HPP
#define RUNRUN_OBJECTFRAMESTATE_HPP

#include <functional>

#include "frame/objectframe.hpp"

namespace runrun {
    class ObjectFrameState {
        public:
            ObjectFrameState() {}

        	void clear();

            const std::vector< const ObjectFrame* >& getFrameList() const;
                  std::vector< const ObjectFrame* >& getFrameList();

            void listGlyphs(std::function< void (const GlyphRenderInfo& info) > fn) const;

    	private:
        	std::vector< const ObjectFrame* > frameList;
    };

    inline void ObjectFrameState::clear() { frameList.clear(); }

    inline const std::vector< const ObjectFrame* >& ObjectFrameState::getFrameList() const { return frameList; }
    inline       std::vector< const ObjectFrame* >& ObjectFrameState::getFrameList()       { return frameList; }

    inline void ObjectFrameState::listGlyphs(std::function< void (const GlyphRenderInfo&)> fn ) const {
        for (const ObjectFrame* frame : frameList) {
            for (const GlyphRenderInfo& info : frame->getGlyphList()) {
                fn(info);
            }
        }
    }
};

#endif /* RUNRUN_OBJECTFRAMESTATE_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    collisionhullentry.hpp
 * Created: 2014-07-08
 * Authors: Jani Salo
 */

/*
 * A list of shapes associated with an identifier.
 */

#ifndef RUNRUN_COLLISIONHULLENTRY_HPP
#define RUNRUN_COLLISIONHULLENTRY_HPP

#include <vector>

#include "geometry/boundingbox.hpp"
#include "geometry/convexpolygon.hpp"

namespace runrun {
    class CollisionHullEntry {
        public:
            std::vector< ConvexPolygon > convexPolygonList;

            CollisionHullEntry()             : id(-1) {}
            CollisionHullEntry(const int id) : id(id) {}

            void computeBoundingBox();

            int         getID()          const;
            BoundingBox getBoundingBox() const;

        private:
            int         id;
            BoundingBox boundingBox;
    };

    inline void CollisionHullEntry::computeBoundingBox() {
        if (convexPolygonList.size() == 0) boundingBox = BoundingBox::createNull();
        else {
            boundingBox = convexPolygonList[0].getBoundingBox();
            for (std::size_t i = 1; i < convexPolygonList.size(); i++) {
                boundingBox += convexPolygonList[i].getBoundingBox();
            }
        }
    }

    inline int         CollisionHullEntry::getID() const { return id; }
    inline BoundingBox CollisionHullEntry::getBoundingBox() const { return boundingBox; }
};

#endif /* RUNRUN_COLLISIONHULLENTRY_HPP */


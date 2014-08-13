/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    pvec3.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a tightly packing three component projective vector.
 * The template paramater is assumed to be a floating point type.
 */

#ifndef RUUKKU_PVEC3_HPP
#define RUUKKU_PVEC3_HPP

#include "../config/packing.hpp"
#include "vec2.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    class PVec3 {
        public:
            T x, y, w;

        public:
            PVec3()                                                                           {}
            PVec3(const T x, const T y, const T w = static_cast< T >(1.0)) : x(x), y(y), w(w) {}

        public:
            bool operator ==(const PVec3& v) const { return (x == v.x) && (y == v.y) && (w == v.w); }
            bool operator !=(const PVec3& v) const { return (x != v.x) || (y != v.y) || (w != v.w); }

        public:
            Vec2< T > getVector()  const { return Vec2< T >(x, y); }
            Vec2< T > getProject() const { const T t = static_cast< T >(1.0) / w; return Vec2< T >(x, y).getScalar(t); }

        public:
            bool isNumeric() { return (x == x) && (y == y) && (w == w); }
    };

    typedef PVec3< float >  FloatPVec3;
    typedef PVec3< double > DoublePVec3;
};

#pragma pack(pop)

#endif /* RUUKKU_PVEC3_HPP */


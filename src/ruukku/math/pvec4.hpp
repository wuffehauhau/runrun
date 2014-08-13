/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    pvec4.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a tightly packing four component projective vector.
 * The template paramater is assumed to be a floating point type.
 */

#ifndef RUUKKU_PVEC4_HPP
#define RUUKKU_PVEC4_HPP

#include "../config/packing.hpp"
#include "vec3.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    class PVec4 {
        public:
            T x, y, z, w;

        public:
            PVec4()                                                                                            {}
            PVec4(const T x, const T y, const T z, const T w = static_cast< T >(1.0)) : x(x), y(y), z(z), w(w) {}

        public:
            bool operator ==(const PVec4& v) const { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
            bool operator !=(const PVec4& v) const { return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w); }

        public:
            Vec3< T > getVector()  const { return Vec3< T >(x, y, z); }
            Vec3< T > getProject() const { const T t = static_cast< T >(1.0) / w; return Vec3< T >(x, y, z).getScalar(t); }

        public:
            bool isNumeric() { return (x == x) && (y == y) && (z == z) && (w == w); }
    };

    typedef PVec4< float >  FloatPVec4;
    typedef PVec4< double > DoublePVec4;
};

#pragma pack(pop)

#endif /* RUUKKU_PVEC4_HPP */


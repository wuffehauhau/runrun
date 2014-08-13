/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    ivec3.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template for an integral three dimensional vector.
 */

#ifndef RUUKKU_IVEC3_HPP
#define RUUKKU_IVEC3_HPP

namespace ruukku {
    template < typename T >
    class IVec3 {
        public:
            T x, y, z;

        public:
            IVec3()                                                   {}
            IVec3(const T x, const T y, const T z) : x(x), y(y), z(z) {}

        public:
            bool operator ==(const IVec3& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
            bool operator !=(const IVec3& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

            IVec3 operator -() const { return IVec3(-x, -y, -z); }

            IVec3 operator +(const IVec3& v) const { return IVec3(x + v.x, y + v.y, z + v.z); }
            IVec3 operator -(const IVec3& v) const { return IVec3(x - v.x, y - v.y, z - v.z); }
            IVec3 operator *(const IVec3& v) const { return IVec3(x * v.x, y * v.y, z * v.z); }
            IVec3 operator *(const T&     t) const { return IVec3(x * t,   y * t,   z * t); }

            IVec3& operator +=(const IVec3& v) { *this = *this + v; return *this; }
            IVec3& operator -=(const IVec3& v) { *this = *this - v; return *this; }
            IVec3& operator *=(const IVec3& v) { *this = *this * v; return *this; }
            IVec3& operator *=(const T&     t) { *this = *this * t; return *this; }
    };

    template < typename T >
    IVec3< T > operator *(const T& t, const IVec3< T >& v) { return v * t; }

    typedef IVec3< int > Int3;
};

#endif /* RUUKKU_IVEC3_HPP */


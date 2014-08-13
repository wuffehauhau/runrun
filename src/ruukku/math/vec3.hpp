/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vec3.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a tightly packing three dimensional euclidean vector.
 * The template paramater is assumed to be a floating point type.
 */

#ifndef RUUKKU_VEC3_HPP
#define RUUKKU_VEC3_HPP

#include <cmath>
#include "../config/packing.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    struct Vec3 {
        public:
            T x, y, z;

        public:
            Vec3() {}
            Vec3(const T x, const T y, const T z) : x(x), y(y), z(z) {}

        public:
            bool operator ==(const Vec3& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
            bool operator !=(const Vec3& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

            Vec3 operator -() const { return Vec3(-x, -y, -z); }

            Vec3 operator +(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
            Vec3 operator -(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
            Vec3 operator *(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
            Vec3 operator *(const T&    t) const { return Vec3(x * t,   y * t,   z * t); }

            Vec3& operator +=(const Vec3& v) { *this = *this + v; return *this; }
            Vec3& operator -=(const Vec3& v) { *this = *this - v; return *this; }
            Vec3& operator *=(const Vec3& v) { *this = *this * v; return *this; }
            Vec3& operator *=(const T&    t) { *this = *this * t; return *this; }

        public:
            T    getDot   (const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
            Vec3 getCross (const Vec3& v) const;

            Vec3 getProjection(const Vec3& v) const { return (this->getDot(v) / v.getDot(v)) * v; }

            T    getLength() const { return std::sqrt(x * x + y * y + z * z); }
            Vec3 getNormal() const { return *this * (static_cast< T >(1.0) / (*this).getLength()); }

        public:
            bool isNumeric() { return (x == x) && (y == y) && (z == z); }
    };

    template < typename T >
    Vec3< T > operator *(const T& t, const Vec3< T >& v) { return v * t; }

    template < typename T >
    Vec3< T > Vec3< T >::getCross(const Vec3& v) const {
        return Vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    typedef Vec3< float >  FloatVec3;
    typedef Vec3< double > DoubleVec3;
};

#pragma pack(pop)

#endif /* RUUKKU_VEC3_HPP */


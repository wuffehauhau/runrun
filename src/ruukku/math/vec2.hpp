/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vec2.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a tightly packing two dimensional euclidean vector.
 * The template paramater is assumed to be a floating point type.
 */

#ifndef RUUKKU_VEC2_HPP
#define RUUKKU_VEC2_HPP

#include <cmath>
#include "../config/packing.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    struct Vec2 {
        public:
            T x, y;

        public:
            Vec2() {}
            Vec2(const T x, const T y) : x(x), y(y) {}

        public:
            bool operator ==(const Vec2& v) const { return (x == v.x) && (y == v.y); }
            bool operator !=(const Vec2& v) const { return (x != v.x) || (y != v.y); }

            Vec2 operator -() const { return Vec2(-x, -y); }

            Vec2 operator +(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
            Vec2 operator -(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
            Vec2 operator *(const Vec2& v) const { return Vec2(x * v.x, y * v.y); }
            Vec2 operator *(const T&    t) const { return Vec2(x * t,   y * t); }

            Vec2& operator +=(const Vec2& v) { *this = *this + v; return *this; }
            Vec2& operator -=(const Vec2& v) { *this = *this - v; return *this; }
            Vec2& operator *=(const Vec2& v) { *this = *this * v; return *this; }
            Vec2& operator *=(const T&    t) { *this = *this * t; return *this; }

        public:
            T    getDot   (const Vec2& v) const { return x * v.x + y * v.y; }
            T    getCross (const Vec2& v) const { return x * v.y - y * v.x; }

            Vec2 getProjection(const Vec2& v) const { return (this->getDot(v) / v.getDot(v)) * v; }

            T    getLength() const { return std::sqrt(x * x + y * y); }
            Vec2 getNormal() const { return *this * (static_cast< T >(1.0) / (*this).getLength()); }

        public:
            bool isNumeric() { return (x == x) && (y == y); }
    };

    template < typename T >
    Vec2< T > operator *(const T& t, const Vec2< T >& v) { return v * t; }

    typedef Vec2< float >  FloatVec2;
    typedef Vec2< double > DoubleVec2;
};

#pragma pack(pop)

#endif /* RUUKKU_VEC2_HPP */


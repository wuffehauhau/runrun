/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    ivec2.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template for an integral two dimensional vector.
 */

#ifndef RUUKKU_IVEC2_HPP
#define RUUKKU_IVEC2_HPP

namespace ruukku {
    template < typename T >
    class IVec2 {
        public:
            T x, y;

        public:
            IVec2()                                  {}
            IVec2(const T x, const T y) : x(x), y(y) {}

        public:
            bool operator ==(const IVec2& v) const { return (x == v.x) && (y == v.y); }
            bool operator !=(const IVec2& v) const { return (x != v.x) || (y != v.y); }

            IVec2 operator -() const { return IVec2(-x, -y); }

            IVec2 operator +(const IVec2& v) const { return IVec2(x + v.x, y + v.y); }
            IVec2 operator -(const IVec2& v) const { return IVec2(x - v.x, y - v.y); }
            IVec2 operator *(const IVec2& v) const { return IVec2(x * v.x, y * v.y); }
            IVec2 operator *(const T&     t) const { return IVec2(x * t,   y * t); }

            IVec2& operator +=(const IVec2& v) { *this = *this + v; return *this; }
            IVec2& operator -=(const IVec2& v) { *this = *this - v; return *this; }
            IVec2& operator *=(const IVec2& v) { *this = *this * v; return *this; }
            IVec2& operator *=(const T&     t) { *this = *this * t; return *this; }
     };

    template < typename T >
    IVec2< T > operator *(const T& t, const IVec2< T >& v) { return v * t; }

    typedef IVec2< int > Int2;
};

#endif /* RUUKKU_IVEC2_HPP */


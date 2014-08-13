/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    rgba.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a tightly packing rgba color element. The template
 * parameter is assumed to be a floating point type.
 */

#ifndef RUUKKU_RGBA_HPP
#define RUUKKU_RGBA_HPP

#include "../config/packing.hpp"
#include "rgb.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    class RGBA {
        public:
            T r, g, b, a;

        public:
            RGBA()                                                                    {}
            RGBA(const T r, const T g, const T b, const T a) : r(r), g(g), b(b), a(a) {}

        public:
            bool operator ==(const RGBA& c) const { return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a); }
            bool operator !=(const RGBA& c) const { return (r != c.r) || (g != c.g) || (b != c.b) || (a != c.a); }

            RGBA operator +(const RGBA& c) const { return RGBA(r + c.r, g + c.g, b + c.b, a + c.a); }
            RGBA operator -(const RGBA& c) const { return RGBA(r - c.r, g - c.g, b - c.b, a - c.a); }
            RGBA operator *(const RGBA& c) const { return RGBA(r * c.r, g * c.g, b * c.b, a * c.a); }
            RGBA operator *(const T     t) const { return RGBA(r * t,   g * t,   b * t,   a * t); }

            RGBA& operator +=(const RGBA& c) { *this = *this + c; return *this; }
            RGBA& operator -=(const RGBA& c) { *this = *this - c; return *this; }
            RGBA& operator *=(const RGBA& c) { *this = *this * c; return *this; }
            RGBA& operator *=(const T     t) { *this = *this * t; return *this; }

        public:
            RGB< T > getRGB     () const { return RGB< T >(r, g, b); }
            RGB< T > getFlatten () const { return getRGB() * a; }

            RGB< T > getBlend(const RGB< T >& rgb) const;
    };

    template < typename T >
    RGBA< T > operator *(const T t, const RGBA< T >& c) { return c * t; }

    template < typename T >
    RGB< T > RGBA< T >::getBlend(const RGB< T >& rgb) const {
        return RGB< T >(
            r * a + rgb.r * (static_cast< T >(1.0) - a),
            g * a + rgb.g * (static_cast< T >(1.0) - a),
            b * a + rgb.b * (static_cast< T >(1.0) - a)
        );
    }

    typedef RGBA< float  > FloatRGBA;
    typedef RGBA< double > DoubleRGBA;
};

#pragma pack(pop)

#endif /* RUUKKU_RGBA_HPP */


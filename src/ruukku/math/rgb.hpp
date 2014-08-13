/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    rgb.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a tightly packing rgb color element. The template
 * parameter is assumed to be a floating point type.
 */

#ifndef RUUKKU_RGB_HPP
#define RUUKKU_RGB_HPP

#include "../config/packing.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    class RGB {
        public:
            T r, g, b;

        public:
            RGB()                                                   {}
            RGB(const T r, const T g, const T b) : r(r), g(g), b(b) {}

        public:
            bool operator ==(const RGB& c) const { return (r == c.r) && (g == c.g) && (b == c.b); }
            bool operator !=(const RGB& c) const { return (r != c.r) || (g != c.g) || (b != c.b); }

            RGB operator +(const RGB& c) const { return RGB(r + c.r, g + c.g, b + c.b); }
            RGB operator -(const RGB& c) const { return RGB(r - c.r, g - c.g, b - c.b); }
            RGB operator *(const RGB& c) const { return RGB(r * c.r, g * c.g, b * c.b); }
            RGB operator *(const T    t) const { return RGB(r * t,   g * t,   b * t); }

            RGB& operator +=(const RGB& c) { *this = *this + c; return *this; }
            RGB& operator -=(const RGB& c) { *this = *this - c; return *this; }
            RGB& operator *=(const RGB& c) { *this = *this * c; return *this; }
            RGB& operator *=(const T    t) { *this = *this * t; return *this; }

        public:
            RGB getTrim() const;

            RGB getScale(T t) const { return RGB(t * r, t * g, t * b); }
    };

    template < typename T >
    RGB< T > operator *(const T t, const RGB< T >& c) { return c * t; }

    template < typename T >
    RGB< T > RGB< T >::getTrim() const {
        RGB c = *this;

        if      (c.r < static_cast< T >(0.0)) c.r = static_cast< T >(0.0);
        else if (c.r > static_cast< T >(1.0)) c.r = static_cast< T >(1.0);
        if      (c.g < static_cast< T >(0.0)) c.g = static_cast< T >(0.0);
        else if (c.g > static_cast< T >(1.0)) c.g = static_cast< T >(1.0);
        if      (c.b < static_cast< T >(0.0)) c.b = static_cast< T >(0.0);
        else if (c.b > static_cast< T >(1.0)) c.b = static_cast< T >(1.0);

        return c;
    }

    typedef RGB< float  > FloatRGB;
    typedef RGB< double > DoubleRGB;
};

#pragma pack(pop)

#endif /* RUUKKU_RGB_HPP */


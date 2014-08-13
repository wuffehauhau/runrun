/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    mat4.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template for a tightly packing 4x4 matrix. The template paramater is
 * assumed to be a floating point type.
 */

#ifndef RUUKKU_MAT4_HPP
#define RUUKKU_MAT4_HPP

#include <array>
#include <cmath>

#include "../config/packing.hpp"

#include "constants.hpp"
#include "pvec4.hpp"
#include "vec3.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    class Mat4 {
        public:
            Mat4() {}

            template < typename... E >
            Mat4(E... e) : e_{{e...}} {}

        public:
            const T& operator [](const int i) const { return e_[i]; }
                  T& operator [](const int i)       { return e_[i]; }

            const T* getData() const { return e_.data(); }
                  T* getData()       { return e_.data(); }

        public:
            bool operator ==(const Mat4& m) const;
            bool operator !=(const Mat4& m) const;

            Mat4 operator +(const Mat4& m) const;
            Mat4 operator -(const Mat4& m) const;
            Mat4 operator *(const Mat4& m) const;
            Mat4 operator *(const T     t) const;

            Mat4& operator +=(const Mat4& m) { *this = *this + m; return *this; }
            Mat4& operator -=(const Mat4& m) { *this = *this - m; return *this; }
            Mat4& operator *=(const Mat4& m) { *this = *this * m; return *this; }
            Mat4& operator *=(const T     t) { *this = *this * t; return *this; }

        public:
            T    getDeterminant() const;
            Mat4 getTranspose()   const;
            Mat4 getInverse()     const;

        public:
            void translate (const T x, const T y, const T z) { this->operator *=(getTranslation(x, y, z)); }
            void scale     (const T x, const T y, const T z) { this->operator *=(getScaling(x, y, z)); }

            void rotate(const T r, const T x, const T y, const T z) { this->operator *=(getRotation(r, x, y, z)); }

        public:
            PVec4< T > transform(const PVec4< T > v) const;
            Vec3< T >  transform(const Vec3 < T > v) const;

        public:
            bool isNumeric();

        public:
            static Mat4 getIdentity();

            static Mat4 getTranslation (const T x, const T y, const T z);
            static Mat4 getScaling     (const T x, const T y, const T z);
            static Mat4 getRotation    (const T r, const T x, const T y, const T z);

            static Mat4 getProjection      (const T fovY, const T aspectRatio, const T near, const T far);
            static Mat4 getOrthoProjection (const T left, const T right, const T bottom, const T top, const T near, const T far);

        public:
            static const int X0 = 0;
            static const int Y0 = 1;
            static const int Z0 = 2;
            static const int W0 = 3;

            static const int X1 = 4;
            static const int Y1 = 5;
            static const int Z1 = 6;
            static const int W1 = 7;

            static const int X2 = 8;
            static const int Y2 = 9;
            static const int Z2 = 10;
            static const int W2 = 11;

            static const int X3 = 12;
            static const int Y3 = 13;
            static const int Z3 = 14;
            static const int W3 = 15;

        private:
            std::array< T, 16 > e_;
    };

    template < typename T >
    bool Mat4< T >::operator ==(const Mat4& m) const {
        return (
            (e_[X0] == m.e_[X0]) && (e_[Y0] == m.e_[Y0]) && (e_[Z0] == m.e_[Z0]) && (e_[W0] == m.e_[W0]) &&
            (e_[X1] == m.e_[X1]) && (e_[Y1] == m.e_[Y1]) && (e_[Z1] == m.e_[Z1]) && (e_[W1] == m.e_[W1]) &&
            (e_[X2] == m.e_[X2]) && (e_[Y2] == m.e_[Y2]) && (e_[Z2] == m.e_[Z2]) && (e_[W2] == m.e_[W2]) &&
            (e_[X3] == m.e_[X3]) && (e_[Y3] == m.e_[Y3]) && (e_[Z3] == m.e_[Z3]) && (e_[W3] == m.e_[W3])
        );
    }

    template < typename T >
    bool Mat4< T >::operator !=(const Mat4& m) const {
        return (
            (e_[X0] != m.e_[X0]) || (e_[Y0] != m.e_[Y0]) || (e_[Z0] != m.e_[Z0]) || (e_[W0] != m.e_[W0]) ||
            (e_[X1] != m.e_[X1]) || (e_[Y1] != m.e_[Y1]) || (e_[Z1] != m.e_[Z1]) || (e_[W1] != m.e_[W1]) ||
            (e_[X2] != m.e_[X2]) || (e_[Y2] != m.e_[Y2]) || (e_[Z2] != m.e_[Z2]) || (e_[W2] != m.e_[W2]) ||
            (e_[X3] != m.e_[X3]) || (e_[Y3] != m.e_[Y3]) || (e_[Z3] != m.e_[Z3]) || (e_[W3] != m.e_[W3])
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::operator +(const Mat4& m) const {
        return Mat4(
            e_[X0] + m.e_[X0], e_[Y0] + m.e_[Y0], e_[Z0] + m.e_[Z0], e_[W0] + m.e_[W0],
            e_[X1] + m.e_[X1], e_[Y1] + m.e_[Y1], e_[Z1] + m.e_[Z1], e_[W1] + m.e_[W1],
            e_[X2] + m.e_[X2], e_[Y2] + m.e_[Y2], e_[Z2] + m.e_[Z2], e_[W2] + m.e_[W2],
            e_[X3] + m.e_[X3], e_[Y3] + m.e_[Y3], e_[Z3] + m.e_[Z3], e_[W3] + m.e_[W3]
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::operator -(const Mat4& m) const {
         return Mat4(
            e_[X0] - m.e_[X0], e_[Y0] - m.e_[Y0], e_[Z0] - m.e_[Z0], e_[W0] - m.e_[W0],
            e_[X1] - m.e_[X1], e_[Y1] - m.e_[Y1], e_[Z1] - m.e_[Z1], e_[W1] - m.e_[W1],
            e_[X2] - m.e_[X2], e_[Y2] - m.e_[Y2], e_[Z2] - m.e_[Z2], e_[W2] - m.e_[W2],
            e_[X3] - m.e_[X3], e_[Y3] - m.e_[Y3], e_[Z3] - m.e_[Z3], e_[W3] - m.e_[W3]
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::operator *(const Mat4& m) const {
        return Mat4(
            e_[X0] * m.e_[X0] + e_[X1] * m.e_[Y0] + e_[X2] * m.e_[Z0] + e_[X3] * m.e_[W0],
            e_[Y0] * m.e_[X0] + e_[Y1] * m.e_[Y0] + e_[Y2] * m.e_[Z0] + e_[Y3] * m.e_[W0],
            e_[Z0] * m.e_[X0] + e_[Z1] * m.e_[Y0] + e_[Z2] * m.e_[Z0] + e_[Z3] * m.e_[W0],
            e_[W0] * m.e_[X0] + e_[W1] * m.e_[Y0] + e_[W2] * m.e_[Z0] + e_[W3] * m.e_[W0],
            e_[X0] * m.e_[X1] + e_[X1] * m.e_[Y1] + e_[X2] * m.e_[Z1] + e_[X3] * m.e_[W1],
            e_[Y0] * m.e_[X1] + e_[Y1] * m.e_[Y1] + e_[Y2] * m.e_[Z1] + e_[Y3] * m.e_[W1],
            e_[Z0] * m.e_[X1] + e_[Z1] * m.e_[Y1] + e_[Z2] * m.e_[Z1] + e_[Z3] * m.e_[W1],
            e_[W0] * m.e_[X1] + e_[W1] * m.e_[Y1] + e_[W2] * m.e_[Z1] + e_[W3] * m.e_[W1],
            e_[X0] * m.e_[X2] + e_[X1] * m.e_[Y2] + e_[X2] * m.e_[Z2] + e_[X3] * m.e_[W2],
            e_[Y0] * m.e_[X2] + e_[Y1] * m.e_[Y2] + e_[Y2] * m.e_[Z2] + e_[Y3] * m.e_[W2],
            e_[Z0] * m.e_[X2] + e_[Z1] * m.e_[Y2] + e_[Z2] * m.e_[Z2] + e_[Z3] * m.e_[W2],
            e_[W0] * m.e_[X2] + e_[W1] * m.e_[Y2] + e_[W2] * m.e_[Z2] + e_[W3] * m.e_[W2],
            e_[X0] * m.e_[X3] + e_[X1] * m.e_[Y3] + e_[X2] * m.e_[Z3] + e_[X3] * m.e_[W3],
            e_[Y0] * m.e_[X3] + e_[Y1] * m.e_[Y3] + e_[Y2] * m.e_[Z3] + e_[Y3] * m.e_[W3],
            e_[Z0] * m.e_[X3] + e_[Z1] * m.e_[Y3] + e_[Z2] * m.e_[Z3] + e_[Z3] * m.e_[W3],
            e_[W0] * m.e_[X3] + e_[W1] * m.e_[Y3] + e_[W2] * m.e_[Z3] + e_[W3] * m.e_[W3]
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::operator *(const T t) const {
         return Mat4(
            e_[X0] * t, e_[Y0] * t, e_[Z0] * t, e_[W0] * t,
            e_[X1] * t, e_[Y1] * t, e_[Z1] * t, e_[W1] * t,
            e_[X2] * t, e_[Y2] * t, e_[Z2] * t, e_[W2] * t,
            e_[X3] * t, e_[Y3] * t, e_[Z3] * t, e_[W3] * t
        );
    }

    template < typename T >
    Mat4< T > operator *(const T t, const Mat4< T >& m) { return m * t; }

    template < typename T >
    T Mat4< T >::getDeterminant() const {
        return (
            e_[X0] * e_[Y1] * e_[Z2] * e_[W3] + e_[X0] * e_[Y2] * e_[Z3] * e_[W1] +  e_[X0] * e_[Y3] * e_[Z1] * e_[W2] +
            e_[X1] * e_[Y0] * e_[Z3] * e_[W2] + e_[X1] * e_[Y2] * e_[Z0] * e_[W3] +  e_[X1] * e_[Y3] * e_[Z2] * e_[W0] +
            e_[X2] * e_[Y0] * e_[Z1] * e_[W3] + e_[X2] * e_[Y1] * e_[Z3] * e_[W0] +  e_[X2] * e_[Y3] * e_[Z0] * e_[W1] +
            e_[X3] * e_[Y0] * e_[Z2] * e_[W1] + e_[X3] * e_[Y1] * e_[Z0] * e_[W2] +  e_[X3] * e_[Y2] * e_[Z1] * e_[W0] -
            e_[X0] * e_[Y1] * e_[Z3] * e_[W2] - e_[X0] * e_[Y2] * e_[Z1] * e_[W3] -  e_[X0] * e_[Y3] * e_[Z2] * e_[W1] -
            e_[X1] * e_[Y0] * e_[Z2] * e_[W3] - e_[X1] * e_[Y2] * e_[Z3] * e_[W0] -  e_[X1] * e_[Y3] * e_[Z0] * e_[W2] -
            e_[X2] * e_[Y0] * e_[Z3] * e_[W1] - e_[X2] * e_[Y1] * e_[Z0] * e_[W3] -  e_[X2] * e_[Y3] * e_[Z1] * e_[W0] -
            e_[X3] * e_[Y0] * e_[Z1] * e_[W2] - e_[X3] * e_[Y1] * e_[Z2] * e_[W0] -  e_[X3] * e_[Y2] * e_[Z0] * e_[W1]
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::getTranspose() const {
        return Mat4(
            e_[X0], e_[X1], e_[X2], e_[X3],
            e_[Y0], e_[Y1], e_[Y2], e_[Y3],
            e_[Z0], e_[Z1], e_[Z2], e_[Z3],
            e_[W0], e_[W1], e_[W2], e_[W3]
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::getInverse() const {
        const T invDet = static_cast< T >(1.0) / getDeterminant();

        return Mat4(
            e_[Y1] * e_[Z2] * e_[W3] + e_[Y2] * e_[Z3] * e_[W1] + e_[Y3] * e_[Z1] * e_[W2] - e_[Y1] * e_[Z3] * e_[W2] - e_[Y2] * e_[Z1] * e_[W3] - e_[Y3] * e_[Z2] * e_[W1],
            e_[Y0] * e_[Z3] * e_[W2] + e_[Y2] * e_[Z0] * e_[W3] + e_[Y3] * e_[Z2] * e_[W0] - e_[Y0] * e_[Z2] * e_[W3] - e_[Y2] * e_[Z3] * e_[W0] - e_[Y3] * e_[Z0] * e_[W2],
            e_[Y0] * e_[Z1] * e_[W3] + e_[Y1] * e_[Z3] * e_[W0] + e_[Y3] * e_[Z0] * e_[W1] - e_[Y0] * e_[Z3] * e_[W1] - e_[Y1] * e_[Z0] * e_[W3] - e_[Y3] * e_[Z1] * e_[W0],
            e_[Y0] * e_[Z2] * e_[W1] + e_[Y1] * e_[Z0] * e_[W2] + e_[Y2] * e_[Z1] * e_[W0] - e_[Y0] * e_[Z1] * e_[W2] - e_[Y1] * e_[Z2] * e_[W0] - e_[Y2] * e_[Z0] * e_[W1],
            e_[X1] * e_[Z3] * e_[W2] + e_[X2] * e_[Z1] * e_[W3] + e_[X3] * e_[Z2] * e_[W1] - e_[X1] * e_[Z2] * e_[W3] - e_[X2] * e_[Z3] * e_[W1] - e_[X3] * e_[Z1] * e_[W2],
            e_[X0] * e_[Z2] * e_[W3] + e_[X2] * e_[Z3] * e_[W0] + e_[X3] * e_[Z0] * e_[W2] - e_[X0] * e_[Z3] * e_[W2] - e_[X2] * e_[Z0] * e_[W3] - e_[X3] * e_[Z2] * e_[W0],
            e_[X0] * e_[Z3] * e_[W1] + e_[X1] * e_[Z0] * e_[W3] + e_[X3] * e_[Z1] * e_[W0] - e_[X0] * e_[Z1] * e_[W3] - e_[X1] * e_[Z3] * e_[W0] - e_[X3] * e_[Z0] * e_[W1],
            e_[X0] * e_[Z1] * e_[W2] + e_[X1] * e_[Z2] * e_[W0] + e_[X2] * e_[Z0] * e_[W1] - e_[X0] * e_[Z2] * e_[W1] - e_[X1] * e_[Z0] * e_[W2] - e_[X2] * e_[Z1] * e_[W0],
            e_[X1] * e_[Y2] * e_[W3] + e_[X2] * e_[Y3] * e_[W1] + e_[X3] * e_[Y1] * e_[W2] - e_[X1] * e_[Y3] * e_[W2] - e_[X2] * e_[Y1] * e_[W3] - e_[X3] * e_[Y2] * e_[W1],
            e_[X0] * e_[Y3] * e_[W2] + e_[X2] * e_[Y0] * e_[W3] + e_[X3] * e_[Y2] * e_[W0] - e_[X0] * e_[Y2] * e_[W3] - e_[X2] * e_[Y3] * e_[W0] - e_[X3] * e_[Y0] * e_[W2],
            e_[X0] * e_[Y1] * e_[W3] + e_[X1] * e_[Y3] * e_[W0] + e_[X3] * e_[Y0] * e_[W1] - e_[X0] * e_[Y3] * e_[W1] - e_[X1] * e_[Y0] * e_[W3] - e_[X3] * e_[Y1] * e_[W0],
            e_[X0] * e_[Y2] * e_[W1] + e_[X1] * e_[Y0] * e_[W2] + e_[X2] * e_[Y1] * e_[W0] - e_[X0] * e_[Y1] * e_[W2] - e_[X1] * e_[Y2] * e_[W0] - e_[X2] * e_[Y0] * e_[W1],
            e_[X1] * e_[Y3] * e_[Z2] + e_[X2] * e_[Y1] * e_[Z3] + e_[X3] * e_[Y2] * e_[Z1] - e_[X1] * e_[Y2] * e_[Z3] - e_[X2] * e_[Y3] * e_[Z1] - e_[X3] * e_[Y1] * e_[Z2],
            e_[X0] * e_[Y2] * e_[Z3] + e_[X2] * e_[Y3] * e_[Z0] + e_[X3] * e_[Y0] * e_[Z2] - e_[X0] * e_[Y3] * e_[Z2] - e_[X2] * e_[Y0] * e_[Z3] - e_[X3] * e_[Y2] * e_[Z0],
            e_[X0] * e_[Y3] * e_[Z1] + e_[X1] * e_[Y0] * e_[Z3] + e_[X3] * e_[Y1] * e_[Z0] - e_[X0] * e_[Y1] * e_[Z3] - e_[X1] * e_[Y3] * e_[Z0] - e_[X3] * e_[Y0] * e_[Z1],
            e_[X0] * e_[Y1] * e_[Z2] + e_[X1] * e_[Y2] * e_[Z0] + e_[X2] * e_[Y0] * e_[Z1] - e_[X0] * e_[Y2] * e_[Z1] - e_[X1] * e_[Y0] * e_[Z2] - e_[X2] * e_[Y1] * e_[Z0]
        ) * invDet;
    }

    template < typename T >
    PVec4< T > Mat4< T >::transform(const PVec4< T > v) const {
        return PVec4< T >(
            e_[X0] * v.x + e_[X1] * v.y + e_[X2] * v.z + e_[X3] * v.w,
            e_[Y0] * v.x + e_[Y1] * v.y + e_[Y2] * v.z + e_[Y3] * v.w,
            e_[Z0] * v.x + e_[Z1] * v.y + e_[Z2] * v.z + e_[Z3] * v.w,
            e_[W0] * v.x + e_[W1] * v.y + e_[W2] * v.z + e_[W3] * v.w
        );
    }

    template < typename T >
    Vec3< T > Mat4< T >::transform(const Vec3< T > v) const {
        return Vec3< T >(
            e_[X0] * v.x + e_[X1] * v.y + e_[X2] * v.z + e_[X3],
            e_[Y0] * v.x + e_[Y1] * v.y + e_[Y2] * v.z + e_[Y3],
            e_[Z0] * v.x + e_[Z1] * v.y + e_[Z2] * v.z + e_[Z3]
        );
    }

    template < typename T >
    bool Mat4< T >::isNumeric() {
        return (
            (e_[X0] == e_[X0]) && (e_[Y0] == e_[Y0]) && (e_[Z0] == e_[Z0]) && (e_[W0] == e_[W0]) &&
            (e_[X1] == e_[X1]) && (e_[Y1] == e_[Y1]) && (e_[Z1] == e_[Z1]) && (e_[W1] == e_[W1]) &&
            (e_[X2] == e_[X2]) && (e_[Y2] == e_[Y2]) && (e_[Z2] == e_[Z2]) && (e_[W2] == e_[W2]) &&
            (e_[X3] == e_[X3]) && (e_[Y3] == e_[Y3]) && (e_[Z3] == e_[Z3]) && (e_[W3] == e_[W3])
        );
    }

    template < typename T >
    Mat4< T > Mat4< T >::getIdentity() {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        return Mat4(
            u, n, n, n,
            n, u, n, n,
            n, n, u, n,
            n, n, n, u
        );
    }

    template < typename T >
    Mat4< T > Mat4<T>::getTranslation(const T x, const T y, const T z) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        return Mat4(
                u, n, n, n,
                n, u, n, n,
                n, n, u, n,
                x, y, z, u
        );
    }

    template < typename T >
    Mat4< T > Mat4<T>::getScaling(const T x, const T y, const T z) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        return Mat4(
                x, n, n, n,
                n, y, n, n,
                n, n, z, n,
                n, n, n, u
        );
    }

    template < typename T >
    Mat4< T > Mat4<T>::getRotation(const T r, const T x, const T y, const T z) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        const T rad = r * Constants< T >::InvDeg360() * Constants< T >::Pi2();

        const T c = std::cos(rad);
        const T s = std::sin(rad);
        const T t = static_cast< T >(1.0) - c;

        return Mat4(
            t * x * x + c,     t * x * y - s * z, t * x * z + s * y, n,
            t * x * y + s * z, t * y * y + c,     t * y * z - s * x, n,
            t * x * z - s * y, t * y * z + s * x, t * z * z + c,     n,
            n,                 n,                 n,                 u
        );
    }

    template < typename T >
    Mat4< T > Mat4<T>::getProjection(const T fovY, const T aspectRatio, const T near, const T far) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        const T halfRad = fovY / 360.0f * Constants< T >::Pi();

        const T yScale = static_cast< T >(1.0) / tan(halfRad);
        const T xScale = yScale / aspectRatio;
        const T length = far - near;

        return Mat4(
                xScale, n,       n,                                            n,
                n,      yScale,  n,                                            n,
                n,      n,      -(far + near) / length,                       -u,
                n,      n,      -static_cast< T >(2.0) * near * far / length,  n
        );
    }

    template < typename T >
    Mat4< T > Mat4<T>::getOrthoProjection(const T left, const T right, const T bottom, const T top, const T near, const T far) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        const T rl =  static_cast< T >(2.0) / (right - left);
        const T tb =  static_cast< T >(2.0) / (top   - bottom);
        const T fn = -static_cast< T >(2.0) / (far   - near);

        const T tx = -((right + left)   / (right - left));
        const T ty = -((top   + bottom) / (top   - bottom));
        const T tz = -((far   + near)   / (far   - near));

        return Mat4(
            rl,  n,  n, n,
            n,  tb,  n, n,
            n,   n, fn, n,
            tx, ty, tz, u
        );
    }

    typedef Mat4< float >  FloatMat4;
    typedef Mat4< double > DoubleMat4;
};

#pragma pack(pop)

#endif /* RUUKKU_MAT4_HPP */


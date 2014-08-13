/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    mat3.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template for a tightly packing 3x3 matrix. The template paramater is
 * assumed to be a floating point type.
 */

#ifndef RUUKKU_MAT3_HPP
#define RUUKKU_MAT3_HPP

#include <array>
#include <cmath>

#include "../config/packing.hpp"

#include "constants.hpp"
#include "pvec3.hpp"
#include "vec2.hpp"

#pragma pack(push, RUUKKU_FLOATING_POINT_TYPE_PACKING)

namespace ruukku {
    template < typename T >
    class Mat3 {
        public:
            Mat3() {}

            template < typename... E >
            Mat3(E... e) : e_{{e...}} {}

        public:
            const T& operator [](const int i) const { return e_[i]; }
                  T& operator [](const int i)       { return e_[i]; }

            const T* getData() const { return e_.data(); }
                  T* getData()       { return e_.data(); }

        public:
            bool operator ==(const Mat3& m) const;
            bool operator !=(const Mat3& m) const;

            Mat3 operator +(const Mat3& m) const;
            Mat3 operator -(const Mat3& m) const;
            Mat3 operator *(const Mat3& m) const;
            Mat3 operator *(const T     t) const;

            Mat3& operator +=(const Mat3& m) { *this = *this + m; return *this; }
            Mat3& operator -=(const Mat3& m) { *this = *this - m; return *this; }
            Mat3& operator *=(const Mat3& m) { *this = *this * m; return *this; }
            Mat3& operator *=(const T     t) { *this = *this * t; return *this; }

        public:
            T    getDeterminant() const;
            Mat3 getTranspose()   const;
            Mat3 getInverse()     const;

        public:
            void translate (const T x, const T y) { this->operator *=(getTranslation(x, y)); }
            void scale     (const T x, const T y) { this->operator *=(getScaling(x, y)); }

            void rotate(const T r) { this->operator *=(getRotation(r)); }

        public:
            PVec3< T > transform(const PVec3< T > v) const;
            Vec2< T >  transform(const Vec2 < T > v) const;

        public:
            bool isNumeric();

        public:
            static Mat3 getIdentity();

            static Mat3 getTranslation (const T x, const T y);
            static Mat3 getScaling     (const T x, const T y);
            static Mat3 getRotation    (const T r);

        public:
            static const int X0 = 0;
            static const int Y0 = 1;
            static const int W0 = 2;

            static const int X1 = 3;
            static const int Y1 = 4;
            static const int W1 = 5;

            static const int X2 = 6;
            static const int Y2 = 7;
            static const int W2 = 8;

        private:
            std::array< T, 9 > e_;
    };

    template < typename T >
    bool Mat3< T >::operator ==(const Mat3& m) const {
        return (
            (e_[X0] == m.e_[X0]) && (e_[Y0] == m.e_[Y0]) && (e_[W0] == m.e_[W0]) &&
            (e_[X1] == m.e_[X1]) && (e_[Y1] == m.e_[Y1]) && (e_[W1] == m.e_[W1]) &&
            (e_[X2] == m.e_[X2]) && (e_[Y2] == m.e_[Y2]) && (e_[W2] == m.e_[W2])
         );
    }

    template < typename T >
    bool Mat3< T >::operator !=(const Mat3& m) const {
        return (
            (e_[X0] != m.e_[X0]) || (e_[Y0] != m.e_[Y0]) || (e_[W0] != m.e_[W0]) ||
            (e_[X1] != m.e_[X1]) || (e_[Y1] != m.e_[Y1]) || (e_[W1] != m.e_[W1]) ||
            (e_[X2] != m.e_[X2]) || (e_[Y2] != m.e_[Y2]) || (e_[W2] != m.e_[W2])
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::operator +(const Mat3& m) const {
        return Mat3(
            e_[X0] + m.e_[X0], e_[Y0] + m.e_[Y0], e_[W0] + m.e_[W0],
            e_[X1] + m.e_[X1], e_[Y1] + m.e_[Y1], e_[W1] + m.e_[W1],
            e_[X2] + m.e_[X2], e_[Y2] + m.e_[Y2], e_[W2] + m.e_[W2]
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::operator -(const Mat3& m) const {
         return Mat3(
            e_[X0] - m.e_[X0], e_[Y0] - m.e_[Y0], e_[W0] - m.e_[W0],
            e_[X1] - m.e_[X1], e_[Y1] - m.e_[Y1], e_[W1] - m.e_[W1],
            e_[X2] - m.e_[X2], e_[Y2] - m.e_[Y2], e_[W2] - m.e_[W2]
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::operator *(const Mat3& m) const {
        return Mat3(
            e_[X0] * m.e_[X0] + e_[X1] * m.e_[Y0] + e_[X2] * m.e_[W0],
            e_[Y0] * m.e_[X0] + e_[Y1] * m.e_[Y0] + e_[Y2] * m.e_[W0],
            e_[W0] * m.e_[X0] + e_[W1] * m.e_[Y0] + e_[W2] * m.e_[W0],
            e_[X0] * m.e_[X1] + e_[X1] * m.e_[Y1] + e_[X2] * m.e_[W1],
            e_[Y0] * m.e_[X1] + e_[Y1] * m.e_[Y1] + e_[Y2] * m.e_[W1],
            e_[W0] * m.e_[X1] + e_[W1] * m.e_[Y1] + e_[W2] * m.e_[W1],
            e_[X0] * m.e_[X2] + e_[X1] * m.e_[Y2] + e_[X2] * m.e_[W2],
            e_[Y0] * m.e_[X2] + e_[Y1] * m.e_[Y2] + e_[Y2] * m.e_[W2],
            e_[W0] * m.e_[X2] + e_[W1] * m.e_[Y2] + e_[W2] * m.e_[W2]
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::operator *(const T t) const {
         return Mat3(
            e_[X0] * t, e_[Y0] * t, e_[W0] * t,
            e_[X1] * t, e_[Y1] * t, e_[W1] * t,
            e_[X2] * t, e_[Y2] * t, e_[W2] * t
        );
    }

    template < typename T >
    Mat3< T > operator *(const T t, const Mat3< T >& m) { return m * t; }

    template < typename T >
    T Mat3< T >::getDeterminant() const {
        return (
            e_[X0] * e_[Y1] * e_[W2] +
            e_[Y0] * e_[W1] * e_[X2] +
            e_[W0] * e_[X1] * e_[Y2] -
            e_[X0] * e_[W1] * e_[Y2] -
            e_[W0] * e_[Y1] * e_[X2] -
            e_[Y0] * e_[X1] * e_[W2]
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::getTranspose() const {
        return Mat3(
            e_[X0], e_[X1], e_[X2],
            e_[Y0], e_[Y1], e_[Y2],
            e_[W0], e_[W1], e_[W2]
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::getInverse() const {
        const T invDet = static_cast< T >(1.0) / getDeterminant();

        return Mat3(
            e_[Y1] * e_[W2] - e_[Y2] * e_[W1],
            e_[Y2] * e_[W0] - e_[Y0] * e_[W2],
            e_[Y0] * e_[W1] - e_[Y1] * e_[W0],
            e_[X2] * e_[W1] - e_[X1] * e_[W2],
            e_[X0] * e_[W2] - e_[X2] * e_[W0],
            e_[X1] * e_[W0] - e_[X0] * e_[W1],
            e_[X1] * e_[Y2] - e_[X2] * e_[Y1],
            e_[X2] * e_[Y0] - e_[X0] * e_[Y2],
            e_[X0] * e_[Y1] - e_[X1] * e_[Y0]
        ) * invDet;
    }

    template < typename T >
    PVec3< T > Mat3< T >::transform(const PVec3< T > v) const {
        return PVec3< T >(
            e_[X0] * v.x + e_[X1] * v.y + e_[X2] * v.z,
            e_[Y0] * v.x + e_[Y1] * v.y + e_[Y2] * v.z,
            e_[W0] * v.x + e_[W1] * v.y + e_[W2] * v.z
        );
    }

    template < typename T >
    Vec2< T > Mat3< T >::transform(const Vec2< T > v) const {
        return Vec2< T >(
            e_[X0] * v.x + e_[X1] * v.y + e_[X2],
            e_[Y0] * v.x + e_[Y1] * v.y + e_[Y2]
        );
    }

    template < typename T >
    bool Mat3< T >::isNumeric() {
        return (
            (e_[X0] == e_[X0]) && (e_[Y0] == e_[Y0]) && (e_[W0] == e_[W0]) &&
            (e_[X1] == e_[X1]) && (e_[Y1] == e_[Y1]) && (e_[W1] == e_[W1]) &&
            (e_[X2] == e_[X2]) && (e_[Y2] == e_[Y2]) && (e_[W2] == e_[W2])
        );
    }

    template < typename T >
    Mat3< T > Mat3< T >::getIdentity() {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        return Mat3(
            u, n, n,
            n, u, n,
            n, n, u
        );
    }

    template < typename T >
    Mat3< T > Mat3<T>::getTranslation(const T x, const T y) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        return Mat3(
            u, n, n,
            n, u, n,
            x, y, u
        );
    }

    template < typename T >
    Mat3< T > Mat3<T>::getScaling(const T x, const T y) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        return Mat3(
            x, n, n,
            n, y, n,
            n, n, u
        );
    }

    template < typename T >
    Mat3< T > Mat3<T>::getRotation(const T r) {
        const T n = static_cast< T >(0.0);
        const T u = static_cast< T >(1.0);

        const T rad = r * Constants< T >::InvDeg360() * Constants< T >::Pi2();

        const T c = std::cos(rad);
        const T s = std::sin(rad);

        return Mat3(
             c, s, n,
            -s, c, n,
             n, n, u
        );
    }

    typedef Mat3< float >  FloatMat3;
    typedef Mat3< double > DoubleMat3;
};

#pragma pack(pop)

#endif /* RUUKKU_MAT3_HPP */


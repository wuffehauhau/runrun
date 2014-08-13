/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    staticarray2.hpp
 * Created: 2014-06-07
 * Authors: Jani Salo
 */

/*
 * Simple template wrapper for treating an array as a two dimensional array.
 */

#ifndef RUNRUN_STATICARRAY2_HPP
#define RUNRUN_STATICARRAY2_HPP

#include <array>
#include <cassert>
#include <functional>

#include "ruukku/math/ivec2.hpp"

namespace runrun {
template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    class StaticArray2 {
        public:
            static const unsigned int AREA = X_SIZE * Y_SIZE;

            std::array< T, AREA > data;

            ruukku::Int2 getSize() const;

            bool         isInside(const ruukku::Int2& pos) const;
            unsigned int getIndex(const ruukku::Int2& pos) const;

            const T& operator [](const unsigned int index) const;
                  T& operator [](const unsigned int index);

            const T& operator [](const ruukku::Int2& pos) const;
                  T& operator [](const ruukku::Int2& pos);

            void loopElements(std::function<void (const T& t, const ruukku::Int2& pos)> func) const;
            void loopElements(std::function<void       (T& t, const ruukku::Int2& pos)> func);
    };

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    ruukku::Int2 StaticArray2< T, X_SIZE, Y_SIZE >::getSize() const { return ruukku::Int2(X_SIZE, Y_SIZE); }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    bool StaticArray2< T, X_SIZE, Y_SIZE >::isInside(const ruukku::Int2& pos) const {
        return (
            pos.x >= 0 && pos.x < static_cast< int >(X_SIZE) &&
            pos.y >= 0 && pos.y < static_cast< int >(Y_SIZE)
        );
    }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    unsigned int StaticArray2< T, X_SIZE, Y_SIZE >::getIndex(const ruukku::Int2& pos) const { return pos.x + pos.y * X_SIZE; }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    const T& StaticArray2< T, X_SIZE, Y_SIZE >::operator [](const unsigned int index) const {
        assert(index < data.size());
        return data[index];
    }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    T& StaticArray2< T, X_SIZE, Y_SIZE >::operator [](const unsigned int index) {
        assert(index < data.size());
        return data[index];
    }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    const T& StaticArray2< T, X_SIZE, Y_SIZE >::operator [](const ruukku::Int2& pos) const {
        assert(isInside(pos));
        return data[getIndex(pos)];
    }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    T& StaticArray2< T, X_SIZE, Y_SIZE >::operator [](const ruukku::Int2& pos) {
        assert(isInside(pos));
        return data[getIndex(pos)];
    }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    void StaticArray2< T, X_SIZE, Y_SIZE >::loopElements(std::function<void (const T& t, const ruukku::Int2& pos)> func) const {
        unsigned int index = 0;

        for (unsigned int y = 0; y < Y_SIZE; y++) {
            for (unsigned int x = 0; x < X_SIZE; x++) {
                const ruukku::Int2 pos(x, y);
                func(data[index++], pos);
            }
        }
    }

    template < typename T, unsigned int X_SIZE, unsigned int Y_SIZE >
    void StaticArray2< T, X_SIZE, Y_SIZE >::loopElements(std::function< void (T& t, const ruukku::Int2& pos) > func) {
        unsigned int index = 0;

        for (unsigned int y = 0; y < Y_SIZE; y++) {
            for (unsigned int x = 0; x < X_SIZE; x++) {
                const ruukku::Int2 pos(x, y);
                func(data[index++], pos);
            }
        }
    }
};

#endif /* RUNRUN_STATICARRAY2_HPP */


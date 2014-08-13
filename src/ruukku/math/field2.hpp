/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    field2.hpp
 * Created: 2012-08-07
 * Authors: Jani Salo
 */

/*
 * A template class for a dynamic two dimensional array.
 */

#ifndef RUUKKU_FIELD2_HPP
#define RUUKKU_FIELD2_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <vector>

#include "../misc/uncopyable.hpp"

#include "ivec2.hpp"
#include "rect.hpp"

namespace ruukku {
    template < typename T >
    class Field2 {
        public:
            Field2() : size_(Int2(0, 0)) {}
            Field2(const Int2& size);

            virtual ~Field2() {}

        public:
            void release();
            void resize(const Int2& size);

        public:
            bool isNull() const { return (data_.size() == 0); }
            Int2 getSize() const { return size_; }

        public:
            bool isInside(const Int2& pos) const { return (pos.x >= 0 && pos.x < size_.x) && (pos.y >= 0 && pos.y < size_.y); }

            int getIndex(const Int2& pos) const { return pos.x + pos.y * size_.x; }

            const T& operator [](const Int2& pos) const { assert(isInside(pos)); return data_[getIndex(pos)]; }
                  T& operator [](const Int2& pos)       { assert(isInside(pos)); return data_[getIndex(pos)]; }

            const T& operator [](const std::size_t index) const { return data_[index]; }
                  T& operator [](const std::size_t index)       { return data_[index]; }

            const std::vector< T >& getData() const { return data_; }
                  std::vector< T >& getData()       { return data_; }

        public:
            void loop(std::function<void (const T& value, const Int2& pos)> func) const;
            void loop(std::function<void (      T& value, const Int2& pos)> func);

        public:
            void flip(const bool flipX, const bool flipY);
            void copy(const Int2& pos, const Field2< T >& source, const IntRect& rect = IntRect(0, 0, 0, 0));

        private:
            Int2 size_;

            std::vector< T > data_;
    };

    template < typename T >
    Field2< T >::Field2(const Int2& size) : size_(0, 0) {
        if (size.x <= 0 || size.y <= 0) throw std::runtime_error("Invalid field size.");
        data_.resize(size.x * size.y);
        size_ = size;
    }

    template < typename T >
    void Field2< T >::release() {
        data_.clear();
        data_.shrink_to_fit();
        size_ = Int2(0, 0);
    }

    template < typename T >
    void Field2< T >::resize(const Int2& size)  {
        release();
        *this = Field2(size);
    }

    template < typename T >
    void Field2< T >::loop(std::function<void (const T& value, const Int2& pos)> func) const {
        for (int y = 0; y < size_.y; y++) {
            for (int x = 0; x < size_.x; x++) {
                const Int2 pos(x, y);
                func(data_[getIndex(pos)], pos);
            }
        }
    }

    template < typename T >
    void Field2< T >::loop(std::function<void (T& value, const Int2& pos)> func) {
        for (int y = 0; y < size_.y; y++) {
            for (int x = 0; x < size_.x; x++) {
                const Int2 pos(x, y);
                func(data_[getIndex(pos)], pos);
            }
        }
    }

    template < typename T >
    void Field2< T >::flip(const bool flipX, const bool flipY) {
        if (isNull())             return;
        if ((!flipX) && (!flipY)) return;

        // Copy will act as source.
        Field2< T > copy = *this;

        Int2 writeStart(0, 0);
        Int2 writeEnd(size_.x - 1, size_.y - 1);
        Int2 writeDir(1, 1);

        if (flipX) {
            std::swap(writeStart.x, writeEnd.x);
            writeDir.x = -1;
        }
        if (flipY) {
            std::swap(writeStart.y, writeEnd.y);
            writeDir.y = -1;
        }

        Int2 readPos;
        Int2 writePos;

        // Copy from source to this.
        for (readPos.y = 0, writePos.y = writeStart.y; readPos.y < size_.y; readPos.y++, writePos.y += writeDir.y) {
            for (readPos.x = 0, writePos.x = writeStart.x; readPos.x < size_.x; readPos.x++, writePos.x += writeDir.x) {
                (*this)[writePos] = copy[readPos];
            }
        }
    }

    template < typename T >
    void Field2< T >::copy(const Int2& pos, const Field2< T >& source, const IntRect& rect) {
        if (isNull() || source.isNull()) return;

        IntRect copyArea;

        // Clip copy area against source.
        if (!rect.hasArea()) copyArea = IntRect(0, 0, source.size_.x, source.size_.y);
        else                 copyArea = IntRect(0, 0, source.size_.x, source.size_.y).clip(rect);

        const Int2 readStart(copyArea.posX, copyArea.posY);

        // Translate copy area to destination.
        copyArea.posX = pos.x;
        copyArea.posY = pos.y;

        // Clip copy area against destination.
        copyArea = IntRect(0, 0, size_.x, size_.y).clip(copyArea);
        if (!copyArea.hasArea()) return;

        const Int2 writeStart (copyArea.posX,                  copyArea.posY);
        const Int2 writeEnd   (copyArea.posX + copyArea.sizeX, copyArea.posY + copyArea.sizeY);

        Int2 readPos;
        Int2 writePos;

        // Copy from source to this.
        for (readPos.y = readStart.y, writePos.y = writeStart.y; writePos.y < writeEnd.y; readPos.y++, writePos.y++) {
            for (readPos.x = readStart.x, writePos.x = writeStart.x; writePos.x < writeEnd.x; readPos.x++, writePos.x++) {
                (*this)[writePos] = source[readPos];
            }
        }
    }
};

#endif /* RUUKKU_FIELD2_HPP */


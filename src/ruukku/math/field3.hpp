/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    field3.hpp
 * Created: 2013-01-03
 * Authors: Jani Salo
 */

/*
 * A template class for a dynamic three dimensional array.
 */

#ifndef RUUKKU_FIELD3_HPP
#define RUUKKU_FIELD3_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <vector>

#include "../misc/uncopyable.hpp"

#include "ivec3.hpp"
#include "cubo.hpp"

namespace ruukku {
    template < typename T >
    class Field3 {
        public:
            Field3() : size_(Int3(0, 0, 0)), sizeXY_(0) {}
            Field3(const Int3& size);

            virtual ~Field3() {}

        public:
            void release();
            void resize(const Int3& size);

        public:
            bool isNull() const { return (data_.size() == 0); }
            Int3 getSize() const { return size_; }

        public:
            bool isInside(const Int3& pos) const { return (pos.x >= 0 && pos.x < size_.x) && (pos.y >= 0 && pos.y < size_.y) && (pos.z >= 0 && pos.z < size_.z); }

            int getIndex(const Int3& pos) const { return pos.x + pos.y * size_.x + pos.z * sizeXY_; }

            const T& operator [](const Int3& pos) const { assert(isInside(pos)); return data_[getIndex(pos)]; }
                  T& operator [](const Int3& pos)       { assert(isInside(pos)); return data_[getIndex(pos)]; }

            const T& operator [](const std::size_t index) const { return data_[index]; }
                  T& operator [](const std::size_t index)       { return data_[index]; }

            const std::vector< T >& getData() const { return data_; }
                  std::vector< T >& getData()       { return data_; }

        public:
            void loop(std::function<void (const T& value, const Int3& pos)> func) const;
            void loop(std::function<void (      T& value, const Int3& pos)> func);

        public:
            void flip(const bool flipX, const bool flipY, const bool flipZ);
            void copy(const Int3& pos, const Field3< T >& source, const IntCubo& cubo = IntCubo(0, 0, 0, 0, 0, 0));

        private:
            Int3 size_;
            int sizeXY_;

            std::vector< T > data_;
    };

    template < typename T >
    Field3< T >::Field3(const Int3& size) : size_(0, 0, 0) {
        if (size.x <= 0 || size.y <= 0 || size.z <= 0) throw std::runtime_error("Invalid field size.");
        data_.resize(size.x * size.y * size.z);
        size_   = size;
        sizeXY_ = size.x * size.y;
    }

    template < typename T >
    void Field3< T >::release() {
        data_.clear();
        data_.shrink_to_fit();
        size_ = Int3(0, 0, 0);
    }

    template < typename T >
    void Field3< T >::resize(const Int3& size)  {
        release();
        *this = Field3(size);
    }

    template < typename T >
    void Field3< T >::loop(std::function<void (const T& value, const Int3& pos)> func) const {
        for (int z = 0; z < size_.z; z++) {
            for (int y = 0; y < size_.y; y++) {
                for (int x = 0; x < size_.x; x++) {
                    const Int3 pos(x, y, z);
                    func(data_[getIndex(pos)], pos);
                }
            }
        }
    }

    template < typename T >
    void Field3< T >::loop(std::function<void (T& value, const Int3& pos)> func) {
        for (int z = 0; z < size_.z; z++) {
            for (int y = 0; y < size_.y; y++) {
                for (int x = 0; x < size_.x; x++) {
                    const Int3 pos(x, y, z);
                    func(data_[getIndex(pos)], pos);
                }
            }
        }
    }

    template < typename T >
    void Field3< T >::flip(const bool flipX, const bool flipY, const bool flipZ) {
        if (isNull())                         return;
        if ((!flipX) && (!flipY) && (!flipZ)) return;

        // Copy will act as source.
        Field3< T > copy = *this;

        Int3 writeStart(0, 0, 0);
        Int3 writeEnd(size_.x - 1, size_.y - 1, size_.z - 1);
        Int3 writeDir(1, 1, 1);

        if (flipX) {
            std::swap(writeStart.x, writeEnd.x);
            writeDir.x = -1;
        }
        if (flipY) {
            std::swap(writeStart.y, writeEnd.y);
            writeDir.y = -1;
        }
        if (flipZ) {
            std::swap(writeStart.z, writeEnd.z);
            writeDir.z = -1;
        }

        Int3 readPos;
        Int3 writePos;

        // Copy from source to this.
        for (readPos.z = 0, writePos.z = writeStart.z; readPos.z < size_.z; readPos.z++, writePos.z += writeDir.z) {
            for (readPos.y = 0, writePos.y = writeStart.y; readPos.y < size_.y; readPos.y++, writePos.y += writeDir.y) {
                for (readPos.x = 0, writePos.x = writeStart.x; readPos.x < size_.x; readPos.x++, writePos.x += writeDir.x) {
                    (*this)[writePos] = copy[readPos];
                }
            }
        }
    }

    template < typename T >
    void Field3< T >::copy(const Int3& pos, const Field3< T >& source, const IntCubo& rect) {
        if (isNull() || source.isNull()) return;

        IntCubo copyVolume;

        // Clip copy volume against source.
        if (!rect.hasVolume()) copyVolume = IntCubo(0, 0, 0, source.size_.x, source.size_.y, source.size_.z);
        else                   copyVolume = IntCubo(0, 0, 0, source.size_.x, source.size_.y, source.size_.z).clip(rect);

        const Int3 readStart(copyVolume.posX, copyVolume.posY, copyVolume.posZ);

        // Translate copy volume to destination.
        copyVolume.posX = pos.x;
        copyVolume.posY = pos.y;
        copyVolume.posZ = pos.z;

        // Clip copy volume against destination.
        copyVolume = IntCubo(0, 0, 0, size_.x, size_.y, size_.z).clip(copyVolume);
        if (!copyVolume.hasVolume()) return;

        const Int3 writeStart (copyVolume.posX,                    copyVolume.posY,                    copyVolume.posZ);
        const Int3 writeEnd   (copyVolume.posX + copyVolume.sizeX, copyVolume.posY + copyVolume.sizeY, copyVolume.posZ + copyVolume.sizeZ);

        Int3 readPos;
        Int3 writePos;

        // Copy from source to this.
        for (readPos.z = readStart.z, writePos.z = writeStart.z; writePos.z < writeEnd.z; readPos.z++, writePos.z++) {
            for (readPos.y = readStart.y, writePos.y = writeStart.y; writePos.y < writeEnd.y; readPos.y++, writePos.y++) {
                for (readPos.x = readStart.x, writePos.x = writeStart.x; writePos.x < writeEnd.x; readPos.x++, writePos.x++) {
                    (*this)[writePos] = source[readPos];
                }
            }
        }
    }
};

#endif /* RUUKKU_FIELD3_HPP */


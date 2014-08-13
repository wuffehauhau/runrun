/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    interleavebuffer.hpp
 * Created: 2013-02-02
 * Authors: Jani Salo
 */

/*
 * A class for interleaving vertex data into a byte buffer.
 */

#ifndef RUUKKU_INTERLEAVEBUFFER_HPP
#define RUUKKU_INTERLEAVEBUFFER_HPP

#include <cstdint>
#include <stdexcept>
#include <vector>

#include "vertexbufferinfo.hpp"

namespace ruukku {
    class InterleaveBuffer {
        public:
            InterleaveBuffer(const VertexBufferInfo& bufferInfo, const std::size_t vertexCount) : bufferInfo_(bufferInfo) { setVertexCount(vertexCount); }

        public:
            const VertexBufferInfo& getBufferInfo() const { return bufferInfo_; }

            std::size_t getVertexCount() const { return vertexCount_; }
            void        setVertexCount(const std::size_t count);

        public:
            // Interleaves data into buffer for given attribute.
            // Index is on the range [0, number of attributes in buffer info)
            template < typename T >
            void writeData(const std::size_t index, const std::vector< T >& data);

            const std::vector< std::uint8_t >& getBuffer() const { return buffer_; }

        private:
            VertexBufferInfo bufferInfo_;
            std::size_t      vertexCount_;

            std::vector< std::uint8_t > buffer_;
    };

    template < typename T >
    void InterleaveBuffer::writeData(const std::size_t index, const std::vector< T >& data) {
        try {
            if (index >= bufferInfo_.getAttributeInfoList().size()) {
                throw std::runtime_error(std::string("index out of range."));
            }

            const VertexAttributeInfo& attribute = bufferInfo_.getAttributeInfoList().at(index);

            if (vertexCount_ != data.size()) {
                throw std::runtime_error(std::string("data size doesn't match buffer size."));
            }

            std::size_t readPtr  = 0;
            std::size_t writePtr = bufferInfo_.getAttributeByteOffsetList().at(index);

            const uint8_t* input  = reinterpret_cast< const uint8_t* >(data.data());
                  uint8_t* output = buffer_.data();

            // Interleave data into buffer.
            for (; writePtr < buffer_.size(); readPtr += attribute.getByteSize(), writePtr += bufferInfo_.getByteStride()) {
                for (std::size_t i = 0; i < attribute.getByteSize(); i++) {
                    output[i + writePtr] = input[i + readPtr];
                }
            }
        }
        catch (std::exception& e) {
            throw std::runtime_error(std::string("Couldn't write into interleave buffer: ") + std::string(e.what()));
        }
    }
};

#endif /* RUUKKU_INTERLEAVEBUFFER_HPP */


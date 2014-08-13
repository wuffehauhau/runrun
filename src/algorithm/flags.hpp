/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    bits.hpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

/*
 * General implementation for bit bits.
 */

#ifndef RUNRUN_FLAGS_HPP
#define RUNRUN_FLAGS_HPP

#include <cstdint>
#include <initializer_list>
#include <type_traits>

namespace runrun {
    // TODO Add a check for the underlying enum type.
    template < typename T >
    class Flags {
        public:
            constexpr Flags(const std::uint32_t bits = 0) : bits(bits)                            {}
            constexpr Flags(const T t)                    : bits(static_cast< std::uint32_t >(t)) {}

            bool operator ==(const Flags f) const;
            bool operator !=(const Flags f) const;

            void reset();

            void set   (const T flag);
            void clear (const T flag);

            bool test(const T      flag) const;
            bool test(const Flags& mask) const;

            constexpr std::uint32_t getBits() const;

        private:
            std::uint32_t bits;
    };

    template< typename T >
    bool Flags< T >::operator ==(const Flags< T > f) const { return bits == f.bits; }

    template< typename T >
    bool Flags< T >::operator !=(const Flags< T > f) const { return bits != f.bits; }

    template< typename T >
    void Flags< T >::reset() { bits = 0; }

    template< typename T >
    void Flags< T >::set(const T flag) { bits |=  static_cast< std::uint32_t >(flag); }

    template< typename T >
    void Flags< T >::clear(const T flag) { bits &= ~static_cast< std::uint32_t >(flag); }

    template< typename T >
    bool Flags< T >::test(const T flag) const { return bits & static_cast< std::uint32_t >(flag); }

    template< typename T >
    bool Flags< T >::test(const Flags< T >& mask) const { return (bits & mask.bits) == mask.bits; }

    template < typename T >
    constexpr std::uint32_t Flags< T >::getBits() const { return bits; }
};

#endif /* RUNRUN_FLAGS_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    pluskernel.hpp
 * Created: 2014-07-30
 * Authors: Jani Salo
 */

/*
 * A template class for sampling and storing plus-shaped kernel of abstract data.
 */

#ifndef RUNRUN_PLUSKERNEL_HPP
#define RUNRUN_PLUSKERNEL_HPP

#include <functional>

#include "edgeflags.hpp"
#include "kerneltesttype.hpp"

namespace runrun {
    template < typename T >
    class PlusKernel {
        public:
            T c, l, r, b, t;

            PlusKernel() {}
            PlusKernel(const T& c, const T& l, const T& r, const T& b, const T& t) : c(c), l(l), r(r), b(b), t(t) {}

            EdgeFlags read(std::function< bool (const T& t, const KernelTestType type) > test) const;
    };

    template < typename T >
    EdgeFlags PlusKernel< T >::read(std::function< bool (const T& t, const KernelTestType type) > test) const {
        EdgeFlags flags;

        if (test(c, KernelTestType::TestIn)) {
            if (test(l, KernelTestType::TestOut)) flags.set(EdgeFlag::Left);
            if (test(r, KernelTestType::TestOut)) flags.set(EdgeFlag::Right);
            if (test(b, KernelTestType::TestOut)) flags.set(EdgeFlag::Bottom);
            if (test(t, KernelTestType::TestOut)) flags.set(EdgeFlag::Top);
        }

        return flags;
    }
};

#endif /* RUNRUN_PLUSKERNEL_HPP */


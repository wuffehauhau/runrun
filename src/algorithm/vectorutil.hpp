/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    vectorutil.hpp
 * Created: 28. kesäkuuta 2014
 * Authors: Jani Salo
 */

/*
 * Vector utilities.
 */

#ifndef RUNRUN_VECTORUTIL_HPP
#define RUNRUN_VECTORUTIL_HPP

#include <cassert>
#include <vector>

namespace runrun {
    class VectorUtil {
        public:
            // Replaces the pointed element with an element from the end of
            // the list, and then erases the last element from the vector.
            template < typename T >
            static void replaceErase(std::vector< T >& list, const typename std::vector< T >::iterator& it);
    };

    template < typename T >
    void VectorUtil::replaceErase(std::vector< T >& list, const typename std::vector< T >::iterator& it) {
        assert(list.size() > 0);
        *it = list.back();
        list.pop_back();
    }
};

#endif /* RUNRUN_VECTORUTIL_HPP */


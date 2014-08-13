/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    primitiveutil.hpp
 * Created: 2013-02-04
 * Authors: Jani Salo
 */

/*
 * A collection of small utilities for manipulating primitive data.
 */

#ifndef RUUKKU_PRIMITIVEUTIL_HPP
#define RUUKKU_PRIMITIVEUTIL_HPP

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

namespace ruukku  {
    class PrimitiveUtil {
        public:
            template < typename V, typename I >
            static void indexVertices(std::vector< V >& vertexList, std::vector< I >& indexList, const std::vector< V >& primitiveList);

            template < typename T >
            static void splitQuads(std::vector< T >& triList, const std::vector< T >& quadList);
    };

    template < typename V, typename I >
    void PrimitiveUtil::indexVertices(
              std::vector< V >& vertexList,
              std::vector< I >& indexList,
        const std::vector< V >& primitiveList
    ) {
        const std::size_t newDataBegin = vertexList.size();

        // Push all unique vertices into vertex list.
        for (typename std::vector< V >::const_iterator v = primitiveList.cbegin(); v < primitiveList.cend(); v++) {
            const typename std::vector< V >::iterator it = std::find(vertexList.begin() + newDataBegin, vertexList.end(), *v);

            if (it != vertexList.end()) continue;
            else vertexList.push_back(*v);
        }

        // Generate indices.
        for (typename std::vector< V >::const_iterator v = primitiveList.cbegin(); v < primitiveList.cend(); v++) {
            const typename std::vector< V >::iterator it = std::find(vertexList.begin() + newDataBegin, vertexList.end(), *v);
            if (it == vertexList.end()) {
                throw std::logic_error(std::string("Couldn't index vertices: vertex not listed."));
            }

            indexList.push_back(static_cast< I >(it - vertexList.begin()));
        }
    }

    template < typename T >
    void PrimitiveUtil::splitQuads(
              std::vector< T >& triList,
        const std::vector< T >& quadList
    ) {
        if ((quadList.size() % 4) != 0) {
            throw std::logic_error(std::string("Couldn't break quad data: input isn't divisible by four."));
        }

        // Break each quad into two triangles.
        for (int i = 0; i < quadList.size(); i += 4) {
            triList.push_back(quadList[i + 0]);
            triList.push_back(quadList[i + 1]);
            triList.push_back(quadList[i + 2]);
            triList.push_back(quadList[i + 2]);
            triList.push_back(quadList[i + 3]);
            triList.push_back(quadList[i + 0]);
        }
    }
};

#endif /* RUUKKU_PRIMITIVEUTIL_HPP */


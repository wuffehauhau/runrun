/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    cellflags.hpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

/*
 * Enumeration of flags used in cells.
 */

#ifndef RUNRUN_CELLFLAGS_HPP
#define RUNRUN_CELLFLAGS_HPP

#include <cstdint>

namespace runrun {
    enum class CellFlags : std::uint32_t {
        UpdateStaticTileDataFront = 1,
        UpdateStaticTileDataBack  = 2
    };
};

#endif /* RUNRUN_CELLFLAGS_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    biome.hpp
 * Created: 2014-06-26
 * Authors: Jani Salo
 */

/*
 * An interface for describing world biome.
 */

#ifndef RUNRUN_BIOME_HPP
#define RUNRUN_BIOME_HPP

#include "tilevisualizer.hpp"

namespace runrun {
    class Biome {
        public:
            ~Biome() {}

            virtual Biome*                createCopy()        const = 0;
            virtual const TileVisualizer* getTileVisualizer() const = 0;
    };
};

#endif /* RUNRUN_BIOME_HPP */


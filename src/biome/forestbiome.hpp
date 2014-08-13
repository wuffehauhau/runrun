/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    forestbiome.hpp
 * Created: 2014-06-27
 * Authors: Jani Salo
 */

/*
 * Concrete biome for forest theme.
 */

#ifndef RUNRUN_FORESTBIOME_HPP
#define RUNRUN_FORESTBIOME_HPP

#include "biome.hpp"
#include "foresttilevisualizer.hpp"

namespace runrun {
    class ForestBiome : public Biome {
        public:
            Biome*                createCopy()        const;
            const TileVisualizer* getTileVisualizer() const;

        private:
            ForestTileVisualizer tileVisualizer;
    };

    inline Biome*                ForestBiome::createCopy()        const { return new ForestBiome(*this); }
    inline const TileVisualizer* ForestBiome::getTileVisualizer() const { return &tileVisualizer; }
};

#endif /* RUNRUN_FORESTBIOME_HPP */


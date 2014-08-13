/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    defaultbiome.hpp
 * Created: 2014-06-27
 * Authors: Jani Salo
 */

/*
 * Default biome, does nothing useful but works.
 */

#ifndef RUNRUN_DEFAULTBIOME_HPP
#define RUNRUN_DEFAULTBIOME_HPP

#include "biome.hpp"
#include "defaulttilevisualizer.hpp"

namespace runrun {
    class DefaultBiome : public Biome {
        public:
            Biome*                createCopy()        const;
            const TileVisualizer* getTileVisualizer() const;

        private:
            DefaultTileVisualizer tileVisualizer;
    };

    inline Biome*                DefaultBiome::createCopy()        const { return new DefaultBiome(*this); }
    inline const TileVisualizer* DefaultBiome::getTileVisualizer() const { return &tileVisualizer; }


};

#endif /* RUNRUN_DEFAULTBIOME_HPP */


/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mainresources.hpp
 * Created: 2014-06-11
 * Authors: Jani Salo
 */

/*
 * A simple container for resources loaded at initialization.
 */

#ifndef RUNRUN_MAINRESOURCES_HPP
#define RUNRUN_MAINRESOURCES_HPP

#include <string>

#include "glyph/glyphset.hpp"
#include "shader/glyphshader.hpp"
#include "shader/tileshader.hpp"

namespace runrun {
    class MainResources {
        public:
            MainResources(const std::string& dataPathPrefix);

            const GlyphSet* getGlyphSet() const;

            const GlyphShader* getGlyphShader() const;
            const TileShader* getTileShader()  const;

        private:
            std::unique_ptr< GlyphSet > glyphSet;

            std::unique_ptr< GlyphShader > glyphShader;
            std::unique_ptr< TileShader > tileShader;
    };

    inline const GlyphSet* MainResources::getGlyphSet() const { return glyphSet.get(); }

    inline const GlyphShader* MainResources::getGlyphShader() const { return glyphShader.get(); };
    inline const TileShader* MainResources::getTileShader() const { return tileShader.get(); };
};

#endif /* RUNRUN_MAINRESOURCES_HPP */


/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltexture2d.hpp
 * Created: 2013-01-19
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL texture intended as a 2D texture.
 */

#ifndef RUUKKU_GLTEXTURE2D_HPP
#define RUUKKU_GLTEXTURE2D_HPP

#include <iostream>

#include "../pixel/surface.hpp"
#include "gltexture.hpp"

namespace ruukku {
     class GLTexture2D : public GLTexture {
        public:
            GLTexture2D() {}
            GLTexture2D(const Surface& surface) { readSurface(surface); }

            virtual ~GLTexture2D() {}

        public:
            void bind()   const { glBindTexture(GL_TEXTURE_2D, getID()); }
            void unbind() const { glBindTexture(GL_TEXTURE_2D, 0);       }

        public:
            // Reading to texture will bind it into 2D texture target.
            void readSurface(const Surface& surface) const;
    };
};

#endif /* RUUKKU_GLTEXTURE2D_HPP */


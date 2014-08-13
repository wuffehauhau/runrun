/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltexture3d.hpp
 * Created: 2013-12-22
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL texture intended as a 3D texture.
 */

#ifndef RUUKKU_GLTEXTURE3D_HPP
#define RUUKKU_GLTEXTURE3D_HPP

#include <iostream>

#include "../pixel/pixelvolume.hpp"
#include "gltexture.hpp"

namespace ruukku {
     class GLTexture3D : public GLTexture {
        public:
            GLTexture3D() {}
            GLTexture3D(const PixelVolume& volume) { readVolume(volume); }

            virtual ~GLTexture3D() {}

        public:
            void bind()   const { glBindTexture(GL_TEXTURE_3D, getID()); }
            void unbind() const { glBindTexture(GL_TEXTURE_3D, 0);       }

        public:
            // Reading to texture will bind it into 3D texture target.
            void readVolume(const PixelVolume& volume) const;
    };
};

#endif /* RUUKKU_GLTEXTURE3D_HPP */


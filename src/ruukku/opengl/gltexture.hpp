/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltexture.hpp
 * Created: 2012-12-18
 * Authors: Jani Salo
 */

/*
 * A wrapper for OpenGL texture object.
 */

#ifndef RUUKKU_GLTEXTURE_HPP
#define RUUKKU_GLTEXTURE_HPP

#include "glresource.hpp"

namespace ruukku {
     class GLTexture : public GLResource {
        public:
                     GLTexture();
            virtual ~GLTexture();
     };
};

#endif /* RUUKKU_GLTEXTURE_HPP */


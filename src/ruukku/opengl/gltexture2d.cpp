/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltexture2d.cpp
 * Created: 2013-01-19
 * Authors: Jani Salo
 */


#include "glerror.hpp"
#include "gltexture2d.hpp"

using namespace std;

namespace ruukku {
    void GLTexture2D::readSurface(const Surface& surface) const {
        try {
            GLError::clearAll();

            glBindTexture(GL_TEXTURE_2D, getID());
            GLError::throwExceptionOnError();

            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                GL_RGBA8,
                surface.getSize().x,
                surface.getSize().y,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                surface.getData().data()
            );
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't create a texture from surface: ") + string(e.what()));
        }
    }
};


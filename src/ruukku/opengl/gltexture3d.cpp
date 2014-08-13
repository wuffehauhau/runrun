/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltexture3d.cpp
 * Created: 2013-12-22
 * Authors: Jani Salo
 */


#include "glerror.hpp"
#include "gltexture3d.hpp"

using namespace std;

namespace ruukku {
    void GLTexture3D::readVolume(const PixelVolume& volume) const {
        try {
            GLError::clearAll();

            glBindTexture(GL_TEXTURE_3D, getID());
            GLError::throwExceptionOnError();

            glTexImage3D
            (
                GL_TEXTURE_3D,
                0,
                GL_RGBA8,
                volume.getSize().x,
                volume.getSize().y,
                volume.getSize().z,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                volume.getData().data()
            );
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't create a texture from volume: ") + string(e.what()));
        }
    }
};


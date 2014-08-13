/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltexture.cpp
 * Created: 2012-12-18
 * Authors: Jani Salo
 */

#include <iostream>

#include "glerror.hpp"
#include "gltexture.hpp"

using namespace std;

namespace ruukku {
    GLTexture::GLTexture() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenTextures(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteTextures(1, &id);
            throw GLException(string("Couldn't create texture: ") + string(e.what()));
        }
    }

    GLTexture::~GLTexture() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteTextures(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            cerr << "Couldn't delete texture: " << e.what() << endl;
        }
    }
};


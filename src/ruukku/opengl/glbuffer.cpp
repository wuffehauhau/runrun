/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glbuffer.cpp
 * Created: 2012-12-10
 * Authors: Jani Salo
 */

#include <iostream>

#include "glerror.hpp"
#include "glbuffer.hpp"

using namespace std;

namespace ruukku {
    GLBuffer::GLBuffer() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenBuffers(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteBuffers(1, &id);
            throw GLException(string("Couldn't create buffer: ") + string(e.what()));
        }
    }

    GLBuffer::~GLBuffer() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteBuffers(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            cerr << "Couldn't delete buffer: " << e.what() << endl;
        }
    }
};


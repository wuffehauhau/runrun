/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glvertexarray.cpp
 * Created: 2013-02-07
 * Authors: Jani Salo
 */

#include <iostream>

#include "glerror.hpp"
#include "glvertexarray.hpp"

using namespace std;

namespace ruukku {
    GLVertexArray::GLVertexArray() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenVertexArrays(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteBuffers(1, &id);
            throw GLException(string("Couldn't create vertex array ") + string(e.what()));
        }
    }

    GLVertexArray::~GLVertexArray() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteVertexArrays(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            cerr << "Couldn't delete vertex array: " << e.what() << endl;
        }
    }
};


/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glerror.cpp
 * Created: 2012-08-13
 * Authors: Jani Salo
 */

#include "glerror.hpp"

using namespace std;

namespace ruukku {
    string GLError::toString(const GLenum error) {
        switch (error) {
            case GL_NO_ERROR:          return string("GL_NO_ERROR");
            case GL_INVALID_ENUM:      return string("GL_INVALID_ENUM");
            case GL_INVALID_VALUE:     return string("GL_INVALID_VALUE");
            case GL_INVALID_OPERATION: return string("GL_INVALID_OPERATION");
            case GL_STACK_OVERFLOW:    return string("GL_STACK_OVERFLOW");
            case GL_STACK_UNDERFLOW:   return string("GL_STACK_UNDERFLOW");
            case GL_OUT_OF_MEMORY:     return string("GL_OUT_OF_MEMORY");
            case GL_TABLE_TOO_LARGE:   return string("GL_TABLE_TOO_LARGE");
        }

        return string("Unknown OpenGL error.");
    }

    void GLError::clearAll() {
        if (!checkErrors_) return;

        // Get errors until the error buffer is empty.
        for (int i = 0; i < MAX_ERROR_COUNT; i++) {
            if (glGetError() == GL_NO_ERROR) return;
        }
    }

    void GLError::throwExceptionOnError() {
        if (!checkErrors_) return;

        string str;

        // Create a string of all errors in the buffer.
        for (int i = 0; i < MAX_ERROR_COUNT; i++) {
            const GLenum error = glGetError();
            if (error == GL_NO_ERROR) break;
            if (i > 0) str.append(", ");
            str.append(toString(error));
        }

        if (str.size() > 0) throw GLException(str);
    }

    bool GLError::checkErrors_ = true;
}


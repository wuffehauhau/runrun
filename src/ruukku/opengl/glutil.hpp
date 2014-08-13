/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glutil.hpp
 * Created: 2013-01-07
 * Authors: Jani Salo
 */

/*
 * A collection of small OpenGL utilities.
 */

#ifndef RUUKKU_GLUTIL_HPP
#define RUUKKU_GLUTIL_HPP

#include <stdexcept>
#include <string>

#include <GL/glew.h>

namespace ruukku {
    class GLUtil {
        public:
            static std::size_t getByteSizefromEnum(const GLenum e) {
                switch (e) {
                    case GL_BYTE:           return sizeof(GLbyte);
                    case GL_SHORT:          return sizeof(GLshort);
                    case GL_INT:            return sizeof(GLint);
                    case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
                    case GL_UNSIGNED_SHORT: return sizeof(GLushort);
                    case GL_UNSIGNED_INT:   return sizeof(GLuint);
                    case GL_FLOAT:          return sizeof(GLfloat);
                    case GL_DOUBLE:         return sizeof(GLdouble);

                    // Used for no type at places.
                    case GL_NONE: return 0;

                    default: {
                        throw std::runtime_error(std::string("Couldn't determine size of an OpenGL type."));
                    }
                }
            }
    };
};

#endif /* RUUKKU_GLUTIL_HPP */


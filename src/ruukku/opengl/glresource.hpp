/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glresource.hpp
 * Created: 2012-08-10
 * Authors: Jani Salo
 */

/*
 * A base class for OpenGL objects.
 */

#ifndef RUUKKU_GLRESOURCE_HPP
#define RUUKKU_GLRESOURCE_HPP

#include <GL/glew.h>
#include "../misc/uncopyable.hpp"

namespace ruukku {
    class GLResource : public Uncopyable {
        public:
            GLResource() : id_(0) {}
            virtual ~GLResource() {}

        public:
            bool isOK() const { return id_ != 0; }

            GLuint getID() const { return id_; }
            void   setID(const GLuint id) { id_ = id; }

        private:
            GLuint id_;
    };
};

#endif /* RUUKKU_GLRESOURCE_HPP */


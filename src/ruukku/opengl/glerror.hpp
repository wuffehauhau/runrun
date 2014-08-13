/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glerror.hpp
 * Created: 2012-08-12
 * Authors: Jani Salo
 */

/*
 * A collection of methods for handling OpenGL errors.
 */

#ifndef RUUKKU_GLERROR_HPP
#define RUUKKU_GLERROR_HPP

#include <string>
#include <GL/glew.h>

#include "glexception.hpp"

namespace ruukku {
    class GLError {
        public:
            static const int MAX_ERROR_COUNT = 256;

        public:
            static std::string toString(const GLenum error);

        public:
            static void clearAll();
            static void throwExceptionOnError();

        public:
            // Checking OpenGL errors forces OpenGL to flush pipeline.
            static void disableErrors() { checkErrors_ = false; }
            static void enableErrors()  { checkErrors_ = true;  }

        private:
            static bool checkErrors_;
    };
};

#endif /* RUUKKU_GLERROR_HPP */


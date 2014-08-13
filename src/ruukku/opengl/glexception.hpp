/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glexception.hpp
 * Created: 2012-08-13
 * Authors: Jani Salo
 */

/*
 * An exception class for OpenGL errors.
 */

#ifndef RUUKKU_GLEXCEPTION_HPP
#define RUUKKU_GLEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace ruukku {
    class GLException : public std::exception {
        public:
            GLException(const std::string& message) : message_(message) {}
            ~GLException() throw() {}

        public:
            const char* what() const throw() { return message_.c_str(); }

        private:
            std::string message_;
    };
};

#endif /* RUUKKU_GLEXCEPTION_HPP */


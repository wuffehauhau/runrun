/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    displayattributes.hpp
 * Created: 2012-08-21
 * Authors: Jani Salo
 */

/*
 * A container for display surface attributes.
 */

#ifndef RUUKKU_DISPLAYATTRIBUTES_HPP
#define RUUKKU_DISPLAYATTRIBUTES_HPP

namespace ruukku {
    class DisplayAttributes {
        public:
            // Zero defaults to some minimum value for red, green and blue.
            DisplayAttributes(
                const int redBits        = 0,
                const int greenBits      = 0,
                const int blueBits       = 0,
                const int alphaBits      = 0,
                const int depthBits      = 0,
                const int stencilBits    = 0,
                const int glContextMajor = 0,
                const int glContextMinor = 0
            ) :
                redBits_        (redBits),
                greenBits_      (greenBits),
                blueBits_       (blueBits),
                alphaBits_      (alphaBits),
                depthBits_      (depthBits),
                stencilBits_    (stencilBits),
                glContextMajor_ (glContextMajor),
                glContextMinor_ (glContextMinor)
            {}

        public:
            int getRedBits()   const { return redBits_; }
            int getGreenBits() const { return greenBits_; }
            int getBlueBits()  const { return blueBits_; }
            int getAlphaBits() const { return alphaBits_; }

            int getStencilBits() const { return stencilBits_; }
            int getDepthBits()   const { return depthBits_; }

            int getGLContextMajor() const { return glContextMajor_; }
            int getGLContextMinor() const { return glContextMinor_; }

        private:
            int redBits_;
            int greenBits_;
            int blueBits_;
            int alphaBits_;

            int depthBits_;
            int stencilBits_;

            int glContextMajor_;
            int glContextMinor_;
    };
};

#endif /* RUUKKU_DISPLAYATTRIBUTES_HPP */


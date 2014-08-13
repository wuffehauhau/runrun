/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    sdl.hpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

/*
 * Instance counted initializer for SDL. Instancing this class initializes
 * requested subsystems if necessary. All systems are quit only after the
 * last instance of this class is destroyed.
 */

#ifndef RUUKKU_SDL_HPP
#define RUUKKU_SDL_HPP

#include <stdexcept>
#include <SDL2/SDL.h>

#include "../misc/uncopyable.hpp"

#include "keyboardstate.hpp"
#include "mousestate.hpp"

namespace ruukku {
    class SDL : public Uncopyable {
        public:
             SDL(uint32_t sdlFlags = 0);
            ~SDL();

        public:
            KeyboardState readKeyboard() const;
            MouseState    readMouse()    const;

        public:
           SDL_GLContext createGLContext(SDL_Window* window = 0L) const;
           void          deleteGLContext(SDL_GLContext glContext) const { SDL_GL_DeleteContext(glContext); }

        private:
            void clean();

        private:
            static int instanceCount_;
    };
};

#endif /* RUUKKU_SDL_HPP */


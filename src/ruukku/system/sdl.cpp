/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    sdl.cpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

#include <iostream>
#include <string>

#include <GL/glew.h>

#include "sdl.hpp"

using namespace std;

namespace ruukku {
    SDL::SDL(uint32_t sdlFlags) {
        try {
            if (instanceCount_ == 0) {
                cout << "Initializing SDL." << endl;
                if(SDL_Init(0) != 0) throw runtime_error(string("Couldn't initialize SDL: ") + string(SDL_GetError()));
            }

            if ((sdlFlags & SDL_INIT_VIDEO) && (SDL_WasInit(SDL_INIT_VIDEO) == 0)) {
                cout << "Initializing SDL video subsystem." << endl;
                if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) throw runtime_error(string("Couldn't initialize SDL video subsystem: ")    + string(SDL_GetError()));
            }
            if ((sdlFlags & SDL_INIT_AUDIO) && (SDL_WasInit(SDL_INIT_AUDIO) == 0)) {
                cout << "Initializing SDL audio subsystem." << endl;
                if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) throw runtime_error(string("Couldn't initialize SDL audio subsystem: ")    + string(SDL_GetError()));
            }
            if ((sdlFlags & SDL_INIT_TIMER) && (SDL_WasInit(SDL_INIT_TIMER) == 0)) {
                cout << "Initializing SDL timer subsystem." << endl;
                if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0) throw runtime_error(string("Couldn't initialize SDL timer subsystem: ")    + string(SDL_GetError()));
            }
            if ((sdlFlags & SDL_INIT_JOYSTICK) && (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)) {
                cout << "Initializing SDL joystic subsystem." << endl;
                if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) throw runtime_error(string("Couldn't initialize SDL joystick subsystem: ") + string(SDL_GetError()));
            }
            if ((sdlFlags & SDL_INIT_HAPTIC) && (SDL_WasInit(SDL_INIT_HAPTIC) == 0)) {
                cout << "Initializing SDL haptic subsystem." << endl;
                if (SDL_InitSubSystem(SDL_INIT_HAPTIC) != 0) throw runtime_error(string("Couldn't initialize SDL haptic subsystem: ")   + string(SDL_GetError()));
            }
        }
        catch (exception& e) {
            if (instanceCount_ == 0) clean();
            throw;
        }

        instanceCount_++;
    }


    SDL::~SDL() {
        instanceCount_--;
        if (instanceCount_ == 0) clean();
    }

    KeyboardState SDL::readKeyboard() const{
        // Update input status internally.
        SDL_PumpEvents();

        int          keys;
        const Uint8* state;
        SDL_Keymod   modifiers;

        state     = SDL_GetKeyboardState(&keys);
        modifiers = SDL_GetModState();

        return KeyboardState(state, keys, modifiers);
    }

    MouseState SDL::readMouse() const {
        // Update input status internally.
        SDL_PumpEvents();

        int  buttons;
        Int2 position;
        Int2 movement;

        buttons = SDL_GetMouseState(&position.x, &position.y);
        SDL_GetRelativeMouseState(&movement.x, &movement.y);

        return MouseState(position, movement, buttons);
    }

    SDL_GLContext SDL::createGLContext(SDL_Window* window) const {
        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        if (glContext == 0) throw runtime_error("Couldn't create a new GL context.");

        // GLEW will fail for OpenGL 3.2+ if this isn't enabled.
        glewExperimental = GL_TRUE;

        // It's safest to re-initialize glew after each created context.
        if (glewInit() != GLEW_OK) {
            SDL_GL_DeleteContext(glContext);
            throw runtime_error("Couldn't initialize GLEW.");
        };

        return glContext;
    }

    void SDL::clean() {
        if (SDL_WasInit(SDL_INIT_HAPTIC)) {
            cout << "Quitting SDL haptic subsystem." << endl;
            SDL_QuitSubSystem(SDL_INIT_HAPTIC);
        }
        if (SDL_WasInit(SDL_INIT_JOYSTICK)) {
            cout << "Quitting SDL joystic subsystem." << endl;
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
        }
        if (SDL_WasInit(SDL_INIT_TIMER)) {
            cout << "Quitting SDL timer subsystem." << endl;
            SDL_QuitSubSystem(SDL_INIT_TIMER);
        }
        if (SDL_WasInit(SDL_INIT_AUDIO)) {
            cout << "Quitting SDL audio subsystem." << endl;
            SDL_QuitSubSystem(SDL_INIT_AUDIO);
        }
        if (SDL_WasInit(SDL_INIT_VIDEO)) {
            cout << "Quitting SDL video subsystem." << endl;
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
        }

        cout << "Quitting SDL." << endl;
        SDL_Quit();
    }

    int SDL::instanceCount_ = 0;
};


/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    window.cpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

#include "endianness.hpp"
#include "window.hpp"

using namespace std;

namespace ruukku {
    Window::Window(
        const bool  resizable,
        const bool  borderless,
        const Int2& size,
        const Int2& pos,
        const DisplayAttributes& displayAttributes
    ) : sdl_(SDL_INIT_VIDEO), windowHandle_(nullptr), glContext_(nullptr)
    {
        // GL Attributes need to be set before creating the window.
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     displayAttributes.getRedBits());
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   displayAttributes.getGreenBits());
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    displayAttributes.getBlueBits());
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   displayAttributes.getAlphaBits());
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   displayAttributes.getDepthBits());
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, displayAttributes.getStencilBits());
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, displayAttributes.getGLContextMajor());
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, displayAttributes.getGLContextMinor());

        // Not sure if necessary but we need it either way.
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        cout << "Requested window surface format: ";
        cout << "R" << displayAttributes.getRedBits  ();
        cout << "G" << displayAttributes.getGreenBits();
        cout << "B" << displayAttributes.getBlueBits ();
        cout << "A" << displayAttributes.getAlphaBits();
        cout << "Z" << displayAttributes.getDepthBits();
        cout << "S" << displayAttributes.getStencilBits();
        cout << ", OpenGL context version ";
        cout << displayAttributes.getGLContextMajor() << "." << displayAttributes.getGLContextMinor();
        cout << endl;

        Uint32 flags = 0;
        if (resizable)  flags |= SDL_WINDOW_RESIZABLE;
        if (borderless) flags |= SDL_WINDOW_BORDERLESS;

        windowHandle_ = SDL_CreateWindow("Window", pos.x, pos.y, size.x, size.y, flags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if (windowHandle_ == nullptr) throw runtime_error("Couldn't create a new window.");
        cout << "Created a new window." << endl;

        int redBits, greenBits, blueBits, alphaBits;
        int depthBits, stencilBits;
        int contextMajor, contextMinor;

        // Actual attributes might be different from requested.
        SDL_GL_GetAttribute(SDL_GL_RED_SIZE,     &redBits);
        SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE,   &greenBits);
        SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE,    &blueBits);
        SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE,   &alphaBits);
        SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE,   &depthBits);
        SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &stencilBits);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &contextMajor);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &contextMinor);

        displayAttributes_ = DisplayAttributes(redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, contextMajor, contextMinor);

        cout << "Window surface format: ";
        cout << "R" << displayAttributes.getRedBits();
        cout << "G" << displayAttributes.getGreenBits();
        cout << "B" << displayAttributes.getBlueBits();
        cout << "A" << displayAttributes.getAlphaBits();
        cout << "Z" << displayAttributes.getDepthBits();
        cout << "S" << displayAttributes.getStencilBits();
        cout << ", OpenGL context version ";
        cout << displayAttributes.getGLContextMajor() << "." << displayAttributes.getGLContextMinor();
        cout << endl;

        glContext_ = sdl_.createGLContext(windowHandle_);
        resizeGLViewport();
    }

    Window::~Window() {
        cout << "Deleting window OpenGL context." << endl;
        if (glContext_) sdl_.deleteGLContext(glContext_);

        cout << "Destroying window." << endl;
        if (windowHandle_) SDL_DestroyWindow(windowHandle_);
    }

    void Window::setIcon(const Surface& icon) const {
        uint32_t rMask = 0x000000ff;
        uint32_t gMask = 0x0000ff00;
        uint32_t bMask = 0x00ff0000;
        uint32_t aMask = 0xff000000;

        // Make sure the order is RGBA.
        Endianness::flipIfBig(rMask);
        Endianness::flipIfBig(gMask);
        Endianness::flipIfBig(bMask);
        Endianness::flipIfBig(aMask);

        SDL_Surface* iconSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, 32, rMask, gMask, bMask, aMask);
        if (iconSurface == nullptr) return;

        SDL_LockSurface (iconSurface);
        uint8_t* pixels = reinterpret_cast< uint8_t* >(iconSurface->pixels);

        // Copy icon from surface to SDL buffer.
        for (int y = 0; y < 32; y++) {
            for (int x = 0; x < 32; x++) {
                if (!icon.isInside(Int2(x, y))) continue;

                // Since the order is fixed, the endianness doesn't matter here.
                pixels[4 * x + 0 + y * iconSurface->pitch] = icon[Int2(x, y)].r;
                pixels[4 * x + 1 + y * iconSurface->pitch] = icon[Int2(x, y)].g;
                pixels[4 * x + 2 + y * iconSurface->pitch] = icon[Int2(x, y)].b;
                pixels[4 * x + 3 + y * iconSurface->pitch] = icon[Int2(x, y)].a;
            }
        }

        SDL_UnlockSurface(iconSurface);
        SDL_SetWindowIcon(windowHandle_, iconSurface);
    }

    void Window::setTitle(const string& title) const {
        SDL_SetWindowTitle(windowHandle_, title.c_str());
    }

    Int2 Window::getSize() const {
        Int2 size;
        SDL_GetWindowSize(windowHandle_, &size.x, &size.y);

        return size;
    }

    void Window::setSize(const Int2& size) const {
        SDL_SetWindowSize(windowHandle_, size.x, size.y);
    }

    Int2 Window::getPosition() const {
        Int2 position;
        SDL_GetWindowPosition(windowHandle_, &position.x, &position.y);

        return position;
    }

    void Window::setPosition(const Int2& pos) const {
        SDL_SetWindowPosition(windowHandle_, pos.x, pos.y);
    }

    void Window::sendCloseEvent() {
        SDL_Event event;

        event.type            = SDL_WINDOWEVENT;
        event.window.type     = SDL_WINDOWEVENT;
        event.window.event    = SDL_WINDOWEVENT_CLOSE;
        event.window.windowID = getID();

        SDL_PushEvent(&event);
    }

    void Window::setGLContextCurrent() const {
        if (SDL_GL_MakeCurrent(windowHandle_, glContext_) != 0) {
            throw runtime_error("Couldn't make an OpenGL context current.");
        }
    }

    DisplayMode Window::getFullscreenDisplayMode() const {
        SDL_DisplayMode mode;
        SDL_GetWindowDisplayMode(windowHandle_, &mode);

        return DisplayMode(Int2(mode.w, mode.h), mode.format, mode.refresh_rate);
    }

    void Window::setFullscreenDisplayMode(const DisplayMode& displayMode) const {
        SDL_DisplayMode mode;

        mode.w            = displayMode.getResolution().x;
        mode.h            = displayMode.getResolution().y;
        mode.format       = displayMode.getFormat();
        mode.refresh_rate = displayMode.getRefreshRate();
        mode.driverdata   = nullptr;

        SDL_SetWindowDisplayMode(windowHandle_, &mode);
    }

    void Window::toggleFullscreen(const bool isFullscreen) const {
        if (SDL_SetWindowFullscreen(windowHandle_, (isFullscreen ? SDL_TRUE : SDL_FALSE)) != 0) {
            if (isFullscreen) throw runtime_error("Couldn't toggle fullscreen to true.");
            else              throw runtime_error("Couldn't toggle fullscreen to false.");
        }
    }

    void Window::toggleVSync(const bool useVSync) const {
        if (SDL_GL_SetSwapInterval((useVSync ? 1 : 0)) != 0) {
            if (useVSync) throw runtime_error("Couldn't toggle vertical sync to true.");
            else          throw runtime_error("Couldn't toggle vertical sync to false.");
        }
    }
};


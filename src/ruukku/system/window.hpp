/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    window.hpp
 * Created: 2012-08-17
 * Authors: Jani Salo
 */

/*
 * An abstract base class for event based windows. All windows are double
 * buffered and have an OpenGL context associated with them.
 */

#ifndef RUUKKU_WINDOW_HPP
#define RUUKKU_WINDOW_HPP

#include <stdexcept>
#include <string>

#include <GL/glew.h>

#include "../math/ivec2.hpp"
#include "../misc/uncopyable.hpp"
#include "../pixel/surface.hpp"

#include "displayattributes.hpp"
#include "displaymode.hpp"
#include "sdl.hpp"

namespace ruukku {
    class Window : public Uncopyable {
        public:
            Window(
                const bool resizable  = false,
                const bool borderless = false,
                const Int2& size      = Int2(640, 480),
                const Int2& pos       = Int2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
                const DisplayAttributes& displayAttributes = DisplayAttributes()
            );

            virtual ~Window();

        public:
            uint32_t getID() const { return SDL_GetWindowID(windowHandle_); }

            const SDL_Window* getWindowHandle() const { return windowHandle_; }
                  SDL_Window* getWindowHandle()       { return windowHandle_; }

        public:
            void setIcon(const Surface& icon)       const;
            void setTitle(const std::string& title) const;

        public:
            Int2 getSize()                    const;
            void setSize(const Int2& size)    const;

            Int2 getPosition()                const;
            void setPosition(const Int2& pos) const;

        public:
            bool isVisible()   const { return SDL_GetWindowFlags(windowHandle_) | SDL_WINDOW_SHOWN; }
            bool isMinimized() const { return SDL_GetWindowFlags(windowHandle_) | SDL_WINDOW_MINIMIZED; }
            bool isMaximized() const { return SDL_GetWindowFlags(windowHandle_) | SDL_WINDOW_MAXIMIZED; }

            void show()     const { SDL_ShowWindow(windowHandle_); }
            void hide()     const { SDL_HideWindow(windowHandle_); }

            void minimize() const { SDL_MinimizeWindow(windowHandle_); }
            void maximize() const { SDL_MaximizeWindow(windowHandle_); }
            void restore()  const { SDL_RestoreWindow (windowHandle_); }

        public:
            // Pushes a close event for this window into SDL queue.
            void sendCloseEvent();

        public:
            // Make user implement his own version of the class.
            virtual void onUpdate() = 0;

            virtual void onKeyUp   (const uint8_t repeat, const SDL_Keysym& keysym) {}
            virtual void onKeyDown (const uint8_t repeat, const SDL_Keysym& keysym) {}

            virtual void onMouseMotion      (const uint8_t buttonState, const Int2& position, const Int2& motion) {}
            virtual void onMouseButtonUp    (const uint8_t buttonState, const Int2& position) {}
            virtual void onMouseButtonDown  (const uint8_t buttonState, const Int2& position) {}
            virtual void onMouseWheelMotion (const Int2&   motion)                            {}

            virtual void onShow() {}
            virtual void onHide() {}

            virtual void onMove   (const Int2& pos)  {}
            virtual void onResize (const Int2& size) {}

            virtual void onMinimize()    {}
            virtual void onMaximize()    {}
            virtual void onRestore()     {}

            virtual void onMouseEnter()  {}
            virtual void onMouseLeave()  {}

            virtual void onFocusGained() {}
            virtual void onFocusLost()   {}

            virtual bool onClose() { return true; }
            virtual bool onQuit()  { return true; }

        public:
            const SDL& getSDL() const { return sdl_; }

            SDL_GLContext getGLContext() const                      { return glContext_; }
            void          setGLContext(const SDL_GLContext context) { glContext_ = context; }

            // Current GL context is thread specific.
            void setGLContextCurrent() const;

        public:
            const DisplayAttributes& getDisplayAttributes() const { return displayAttributes_; }

            DisplayMode getFullscreenDisplayMode()                               const;
            void        setFullscreenDisplayMode(const DisplayMode& displayMode) const;

            void toggleFullscreen (const bool isFullscreen) const;
            void toggleVSync      (const bool useVSync)     const;

            void resizeGLViewport() const { glViewport(0, 0, getSize().x, getSize().y); }

        public:
            void flipDisplayBuffer() const { SDL_GL_SwapWindow(windowHandle_); }

        private:
            SDL sdl_;

            SDL_Window*   windowHandle_;
            SDL_GLContext glContext_;

            DisplayAttributes displayAttributes_;
    };
};

#endif /* RUUKKU_WINDOW_HPP */


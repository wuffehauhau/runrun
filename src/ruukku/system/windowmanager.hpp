/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    windowmanager.hpp
 * Created: 2012-08-25
 * Authors: Jani Salo
 */

/*
 * A manager class for windows. Stores a reference to a list of windows and
 * manages the list and the windows on it, calling event methods on each
 * window as necessary.
 */

#ifndef RUUKKU_WINDOWMANAGER_HPP
#define RUUKKU_WINDOWMANAGER_HPP

#include <exception>
#include <vector>

#include "sdl.hpp"
#include "window.hpp"

namespace ruukku {
    class WindowManager {
        public:
            WindowManager(std::vector< Window* >* windowList) : shouldQuit_(false), windowList_(windowList) {}

        public:
            bool shouldQuit() const { return shouldQuit_; }

            // Dispatches pending SDL events to windows and calls their update methods.
            void pumpEvents(const int maxEvents = 256);

        public:
            const std::vector< Window* >* getWindowList() const { return windowList_; }
                  std::vector< Window* >* getWindowList()       { return windowList_; }

            void setWindowList(std::vector< Window* >* list) { windowList_ = list; }

            // Returns end of the window list if no window with specified id exist in the list.
            std::vector< Window* >::iterator findWindow(uint32_t id) const;

        private:
            SDL sdl_;

            bool                    shouldQuit_;
            std::vector< Window* >* windowList_;
    };
};

#endif /* RUUKKU_WINDOWMANAGER_HPP */


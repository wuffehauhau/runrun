/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mainwindow.hpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

/*
 * Main window class.
 */

#ifndef RUNRUN_MAINWINDOW_HPP
#define RUNRUN_MAINWINDOW_HPP

#include <memory>

#include "ruukku/system/window.hpp"

#include "engine/engine.hpp"
#include "resource/mainresources.hpp"
#include "system/timer.hpp"

namespace runrun {
    class MainWindow : public ruukku::Window {
        public:
            static const int DEFAULT_WIDTH  = 1280;
            static const int DEFAULT_HEIGHT = 720;

            MainWindow();

            void onKeyUp(const uint8_t repeat, const SDL_Keysym& keysym);
            void onUpdate();

        private:
            ruukku::SDL sdl;

            std::unique_ptr< MainResources > mainResources;
            std::unique_ptr< Engine > engine;

            void readGameInput(GameInput& input);
            void loadResources();

            void saveFrame();
    };
};

#endif /* RUNRUN_MAINWINDOW_HPP */


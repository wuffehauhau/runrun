/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mainwindow.cpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

#include <string>
#include <sstream>

#include "ruukku/pixel/surface.hpp"
#include "mainwindow.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    MainWindow::MainWindow() :
        Window(
            false,
            false,
            Int2(DEFAULT_WIDTH, DEFAULT_HEIGHT),
            Int2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
            DisplayAttributes(8, 8, 8, 8, 0, 0, 3, 1)
        ),
        sdl(SDL_INIT_VIDEO | SDL_INIT_TIMER)
    {
        if (!GLEW_VERSION_3_1) throw runtime_error("OpenGL 3.1 not supported.");

        setTitle(string("runrun"));

        try {
            Surface icon;
            icon.readPNG(string("data/misc/icon.png"));
            setIcon(icon);
        }
        catch (exception& e) {
            cerr << e.what() << endl;
        }

        try {
            toggleVSync(false);
        }
        catch (exception& e) {
            cerr << e.what() << endl;
        }

        loadResources();
    }

    void MainWindow::onKeyUp(const uint8_t repeat, const SDL_Keysym& keysym) {
        if (keysym.sym == SDLK_ESCAPE) {
            sendCloseEvent();
        }
    }

    void MainWindow::onUpdate() {
        static bool shouldUpdate = true;
        static unsigned int subFrame = 0;

        // Both timer and game input are resetted in their constructor.
        static Timer     timer;
        static GameInput input;

        if (shouldUpdate) {
            shouldUpdate = false;

            glClearColor(10.0f / 255.0f, 19.0f / 255.0f, 22.0f / 255.0f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);

            readGameInput(input);
            engine->update(input);

            input.buttons.reset();
            SDL_Delay(1);
        }

        if (timer.getSecondsElapsed() >= 1.0 / 120.0) {
            timer.reset();
            shouldUpdate = true;

            if (subFrame == 1) {
                // DEBUG
                static Timer renderTimer;
                renderTimer.reset();

                engine->render();

                // DEBUG
                cout << "Frame render time: " << renderTimer.getSecondsElapsed() * 1000.0 << "ms" << endl;

                flipDisplayBuffer();

                // DEBUG
                // saveFrame();
            }

            subFrame++;
            if (subFrame > 1) subFrame = 0;
        }
        else {
            readGameInput(input);
            if (timer.getSecondsElapsed() < 1.0 / 120.0 - 1.0 / 200.0) {
                SDL_Delay(1);
            }
        }
    }

    void MainWindow::readGameInput(GameInput& input) {
        KeyboardState kb = getSDL().readKeyboard();

        if (kb.isKeyDown(SDL_SCANCODE_LEFT))  input.buttons.set(GameInput::Button::Left);
        if (kb.isKeyDown(SDL_SCANCODE_RIGHT)) input.buttons.set(GameInput::Button::Right);
        if (kb.isKeyDown(SDL_SCANCODE_DOWN))  input.buttons.set(GameInput::Button::Down);
        if (kb.isKeyDown(SDL_SCANCODE_UP))    input.buttons.set(GameInput::Button::Up);
        if (kb.isKeyDown(SDL_SCANCODE_A))     input.buttons.set(GameInput::Button::ZoomIn);
        if (kb.isKeyDown(SDL_SCANCODE_Z))     input.buttons.set(GameInput::Button::ZoomOut);
    }

    void MainWindow::loadResources() {
        mainResources = unique_ptr< MainResources >(new MainResources(string("data")));
        engine = unique_ptr< Engine >(new Engine(mainResources.get()));
    }

    void MainWindow::saveFrame() {
        static unsigned int frameCount = 0;
        static Surface surface(Int2(DEFAULT_WIDTH, DEFAULT_HEIGHT));

        glReadPixels(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, surface.getData().data());

        stringstream ss;
        ss << "c:/tmp/runrun/frame";

        if      (frameCount < 10) ss << "0000";
        else if (frameCount < 100) ss << "000";
        else if (frameCount < 1000) ss << "00";
        else if (frameCount < 10000) ss << "0";

        ss << frameCount++;
        ss << ".png";

        surface.flip(false, true);
        surface.writePNG(ss.str());
    }
};


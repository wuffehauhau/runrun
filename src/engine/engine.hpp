/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    engine.hpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

/*
 * Runs the main loop for the game engine.
 */

#ifndef RUNRUN_ENGINE_HPP
#define RUNRUN_ENGINE_HPP

#include <memory>
#include <vector>

#include "ruukku/misc/uncopyable.hpp"

#include "animation/gameanimation.hpp"
#include "painter/worldpainter.hpp"
#include "physicsengine/physicsengine.hpp"
#include "player/player.hpp"
#include "renderer/glyphrenderer.hpp"
#include "renderer/tilerenderer.hpp"
#include "resource/mainresources.hpp"
#include "world/world.hpp"

#include "gameinput.hpp"

namespace runrun {
    class Engine : ruukku::Uncopyable {
        public:
            Engine(const MainResources* mainResources);

            double getNominalUpdateLength() const { return 1.0 / 120.0; }

            void update(const GameInput& input);
            void render();

        private:
            std::unique_ptr< GlyphRenderer > glyphRenderer;
            std::unique_ptr< TileRenderer  > tileRenderer;
            std::unique_ptr< WorldPainter  > worldPainter;
            std::unique_ptr< PhysicsEngine > physicsEngine;

            std::unique_ptr< GameAnimation > gameAnimation;

            std::unique_ptr< Player > player;
            std::unique_ptr< World >  world;

            // DEBUG
            float zoom;

            void handleInput(const GameInput& input);
    };
};

#endif /* RUNRUN_ENGINE_HPP */


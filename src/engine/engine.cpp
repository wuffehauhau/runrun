/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    engine.cpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

#include "biome/forestbiome.hpp"
#include "camera/camera.hpp"
#include "map/mapgenerator.hpp"
#include "player/playerstride.hpp"
#include "time/worldtime.hpp"
#include "util/datafile.hpp"

#include "engine.hpp"
#include "system/timer.hpp"

// DEBUG
#include <iomanip>

using namespace std;
using namespace ruukku;

namespace runrun {
    Engine::Engine(const MainResources* mainResources) {
        // DEBUG
        cout << std::setprecision(6);

        glyphRenderer = unique_ptr< GlyphRenderer >(new GlyphRenderer(mainResources->getGlyphShader(), mainResources->getGlyphSet()));
        tileRenderer  = unique_ptr< TileRenderer  >(new TileRenderer(mainResources->getTileShader(),  mainResources->getGlyphSet()));
        worldPainter  = unique_ptr< WorldPainter  >(new WorldPainter(glyphRenderer.get(), tileRenderer.get()));
        physicsEngine = unique_ptr< PhysicsEngine >(new PhysicsEngine());

        gameAnimation = unique_ptr< GameAnimation >(new GameAnimation(string("data")));

        player = unique_ptr< Player >(new Player(gameAnimation->getPlayerAnimation()));
        world  = unique_ptr< World  >(new World());

        ForestBiome forestBiome;
        world->setBiome(forestBiome);

        MapGenerator mapGenerator;
        unique_ptr< Map > testMap = unique_ptr< Map >(mapGenerator.newMapFromTemplate(string("data/map/template/test")));
        world->loadMap(*testMap);

        // TODO Load from map.
        world->setPhysics(MapPhysics(0.998f, 0.01f));

        world->insertPlayer(player.get());
        worldPainter->bufferStaticTileData(world.get());

        player->body().setPosition(GLFloatVec2(105.0f, 115.0f));

        WorldTime::reset();
        zoom = 1.0f;
    }

    void Engine::update(const GameInput& input) {
        WorldTime::tick();

        handleInput(input);
        player->updateState();
        player->updateFrameState();

        // DEBUG
        static Timer timer;
        timer.reset();

        physicsEngine->updateObjects(world.get(), 1.0f / 16.0f, 1.0f);

        // DEBUG
        cout << "Time spent on physics: " << timer.getSecondsElapsed() * 1000.0 << "ms" << endl;
    }

    void Engine::render() {
        // TODO Compute this elsewhere.
        Camera camera(player->body().getPosition(), GLFloatVec2(0.0f, 1.0f), zoom / 48.0f, 1280.0f / 720.0f);
        camera.clip(world.get()->getBoundingBox());

        worldPainter->setCamera(camera);
        worldPainter->drawTiles(world.get());
        worldPainter->drawObjects(world.get());
    }

    void Engine::handleInput(const GameInput& input) {
        PlayerJump   playerJump   = PlayerJump::Idle;
        PlayerStride playerStride = PlayerStride::Idle;

        if      (input.buttons.test(GameInput::Button::Left))  playerStride = PlayerStride::WalkLeft;
        else if (input.buttons.test(GameInput::Button::Right)) playerStride = PlayerStride::WalkRight;

        if (input.buttons.test(GameInput::Button::Up)) playerJump = PlayerJump::Jump;

        player->setCurrentJump(playerJump);
        player->setCurrentStride(playerStride);

        if      (input.buttons.test(GameInput::Button::ZoomIn))  zoom += 0.01f;
        else if (input.buttons.test(GameInput::Button::ZoomOut)) zoom -= 0.01f;

        if      (zoom < 0.5f) zoom = 0.5f;
        else if (zoom > 4.0f) zoom = 4.0f;
    }
};


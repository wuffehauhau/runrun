/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    worldpainter.hpp
 * Created: 2014-06-21
 * Authors: Jani Salo
 */

/*
 * Takes care of rendering the game world.
 */

#ifndef RUNRUN_WORLDPAINTER_HPP
#define RUNRUN_WORLDPAINTER_HPP

#include <memory>

#include "camera/camera.hpp"
#include "renderer/glyphrenderer.hpp"
#include "renderer/tilerenderer.hpp"
#include "world/world.hpp"

namespace runrun {
    class WorldPainter {
        public:
            WorldPainter(GlyphRenderer* glyphRenderer, TileRenderer* tileRenderer);

            void setCamera(const Camera& camera);

            void drawTiles                  (World* world);
            void drawObjects          (const World* world);
            void bufferStaticTileData       (World* world);

        private:
            typedef StaticArray2< std::unique_ptr< TileRenderBuffer >, MapMetrics::MAP_DIM_IN_CELLS, MapMetrics::MAP_DIM_IN_CELLS > RenderBufferArray;

            GlyphRenderer* glyphRenderer;
            TileRenderer*  tileRenderer;

            RenderBufferArray renderBufferArray;

            View                currentView;
            ruukku::GLFloatMat4 currentProjection;
            ruukku::GLFloatMat4 currentModelView;
    };
};

#endif /* RUNRUN_WORLDPAINTER_HPP */


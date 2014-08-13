/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    worldpainter.cpp
 * Created: 2014-06-21
 * Authors: Jani Salo
 */

#include "worldpainter.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    WorldPainter::WorldPainter(GlyphRenderer* glyphRenderer, TileRenderer* tileRenderer) :
        glyphRenderer(glyphRenderer), tileRenderer(tileRenderer)
    {
        renderBufferArray.loopElements([&](unique_ptr< TileRenderBuffer >& buffer, const Int2& position) {
            const GLfloat x = Cell::getEdgeLength() * static_cast< GLfloat >(position.x);
            const GLfloat y = Cell::getEdgeLength() * static_cast< GLfloat >(position.y);

            GLFloatMat3 tileMatrix = GLFloatMat3::getTranslation(x, y);
            buffer = unique_ptr< TileRenderBuffer >(tileRenderer->createTileRenderBuffer(tileMatrix));
        });
    }

    void WorldPainter::setCamera(const Camera& camera) {
        currentView       = camera.getView();
        currentProjection = camera.getProjectionMatrix();
        currentModelView  = camera.getViewMatrix();
    }

    void WorldPainter::drawTiles(World* world) {
        tileRenderer->begin(currentProjection, currentModelView);

        world->findVisibleCells(currentView, [&](Cell& cell) {
            TileRenderBuffer* currentRenderBuffer = renderBufferArray[cell.getGridPosition()].get();

            if (cell.flags.test(CellFlags::UpdateStaticTileDataFront)) {
                tileRenderer->updateTileRenderBufferStaticData(currentRenderBuffer, cell.staticRenderData, TileStaticRenderData::Layer::Front);
                cell.flags.clear(CellFlags::UpdateStaticTileDataFront);
            }

            if (cell.flags.test(CellFlags::UpdateStaticTileDataBack)) {
                tileRenderer->updateTileRenderBufferStaticData(currentRenderBuffer, cell.staticRenderData, TileStaticRenderData::Layer::Back);
                cell.flags.clear(CellFlags::UpdateStaticTileDataBack);
            }

            tileRenderer->updateTileRenderBufferDynamicData(currentRenderBuffer, cell.dynamicRenderData);
            tileRenderer->renderTiles(currentRenderBuffer, TileStaticRenderData::Layer::Back);
            tileRenderer->renderTiles(currentRenderBuffer, TileStaticRenderData::Layer::Front);
        });

        tileRenderer->end();
    }

    void WorldPainter::drawObjects(const World* world) {
        glyphRenderer->begin(currentProjection, currentModelView);

        world->findVisibleObjects(currentView, [&](const Object& object) {
            object.getFrameState().listGlyphs([&](const GlyphRenderInfo& info) {
                glyphRenderer->drawGlyph(info, object.body().getPosition());
            });
        });

        glyphRenderer->end();
    }

    void WorldPainter::bufferStaticTileData(World* world) {
        world->findAllCells([&](Cell& cell) {
            TileRenderBuffer* currentRenderBuffer = renderBufferArray[cell.getGridPosition()].get();
            tileRenderer->updateTileRenderBufferStaticData(currentRenderBuffer, cell.staticRenderData, TileStaticRenderData::Layer::Front);
            tileRenderer->updateTileRenderBufferStaticData(currentRenderBuffer, cell.staticRenderData, TileStaticRenderData::Layer::Back);

            cell.flags.clear(CellFlags::UpdateStaticTileDataFront);
            cell.flags.clear(CellFlags::UpdateStaticTileDataBack);
        });
    }
};


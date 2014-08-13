/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    mainresources.cpp
 * Created: 2014-06-13
 * Authors: Jani Salo
 */

#include "mainresources.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    MainResources::MainResources(const string& dataPathPrefix) {
        Surface font;

        font.readPNG(dataPathPrefix + string("/artwork/glyphset.png"));
        glyphSet = unique_ptr< GlyphSet >(new GlyphSet(font));

        GLVertexShader glyphVertexShader;
        glyphVertexShader.setSourceFromFile(dataPathPrefix + string("/shader/glyphshader.vert"));
        glyphVertexShader.compile();
        cerr << glyphVertexShader.getInfoLog();

        GLFragmentShader glyphFragmentShader;
        glyphFragmentShader.setSourceFromFile(dataPathPrefix + string("/shader/glyphshader.frag"));
        glyphFragmentShader.compile();
        cerr << glyphFragmentShader.getInfoLog();

        GLVertexShader tileVertexShader;
        tileVertexShader.setSourceFromFile(dataPathPrefix + string("/shader/tileshader.vert"));
        tileVertexShader.compile();
        cerr << tileVertexShader.getInfoLog();

        GLFragmentShader tileFragmentShader;
        tileFragmentShader.setSourceFromFile(dataPathPrefix + string("/shader/tileshader.frag"));
        tileFragmentShader.compile();
        cerr << tileFragmentShader.getInfoLog();

        glyphShader = unique_ptr< GlyphShader > (new GlyphShader (glyphVertexShader, glyphFragmentShader));
        tileShader  = unique_ptr< TileShader >  (new TileShader  (tileVertexShader,  tileFragmentShader));
    }
};


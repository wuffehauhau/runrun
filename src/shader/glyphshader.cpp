/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    glyphshader.cpp
 * Created: 2014-05-28
 * Authors: Jani Salo
 */

#include "glyphshader.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    GlyphShader::GlyphShader(
        const GLVertexShader&   vertexShader,
        const GLFragmentShader& fragmentShader
    ) : ShaderProgram(
        vertexShader,
        fragmentShader,
        getVertexArrayInfo(),
        getOutputNameList()
    ) {
        posMatrix  = getUniformLocation(string("posMatrix"));
        texSampler = getUniformLocation(string("texSampler"));
    }

    vector< string > GlyphShader::getOutputNameList() {
        return vector< string > ({
            string("colorOut")
        });
    }

    VertexBufferInfo GlyphShader::getVertexBufferInfo() {
        return VertexBufferInfo({
            VertexAttributeInfo(2, GL_FLOAT, 0, string("vPosition")),
            VertexAttributeInfo(2, GL_FLOAT, 1, string("vTexCoord")),
            VertexAttributeInfo(4, GL_FLOAT, 2, string("vColor")),
        });
    }

    VertexArrayInfo GlyphShader::getVertexArrayInfo() {
        return VertexArrayInfo({getVertexBufferInfo()});
    }
};


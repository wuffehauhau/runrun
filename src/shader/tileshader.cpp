/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    tileshader.cpp
 * Created: 2014-06-06
 * Authors: Jani Salo
 */

#include "tileshader.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    TileShader::TileShader(
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

    vector< string > TileShader::getOutputNameList() {
        return vector< string > ({
            string("colorOut")
        });
    }

    VertexBufferInfo TileShader::getPositionBufferInfo() {
        return VertexBufferInfo({
            VertexAttributeInfo(2, GL_FLOAT, 0, string("vPosition")),
        });
    }

    VertexBufferInfo TileShader::getDynamicBufferInfo() {
        return VertexBufferInfo({
            VertexAttributeInfo(4, GL_FLOAT, 1, string("vLight"))
        });
    }

    VertexBufferInfo TileShader::getStaticBufferInfo() {
        return VertexBufferInfo({
            VertexAttributeInfo(2, GL_FLOAT, 2, string("vTexCoord")),
            VertexAttributeInfo(4, GL_FLOAT, 3, string("vColorFront")),
            VertexAttributeInfo(4, GL_FLOAT, 4, string("vColorBack"))
        });
    }

    VertexArrayInfo TileShader::getVertexArrayInfo() {
        return VertexArrayInfo({
            getPositionBufferInfo(),
            getStaticBufferInfo(),
            getDynamicBufferInfo()
        });
    }
};


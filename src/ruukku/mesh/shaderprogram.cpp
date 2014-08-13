/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    shaderprogram.cpp
 * Created: 2013-02-04
 * Authors: Jani Salo
 */

#include <stdexcept>
#include "shaderprogram.hpp"

using namespace std;

namespace ruukku {
    ShaderProgram::ShaderProgram(
        const GLVertexShader&   vertexShader,
        const GLFragmentShader& fragmentShader,
        const VertexArrayInfo&  vertexArrayInfo,
        const vector< string >& outputNameList
    ) : vertexArrayInfo_(vertexArrayInfo) {
        try {
            program_ = new GLProgram();
            program_->attachShader(vertexShader.getID());
            program_->attachShader(fragmentShader.getID());

            // Bind attribute names.
            for (const VertexBufferInfo& bufferInfo : vertexArrayInfo_.getBufferInfoList()) {
                bufferInfo.loopAttributes([=](const VertexAttributeInfo& info) {
                    program_->bindAttributeLocation(info.getName(), info.getIndex());
                });
            }

            GLuint fragmentOutputIndex = 0;

            // Bind fragment shader outputs in sequential order.
            for (const string& name : outputNameList) {
                program_->bindFragmentDataLocation(name, fragmentOutputIndex++);
            }

            program_->link();
            if (!program_->isLinked()) {
                throw runtime_error(program_->getInfoLog());
            }
        }
        catch (exception& e) {
            delete program_;
            throw;
        }
    }

    ShaderProgram::~ShaderProgram() {
        delete program_;
    }
};


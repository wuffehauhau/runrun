/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    glshader.cpp
 * Created: 2012-08-10
 * Authors: Jani Salo
 */

#include <fstream>
#include <iostream>
#include <memory>

#include "glerror.hpp"
#include "glshader.hpp"

using namespace std;

namespace ruukku {
    GLShader::GLShader(GLuint type) {
        try {
            GLError::clearAll();
            setID(glCreateShader(type));
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteShader(getID());
            throw GLException(string("Couldn't create shader: ") + string(e.what()));
        }
    }

    GLShader::~GLShader() {
        try {
            GLError::clearAll();
            glDeleteShader(getID());
            GLError::throwExceptionOnError();
        } catch (exception& e) {
            cerr << "Couldn't delete shader: " << e.what() << endl;
        }
    };

    GLint GLShader::getType() const {
        GLint type;

        try {
            GLError::clearAll();
            glGetShaderiv(getID(), GL_SHADER_TYPE, &type);
            GLError::throwExceptionOnError();
        } catch (GLException& e) {
            throw GLException(string("Couldn't get shader type: ") + string(e.what()));
        }

        return type;
    }

    void GLShader::compile() const {
       try {
            GLError::clearAll();
            glCompileShader(getID());
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't compile shader: ") + string(e.what()));
        }
    }

    bool GLShader::isCompiled() const {
        GLint status = GL_FALSE;

        try {
            GLError::clearAll();
            glGetShaderiv(getID(), GL_COMPILE_STATUS, &status);
            GLError::throwExceptionOnError();
        } catch (GLException& e) {
            throw GLException(string("Couldn't get shader compilation status: ") + string(e.what()));
        }

        return status == GL_TRUE;
    }

    string GLShader::getInfoLog() const {
        string str;

        try {
            GLError::clearAll();

            int length = 0;
            glGetShaderiv(getID(), GL_INFO_LOG_LENGTH, &length);
            GLError::throwExceptionOnError();

            if (length == 0) return string();

            unique_ptr< GLchar[] > log(new GLchar[length]);
            glGetShaderInfoLog(getID(), length, 0, log.get());
            GLError::throwExceptionOnError();

            str = string(log.get());
        } catch (GLException& e) {
            throw GLException(string("Couldn't get shader infolog: ") + string(e.what()));
        }

        return str;
    }

    void GLShader::setSourceFromString(const string& source) const {
        try {
            GLError::clearAll();

            const GLchar* str    = source.c_str();
            const GLint   length = source.size();

            glShaderSource(getID(), 1, &str, &length);
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't set shader source: ") + string(e.what()));
        }
    }

    void GLShader::setSourceFromStream(istream& is) const {
        string input;

        while(is.good()) {
             string line;
             getline(is, line);
             input.append(line + "\n");
        }

        setSourceFromString(input);
    }

    void GLShader::setSourceFromFile(const string& filename) const {
        ifstream is;

        // Compiling will likely fail if the source isn't opened as text.
        is.open(filename.c_str(), ios::in);
        if (!is.is_open()) throw runtime_error(string("Couldn't open file: ") + string(filename));

        setSourceFromStream(is);
        is.close();
    }
};


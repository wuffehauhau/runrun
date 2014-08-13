/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    objectframelist.cpp
 * Created: 2014-05-30
 * Authors: Jani Salo
 */

#include <cassert>
#include <sstream>

#include "geometry/transformations.hpp"
#include "glyph/glyphset.hpp"

#include "objectframelist.hpp"

using namespace std;
using namespace ruukku;

namespace runrun {
    ObjectFrameList::ObjectFrameList() : name(string("empty")) {
        frameList.push_back(ObjectFrame());
    }

    ObjectFrameList::ObjectFrameList(const string& name, const vector< ObjectFrame >& frameList)
        : name(name), frameList(frameList), totalLength(0)
    {
        assert(frameList.size() != 0);
        for (const ObjectFrame& frame : frameList) {
            totalLength += frame.getLength();
        }

        if (totalLength == 0) totalLength = 1;
    }

    const ObjectFrame& ObjectFrameList::getFrame(const unsigned int time) const {
        const unsigned int targetTime = time % totalLength;
        unsigned int currentTime = 0;

        for (const ObjectFrame& frame : frameList) {
            if (currentTime + frame.getLength() - 1 >= targetTime) return frame;
            currentTime += frame.getLength();
        }

        // How did this happen?
        assert(false);
    }

    ObjectFrameList ObjectFrameList::getTransformed(const std::string& name, const ruukku::GLFloatMat3& tf) const {
        vector< ObjectFrame > newFrameList;
        for (const ObjectFrame& frame : frameList) {
            newFrameList.push_back(frame.getTransformed(tf));
        }

        return ObjectFrameList(name, newFrameList);
    }

    ObjectFrameList ObjectFrameList::constructFromDataFile(const std::string& name, const DataFile& data) {
        vector< ObjectFrame > objectFrameList;

        try {
            bool foundObject = false;

            DataFile::ConstListIt it = data.getFormattedData().cbegin();
            DataFile::ConstListIt end = data.getFormattedData().cend();

            for (; it < end; it++) {
                if (it->compare(name) == 0) {
                    foundObject = true;
                    break;
                }
            }

            if (!foundObject) throw runtime_error("couldn't find object name.");
            const GLFloatVec2 origo = readOrigo(++it, end);

            while (it < end) {
                if (it->compare(string("frame")) == 0) {
                    ObjectFrame frame = readFrame(++it, end, origo);
                    objectFrameList.push_back(frame);
                    continue;
                }

                break;
            }

            if (objectFrameList.size() == 0) throw runtime_error("couldn't find any frames.");
        }
        catch (exception& e) {
            throw runtime_error(
                string("Error constructing object frame list from a data file: ") +
                string(name) +
                string(", ") +
                string(e.what())
            );
        }

        return ObjectFrameList(name, objectFrameList);
    }

    GLFloatVec2 ObjectFrameList::readOrigo(DataFile::ConstListIt& it, const DataFile::ConstListIt& end) {
        if (it >= end) throw runtime_error("unexpected end of file.");
        istringstream iss(*it);

        int x, y;
        iss >> x;
        iss >> y;

        if (iss.fail() || !iss.eof()) throw runtime_error("couldn't read frame origo.");
        it++;

        // Correct origo on return, assuming pixel position at the center of the pixel square.
        return GLFloatVec2(static_cast< GLfloat >(x), static_cast< GLfloat >(y));
    }

    ObjectFrame ObjectFrameList::readFrame(DataFile::ConstListIt& it, const DataFile::ConstListIt& end, const ruukku::GLFloatVec2& origo) {
        unsigned int frameLength;
        frameLength = readFrameLength(it, end);

        GlyphRenderInfo glyphInfo;
        vector< GlyphRenderInfo > glyphList;

        while (readFrameGlyph(it, end, origo, glyphInfo)) {
            glyphList.push_back(glyphInfo);
        }

        return ObjectFrame(frameLength, glyphList);
    }

    unsigned int ObjectFrameList::readFrameLength(DataFile::ConstListIt& it, const DataFile::ConstListIt& end) {
        if (it >= end) throw runtime_error("unexpected end of file.");

        istringstream iss(*it);
        unsigned int frameLength;
        iss >> frameLength;

        if (iss.fail() || !iss.eof()) throw runtime_error("couldn't read frame length.");
        it++; return frameLength;
    }

    bool ObjectFrameList::readFrameGlyph(DataFile::ConstListIt& it, const DataFile::ConstListIt& end, const ruukku::GLFloatVec2& origo, GlyphRenderInfo& glyphInfoOut) {
        if (it >= end) return false;

        DataFile::ConstListIt old = it;
        stringstream ss(*it);

        unsigned int glyphIndex;
        ss >> glyphIndex;

        int x, y;
        ss >> x;
        ss >> y;

        unsigned int rotation;
        ss >> rotation;

        uint32_t color;
        ss << std::hex;
        ss >> color;

        if (ss.fail() || !ss.eof()) {
            it = old;
            return false;
        }

        glyphIndex = glyphIndex % GlyphSet::getGlyphCount();

        GLFloatVec2 xAxis(1.0f, 0.0f);
        GLFloatVec2 yAxis(0.0f, 2.0f);

        array< Transformations::Rotation, 4 > rotationList = {
            Transformations::Rotation::None, Transformations::Rotation::CW90, Transformations::Rotation::CW180, Transformations::Rotation::CW270
        };

        const unsigned int rotationIndex = rotation % 4;

        if (rotation < 4) {
            xAxis = Transformations::RotateAndFlip(xAxis, GLFloatVec2(0.0f, 0.0f), rotationList[rotationIndex], Transformations::Direction::Normal);
            yAxis = Transformations::RotateAndFlip(yAxis, GLFloatVec2(0.0f, 0.0f), rotationList[rotationIndex], Transformations::Direction::Normal);
        }
        else {
            xAxis = Transformations::RotateAndFlip(xAxis, GLFloatVec2(0.0f, 0.0f), rotationList[rotationIndex], Transformations::Direction::MirrorY);
            yAxis = Transformations::RotateAndFlip(yAxis, GLFloatVec2(0.0f, 0.0f), rotationList[rotationIndex], Transformations::Direction::MirrorY);
        }

        // Transform from pixel coordinates to game space.
        GLFloatVec2 glyphPosition(
             0.125f * (static_cast< GLfloat >(x) - origo.x) - yAxis.x,
            -0.125f * (static_cast< GLfloat >(y) - origo.y) - yAxis.y
        );

        GLfloat r = static_cast< GLfloat >((color & 0xFF000000) >> 24) / 255.0f;
        GLfloat g = static_cast< GLfloat >((color & 0xFF0000) >> 16) / 255.0f;
        GLfloat b = static_cast< GLfloat >((color & 0xFF00) >> 8) / 255.0f;
        GLfloat a = static_cast< GLfloat >((color & 0xFF) >> 0) / 255.0f;

        glyphInfoOut = GlyphRenderInfo(
            glyphIndex,
            glyphPosition,
            glyphPosition + xAxis,
            glyphPosition + xAxis + yAxis,
            glyphPosition + yAxis,
            GLFloatRGBA(r, g, b, a)
        );

        it++; return true;
    }
};


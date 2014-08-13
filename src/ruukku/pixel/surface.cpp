/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    surface.cpp
 * Created: 2012-08-09
 * Authors: Jani Salo
 */

#include <fstream>

#include "../pngpp/png.hpp"
#include "surface.hpp"

using namespace std;
using namespace png;

namespace ruukku {
    void Surface::readPNG(istream& is) {
        // Create png++ surface from the stream.
        image< rgba_pixel > img(is);

        // Resize this surface to image dimensions.
        resize(Int2(img.get_width(), img.get_height()));

        // Copy pixels from png++ surface to surface.
        for (size_t y = 0; y < img.get_height(); y++) {
            for (size_t x = 0; x < img.get_width(); x++) {
                (*this)[Int2(x, y)] = RGBA32(
                    img.get_pixel(x, y).red,
                    img.get_pixel(x, y).green,
                    img.get_pixel(x, y).blue,
                    img.get_pixel(x, y).alpha
                );
            }
        }
    }

    void Surface::readPNG(const string& filename) {
        try {
            ifstream ifs;
            ifs.open(filename, ios::in | ios::binary);
            if (!ifs.is_open()) throw runtime_error(string("Couldn't open file."));

            readPNG(ifs);
            ifs.close();
        }
        catch (exception& e) {
            throw runtime_error(string("Couldn't read PNG from file: ") + filename + string(", ") + e.what());
        }
    }

    void Surface::writePNG(ostream& os) const {
        image< rgba_pixel > img(getSize().x, getSize().y);

        // Copy surface pixels to png++ surface.
        for (size_t y = 0; y < img.get_height(); y++) {
            for (size_t x = 0; x < img.get_width(); x++) {
               const RGBA32 pixel = (*this)[Int2(x, y)];
               img.set_pixel(x, y, rgba_pixel(pixel.r, pixel.g, pixel.b, pixel.a));
            }
        }

        // Version 0.2.5 of PNG++ contains a bug in image.hpp, where there are
        // two versions of img::write_stream, causing a crash when called with
        // a _reference_ to an output stream. It appears to be fixed on the
        // development version.
        img.write_stream(os);
    }

    void Surface::writePNG(const string& filename) const {
        try {
            ofstream ofs;
            ofs.open(filename, ios::out | ios::binary);
            if (!ofs.is_open()) throw runtime_error(string("Couldn't open file."));

            writePNG(ofs);
            ofs.close();
        }
        catch (exception& e) {
            throw runtime_error(string("Couldn't write PNG to file: ") + filename + string(", ") + e.what());
        }
    }
};


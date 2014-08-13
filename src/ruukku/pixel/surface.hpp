/*
 * Copyright (C) Jani Salo 2012 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    surface.hpp
 * Created: 2012-08-08
 * Authors: Jani Salo
 */

/*
 * A container for a RGBA surface.
 */

#ifndef RUUKKU_SURFACE_HPP
#define RUUKKU_SURFACE_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "../math/field2.hpp"
#include "rgba32.hpp"

namespace ruukku {
    class Surface : public Field2< RGBA32 > {
        public:
            Surface() {}
            Surface(const Int2& size) : Field2< RGBA32 >(size) {}

        public:
            void readPNG(std::istream& is);
            void readPNG(const std::string& filename);

        public:
            void writePNG(std::ostream& os) const;
            void writePNG(const std::string& filename) const;
    };
};

#endif /* RUUKKU_SURFACE_HPP */


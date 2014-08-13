/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    packing.cpp
 * Created: 2013-01-22
 * Authors: Jani Salo
 */

#include <climits>
#include <GL/glew.h>

#include "packing.hpp"

namespace ruukku {
    // This is assumed in the framework.
    static_assert(CHAR_BIT == 8, "Type char needs to be eight bits in size.");

    // Probably very unnecessary, but it doesn't hurt to check.
    static_assert((sizeof(float)    % RUUKKU_FLOATING_POINT_TYPE_PACKING) == 0, "Type float doesn't seem to pack tightly with current floating point packing value.");
    static_assert((sizeof(double)   % RUUKKU_FLOATING_POINT_TYPE_PACKING) == 0, "Type double doesn't seem to pack tightly with current floating point packing value.");
    static_assert((sizeof(GLfloat)  % RUUKKU_FLOATING_POINT_TYPE_PACKING) == 0, "Type GLfloat doesn't seem to pack tightly with current floating point packing value.");
    static_assert((sizeof(GLdouble) % RUUKKU_FLOATING_POINT_TYPE_PACKING) == 0, "Type GLdouble doesn't seem to pack tightly with current floating point packing value.");
};


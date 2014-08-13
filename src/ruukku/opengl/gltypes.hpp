/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    gltypes.hpp
 * Created: 2013-01-21
 * Authors: Jani Salo
 */

/*
 * Collection of type definitions for use with OpenGL.
 */

#ifndef RUUKKU_GLTYPES_HPP
#define RUUKKU_GLTYPES_HPP

#include <GL/glew.h>

#include "../math/ivec2.hpp"
#include "../math/ivec3.hpp"
#include "../math/vec2.hpp"
#include "../math/vec3.hpp"
#include "../math/pvec3.hpp"
#include "../math/pvec4.hpp"
#include "../math/mat3.hpp"
#include "../math/mat4.hpp"
#include "../math/rgb.hpp"
#include "../math/rgba.hpp"

namespace ruukku {
    typedef IVec2< GLint >  GLIntVec2;
    typedef IVec2< GLuint > GLUIntVec2;
    typedef IVec3< GLint >  GLIntVec3;
    typedef IVec3< GLuint > GLUIntVec3;

    typedef Vec2< GLfloat >  GLFloatVec2;
    typedef Vec2< GLdouble > GLDoubleVec2;
    typedef Vec3< GLfloat >  GLFloatVec3;
    typedef Vec3< GLdouble > GLDoubleVec3;

    typedef PVec3< GLfloat >  GLFloatPVec3;
    typedef PVec3< GLdouble > GLDoublePVec3;
    typedef PVec4< GLfloat >  GLFloatPVec4;
    typedef PVec4< GLdouble > GLDoublePVec4;

    typedef Mat3< GLfloat >  GLFloatMat3;
    typedef Mat3< GLdouble > GLDoubleMat3;
    typedef Mat4< GLfloat >  GLFloatMat4;
    typedef Mat4< GLdouble > GLDoubleMat4;

    typedef RGB  < GLfloat >  GLFloatRGB;
    typedef RGB  < GLdouble > GLDoubleRGB;
    typedef RGBA < GLfloat >  GLFloatRGBA;
    typedef RGBA < GLdouble > GLDoubleRGBA;
};

#endif /* RUUKKU_GLTYPES_HPP */


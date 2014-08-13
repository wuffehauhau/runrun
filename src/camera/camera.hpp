/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    camera.hpp
 * Created: 2014-06-05
 * Authors: Jani Salo
 */

/*
 * Scene camera.
 */

#ifndef RUNRUN_CAMERA_HPP
#define RUNRUN_CAMERA_HPP

#include "ruukku/opengl/gltypes.hpp"
#include "geometry/boundingbox.hpp"
#include "view.hpp"

namespace runrun {
    class Camera {
        public:
            static constexpr GLfloat getNearClipPlane() { return  1.0f / 16.0f; }
            static constexpr GLfloat getFarClipPlane()  { return 16.0f; }

        public:
            Camera() {}
            Camera(
                const ruukku::GLFloatVec2& target,
                const ruukku::GLFloatVec2& up,
                const GLfloat zoom,
                const GLfloat aspect
            );

            ruukku::GLFloatVec2 getTarget() const;
            ruukku::GLFloatVec2 getUp()     const;
            GLfloat             getZoom()   const;
            GLfloat             getAspect() const;

            void setTarget (const ruukku::GLFloatVec2& target);
            void setUp     (const ruukku::GLFloatVec2& up);
            void setZoom   (const GLfloat zoom);
            void setAspect (const GLfloat aspect);

            ruukku::GLFloatMat3 getRotationMatrix3()  const;
            ruukku::GLFloatMat4 getRotationMatrix4()  const;
            ruukku::GLFloatMat4 getViewMatrix()       const;
            ruukku::GLFloatMat4 getProjectionMatrix() const;

            void clip(const BoundingBox& box);

            BoundingBox getBoundingBox() const;
            View getView() const;

        private:
            ruukku::GLFloatVec2 target;
            ruukku::GLFloatVec2 up;
            GLfloat             zoom;
            GLfloat             aspect;
    };
};

#endif /* RUNRUN_CAMERA_HPP */


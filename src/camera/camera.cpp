/*
 * Copyright (C) Jani Salo 2014 -
 * All rights reserved unless otherwise stated.
 *
 * runrun
 *
 * File:    camera.cpp
 * Created: 2014-06-05
 * Authors: Jani Salo
 */

#include "camera.hpp"
#include <iostream>

using namespace std;
using namespace ruukku;

namespace runrun {
    Camera::Camera(
        const GLFloatVec2& target,
        const GLFloatVec2& up,
        const GLfloat zoom,
        const GLfloat aspect
    ) : target(target), up(up), zoom(zoom), aspect(aspect) {}

    GLFloatVec2 Camera::getTarget() const { return target; }
    GLFloatVec2 Camera::getUp()     const { return up;     }
    GLfloat     Camera::getZoom()   const { return zoom;   }
    GLfloat     Camera::getAspect() const { return aspect; }

    void Camera::setTarget (const GLFloatVec2& target) { this->target = target; }
    void Camera::setUp     (const GLFloatVec2& up)     { this->up     = up;     }
    void Camera::setZoom   (const GLfloat      zoom)   { this->zoom   = zoom;   }
    void Camera::setAspect (const GLfloat      aspect) { this->aspect = aspect; }

    GLFloatMat3 Camera::getRotationMatrix3() const {
        const GLFloatVec2 yAxis = up.getNormal();
        const GLFloatVec2 xAxis(yAxis.y, -yAxis.x);

        return GLFloatMat3(
            xAxis.x, xAxis.y, 0.0f,
            yAxis.x, yAxis.y, 0.0f,
            0.0f,    0.0f,    1.0f
        );
    }

    GLFloatMat4 Camera::getRotationMatrix4() const {
        const GLFloatMat3 rot = getRotationMatrix3();

        return GLFloatMat4(
            rot[GLFloatMat3::X0], rot[GLFloatMat3::Y0], rot[GLFloatMat3::W0], 0.0f,
            rot[GLFloatMat3::X1], rot[GLFloatMat3::Y1], rot[GLFloatMat3::W1], 0.0f,
            rot[GLFloatMat3::X2], rot[GLFloatMat3::Y2], rot[GLFloatMat3::W2], 0.0f,
            0.0f,                 0.0f,                 0.0f,                 1.0f
        );
    }

    GLFloatMat4 Camera::getViewMatrix() const {
        const GLFloatMat4 rotation    = getRotationMatrix4();
        const GLFloatMat4 translation = GLFloatMat4::getTranslation(target.x, target.y, 1.0f);
        const GLFloatMat4 scaling     = GLFloatMat4::getScaling(1.0f / zoom, 1.0f / zoom, 1.0f);

        // I hope I got this right.
        return (translation * rotation * scaling).getInverse();
    }

    GLFloatMat4 Camera::getProjectionMatrix() const {
        return GLFloatMat4::getOrthoProjection(
            -0.5f * aspect,
             0.5f * aspect,
            -0.5f,
             0.5f,
            getNearClipPlane(),
            getFarClipPlane()
        );
    }

    void Camera::clip(const BoundingBox& box) {
        const BoundingBox cameraBox = getBoundingBox();

        if (box.getSize().x < cameraBox.getSize().x) {
            target.x = 0.5f * (box.min.x + box.max.x);
        }
        else {
            if      (cameraBox.min.x < box.min.x) target.x += box.min.x - cameraBox.min.x;
            else if (cameraBox.max.x > box.max.x) target.x += box.max.x - cameraBox.max.x;
        }

        if (box.getSize().y < cameraBox.getSize().y) {
            target.y = 0.5f * (box.min.y + box.max.y);
        }
        else {
            if      (cameraBox.min.y < box.min.y) target.y += box.min.y - cameraBox.min.y;
            else if (cameraBox.max.y > box.max.y) target.y += box.max.y - cameraBox.max.y;
        }
    }

    BoundingBox Camera::getBoundingBox() const {
        const GLFloatMat3 rotation = getRotationMatrix3();
        const GLfloat inverseZoom = 1.0f / zoom;

        const GLFloatVec2 origo = target + rotation.transform(inverseZoom * GLFloatVec2(-0.5f * aspect, -0.5f));
        const GLFloatVec2 uAxis = rotation.transform(inverseZoom * GLFloatVec2(aspect, 0.0f));
        const GLFloatVec2 vAxis = rotation.transform(inverseZoom * GLFloatVec2(0.0f, 1.0f));

        static vector< GLFloatVec2 > boxVertexCache;

        boxVertexCache.clear();
        boxVertexCache = {{origo, origo + uAxis, origo + vAxis, origo + uAxis + vAxis}};

        return BoundingBox(boxVertexCache);
    }

    View Camera::getView() const {
        const GLfloat inverseZoom = 1.0f / zoom;

        Line lLine(inverseZoom * GLFloatVec2(-0.5f * aspect, 0.0f), GLFloatVec2(-1.0f,  0.0f));
        Line rLine(inverseZoom * GLFloatVec2( 0.5f * aspect, 0.0f), GLFloatVec2( 1.0f,  0.0f));
        Line bLine(inverseZoom * GLFloatVec2( 0.0f,         -0.5f), GLFloatVec2( 0.0f, -1.0f));
        Line tLine(inverseZoom * GLFloatVec2( 0.0f,          0.5f), GLFloatVec2( 0.0f,  1.0f));

        const GLFloatMat3 rotation = getRotationMatrix3();

        lLine = lLine.getTransformed(rotation); lLine.p += target;
        rLine = rLine.getTransformed(rotation); rLine.p += target;
        bLine = bLine.getTransformed(rotation); bLine.p += target;
        tLine = tLine.getTransformed(rotation); tLine.p += target;

        return View(lLine, rLine, bLine, tLine);
    }
};


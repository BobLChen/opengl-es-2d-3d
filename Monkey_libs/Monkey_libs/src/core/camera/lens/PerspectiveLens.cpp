//
//  PerspectiveLens.cpp
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/camera/lens/PerspectiveLens.h"
#include "platform/PlatformMacros.h"
#include "core/geom/mmath.h"

NS_MONKEY_BEGIN

PerspectiveLens::PerspectiveLens() :
LensBase(),
_near(0.1f),
_far(3000.0f),
_zoom(1.0f),
_fieldOfView(75.0f),
_aspectRatio(1.3f)
{
    
}

PerspectiveLens::~PerspectiveLens() {
    
}

float PerspectiveLens::getFar() const {
    return _far;
}

void PerspectiveLens::setFar(float value) {
    if (_far == value) {
        return;
    }
    _far = value;
    invalidProjection();
}

float PerspectiveLens::getNear() const {
    return _near;
}

void PerspectiveLens::setNear(float value) {
    if (_near == value) {
        return;
    }
    _near = value;
    invalidProjection();
}

float PerspectiveLens::getZoom() {
    return _zoom;
}

void PerspectiveLens::setZoom(float value) {
    if (_zoom == value) {
        return;
    }
    
    _zoom = value;
    _fieldOfView = atanf(_zoom) * 360 / PI;
    
    invalidProjection();
}

float PerspectiveLens::getFieldOfView() const {
    return _fieldOfView;
}

void PerspectiveLens::setFieldOfView(float value) {
    if (_fieldOfView == value) {
        return;
    }
    _fieldOfView = value;
    _zoom        = tanf(_fieldOfView * PI / 360);
    invalidProjection();
}

void PerspectiveLens::updateProjectionMatrix() {
    
    _aspectRatio = _viewport.getWidth() / _viewport.getHeight();
    
    float yMax = _near / _zoom;
    float xMax = yMax * _aspectRatio;
    
    _projection.identity();
    _projection.rawData[0]  = _near / xMax;
    _projection.rawData[5]  = _near / yMax;
    _projection.rawData[10] = _far / (_far - _near);
    _projection.rawData[11] = 1.0f;
    _projection.rawData[14] = -_near * _projection.rawData[10];
    _projection.rawData[1] = _projection.rawData[2] = _projection.rawData[3] = _projection.rawData[4] =
    _projection.rawData[6] = _projection.rawData[7] = _projection.rawData[8] = _projection.rawData[9] =
    _projection.rawData[12]= _projection.rawData[13]= _projection.rawData[15]= 0.0f;
    
    LensBase::updateProjectionMatrix();
}

void PerspectiveLens::getPointDir(float x, float y, const monkey::Matrix3D &world, monkey::Vector3D &dest) {
    
}

bool PerspectiveLens::isInView(const monkey::Vector3D &point, float radius, bool viewSpace) {
    return true;
}


NS_MONKEY_END
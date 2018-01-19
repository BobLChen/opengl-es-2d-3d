//
//  OrthographicLens.cpp
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/camera/lens/OrthographicLens.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

OrthographicLens::OrthographicLens() :
LensBase(),
_left(0.0f),
_right(0.0f),
_top(0.0f),
_bottom(0.0f),
_near(-10.0f),
_far(100.0f)
{
}

OrthographicLens::~OrthographicLens() {
    
}

void OrthographicLens::setViewport(float x, float y, float width, float height) {
    LensBase::setViewport(x, y, width, height);
    init(0, width, 0, height, _near, _far);
}

void OrthographicLens::setNear(float value) {
    if (_near == value) {
        return;
    }
    _near = value;
    invalidProjection();
}

void OrthographicLens::setFar(float value) {
    if (_far == value) {
        return;
    }
    _far = value;
    invalidProjection();
}

float OrthographicLens::getNear() const {
    return _near;
}

float OrthographicLens::getFar() const {
    return _far;
}

void OrthographicLens::setLeft(float value) {
    if (_left == value) {
        return;
    }
    _left = value;
    invalidProjection();
}

float OrthographicLens::getLeft() const {
    return _left;
}

void OrthographicLens::setRight(float value) {
    if (_right == value) {
        return;
    }
    _right = value;
    invalidProjection();
}

float OrthographicLens::getRight() const {
    return _right;
}

void OrthographicLens::setTop(float value) {
    if (_top == value) {
        return;
    }
    _top = value;
    invalidProjection();
}

float OrthographicLens::getTop() const {
    return _top;
}

void OrthographicLens::setBottom(float value) {
    if (_bottom == value) {
        return;
    }
    _bottom = value;
    invalidProjection();
}

float OrthographicLens::getBottom() const {
    return _bottom;
}

void OrthographicLens::init(float left, float right, float bottom, float top, float near, float far) {
    _left   = left;
    _right  = right;
    _bottom = bottom;
    _top    = top;
    _near   = near;
    _far    = far;
    invalidProjection();
}

void OrthographicLens::updateProjectionMatrix() {
    
    float scaleX = 2 / (_right - _left);
    float scaleY = 2 / (_top - _bottom);
    float scaleZ = 1 / (_far - _near);
    float offseX = (-0.5 * (_right + _left)) * scaleX;
    float offseY = (-0.5 * (_top + _bottom)) * scaleY;
    float offseZ = _near * scaleZ;
    
    _projection.rawData[0] = scaleX;
    _projection.rawData[5] = scaleY;
    _projection.rawData[10]= scaleZ;
    _projection.rawData[12]= offseX;
    _projection.rawData[13]= offseY;
    _projection.rawData[14]= -offseZ;
    _projection.rawData[1] = _projection.rawData[2] = _projection.rawData[4] = _projection.rawData[6] =
    _projection.rawData[9] = _projection.rawData[3] = _projection.rawData[7] = _projection.rawData[11]= 0.0f;
    _projection.rawData[15] = 1.0f;
    
    LensBase::updateProjectionMatrix();
}

NS_MONKEY_END
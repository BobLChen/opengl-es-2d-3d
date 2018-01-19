//
//  Camera3D.cpp
//  Monkey_libs
//
//  Created by Neil on 4/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/camera/Camera3D.h"
#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

const std::string Camera3D::LENS_CHANGE_EVENT = "LENS_CHANGE_EVENT";
Event Camera3D::_lensChangeEvent = Event(LENS_CHANGE_EVENT, false);

Camera3D::Camera3D(LensBase *lens) : Pivot3D(), _lens(lens) {
    _viewProjection.identity();
}

Camera3D::~Camera3D() {
    if (_lens) {
        delete _lens;
        _lens  = nullptr;
    }
}

void Camera3D::setLens(LensBase *lens) {
    if (_lens) {
        delete _lens;
        _lens = nullptr;
    }
    _lens = lens;
}

LensBase* Camera3D::getLens() const {
    return _lens;
}

Matrix3D& Camera3D::getProjection() {
    return _lens->getProjection();
}

void Camera3D::getPointDir(float x, float y, monkey::Vector3D &dest) {
    
}

bool Camera3D::isInView(const monkey::Vector3D &point, float radius, bool viewSpace) {
    return _lens->isInView(point, radius, viewSpace);
}

Matrix3D& Camera3D::getViewProjection() {
    _viewProjection.identity();
    _viewProjection.append(getView());
    _viewProjection.append(_lens->getProjection());
    return _viewProjection;
}

Matrix3D& Camera3D::getView() {
    return getInvWorld();
}

void Camera3D::setViewport(float x, float y, float width, float height) {
    _lens->setViewport(x, y, width, height);
}

NS_MONKEY_END

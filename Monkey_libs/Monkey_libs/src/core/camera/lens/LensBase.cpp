//
//  LensBase.cpp
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/camera/lens/LensBase.h"
#include "core/event/Event.h"

NS_MONKEY_BEGIN

const std::string LensBase::PROJECTION_UPDATE_EVNET = "PROJECTION_UPDATE_EVNET";

Event LensBase::_projectionUpdateEvent(PROJECTION_UPDATE_EVNET, false);

LensBase::LensBase() : EventDispatcher(), _dirty(true) {
    _projection.identity();
    _viewport.set(0, 0, 0, 0);
}

LensBase::~LensBase() {
    
}

Matrix3D& LensBase::getProjection() {
    if (_dirty) {
        updateProjectionMatrix();
    }
    return _projection;
}

void LensBase::updateProjectionMatrix() {
    _dirty = false;
    if (hasEventListener(PROJECTION_UPDATE_EVNET)) {
        _projectionUpdateEvent.reset();
        dispatchEvent(_projectionUpdateEvent);
    }
}

bool LensBase::isInView(const monkey::Vector3D &point, float radius, bool viewSpace) {
    
    return true;
}

void LensBase::getPointDir(float x, float y, const monkey::Matrix3D &world, monkey::Vector3D &dest) {
    
}

void LensBase::setViewport(float x, float y, float width, float height) {
    if (_viewport.getX() == x && _viewport.getY() == y && _viewport.getWidth() == width && _viewport.getHeight() == height) {
        return;
    }
    _viewport.set(x, y, width, height);
    invalidProjection();
}

void LensBase::invalidProjection() {
    _dirty = true;
}

NS_MONKEY_END
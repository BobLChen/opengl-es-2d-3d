//
//  Scene.cpp
//  Monkey_libs
//
//  Created by Neil on 3/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "platform/PlatformConfig.h"

#include "core/scene/Scene.h"
#include "core/camera/Camera3D.h"
#include "core/camera/lens/OrthographicLens.h"
#include "core/event/TouchEvent.h"
#include "core/event/KeyboardEvent.h"

#include "App.h"

#include <algorithm>

NS_MONKEY_BEGIN

const std::string Scene::RENDER_EVENT       = "RENDER_EVENT";
const std::string Scene::PAUSED_EVENT       = "PAUSED_EVENT";
const std::string Scene::POSTRENDER_EVENT   = "POSTRENDER_EVENT";
const std::string Scene::PRERENDER_EVENT    = "PRERENDER_EVENT";
const std::string Scene::SOFT_MODE_EVENT    = "SOFT_MODE_EVENT";

Event Scene::_postRenderEvent = Event(POSTRENDER_EVENT,  false);
Event Scene::_preRenderEvent  = Event(PRERENDER_EVENT,   false);
Event Scene::_pausedEvent     = Event(PAUSED_EVENT,      false);
Event Scene::_renderEvent     = Event(RENDER_EVENT,      false);
Event Scene::_softEvent       = Event(SOFT_MODE_EVENT,   false);

Scene::Scene() :
Pivot3D(),
skipRender(false),
_renderIndex(0),
_renderLength(0),
_frameRate(0),
_tick(0),
_paused(false),
_camera(nullptr),
_antialias(0),
_updated(false),
_updateIndex(0),
_updateLength(0)
{
    _camera        = new Camera3D(new OrthographicLens());
    _defaultCamera = _camera;
}

/**
 *  TODO:dispose scene
 */
Scene::~Scene() {
    _renderList.clear();
    _updateList.clear();
}

void Scene::setBackgroundColor(unsigned int color) {
    clearColor.z = (color & 0xFF) / 0xFF;
    clearColor.y = ((color >> 8) & 0xFF) / 0xFF;
    clearColor.x = ((color >> 16) & 0xFF) / 0xFF;
}

unsigned int Scene::getBackgroundColor() const {
    return (int(clearColor.x * 0xFF) << 16) | (int(clearColor.y * 0xFF) << 8) | int(clearColor.z * 0xFF);
}

void Scene::setViewport(float x, float y, float width, float height) {
    if (_viewPort.getX() == x && _viewPort.getY() == y && _viewPort.getWidth() == width && _viewPort.getHeight() == height) {
        return;
    }
    _viewPort.set(x, y, width, height);
    if (_camera) {
        _camera->setViewport(x, y, width, height);
    }
}

Camera3D* Scene::getCamera() const {
    return _camera;
}

void Scene::setCamera(Camera3D* camera) {
    _camera = camera;
}

float Scene::getFrameRate() const {
    return _frameRate;
}

void Scene::setFrameRate(float value) {
    _frameRate = value;
    _tick      = 1.0f / _frameRate;
}

void Scene::enterScene(float advancedTime) {
    
    _enterFrameEvent.reset();
    dispatchEvent(_enterFrameEvent);
    
    if (!_paused) {
        update(advancedTime, true);
        _updated = true;
    } else {
        _pausedEvent.reset();
        dispatchEvent(_pausedEvent);
    }
    
    setupFrame(_camera);
    
    if (_updated) {
        _updated = false;
        if (!_paused) {
            skipRender = false;
            // prerender
            _preRenderEvent.reset();
            dispatchEvent(_preRenderEvent);
            // render
            if (!skipRender) {
                render(_camera, false);
            }
            // posrender
            _postRenderEvent.reset();
            dispatchEvent(_postRenderEvent);
        }
    }
    
    _exitFrameEvent.reset();
    dispatchEvent(_exitFrameEvent);
    
}

void Scene::setupFrame(Camera3D *camera) {
    App::getInstance()->drawcalls = 0;
    App::getInstance()->triangles = 0;
    App::getInstance()->vertices  = 0;
    App::getInstance()->view.copyFrom(camera->getView());
    App::getInstance()->projection.copyFrom(camera->getProjection());
    App::getInstance()->viewProjection.copyFrom(App::getInstance()->view);
    App::getInstance()->viewProjection.append(App::getInstance()->projection);
    
}

void Scene::draw(bool includeChildren, Material3D* shader) {
    
}

void Scene::update(float advancedTime, bool includeChildren) {
    _updateEvent.reset();
    dispatchEvent(_updateEvent);
    
    _updateLength = (int)_updateList.size();
    _updateIndex  = 0;
    
    while (_updateIndex < _updateLength) {
        _updateList[_updateIndex]->update(advancedTime, true);
        _updateIndex++;
    }
}

void Scene::render(Camera3D* camera, bool clearDepth) {
    _renderLength = (int)_renderList.size();
    if (_renderLength == 0 || !_visible) {
        return;
    }
    _renderIndex  = 0;
    bool doRender = false;
    if (!_paused) {
        doRender = true;
        _renderEvent.reset();
        dispatchEvent(_renderEvent);
    }
    
    if (clearDepth) {
#if CC_TARGET_PLATFORM == CC_TARGET_OS_IPHONE || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        glClearDepthf(1.0);
#else
        glClearDepth(1.0);
#endif
    }
    
    if (doRender) {
        while (_renderIndex < _renderLength) {
            _renderList[_renderIndex]->draw(false);
            _renderIndex++;
        }
    }
    
}

void Scene::setParent(Pivot3D *parent) {
    
}

Pivot3D* Scene::getParent() {
    return nullptr;
}

void Scene::resume() {
    _paused = false;
}

void Scene::pause() {
    _paused = true;
}

bool Scene::paused() {
    return _paused;
}

int Scene::getAntialias() {
    return _antialias;
}

void Scene::setAntialias(int value) {
    _antialias = value;
}

const Rectangle& Scene::getViewPort() {
    return _viewPort;
}

std::vector<Pivot3D*>& Scene::getRenderList() {
    return _renderList;
}

std::vector<Pivot3D*>& Scene::getUpdateList() {
    return _updateList;
}

void Scene::removeFromScene(Pivot3D *pivot, bool update, bool render) {
    if (update && _updateList.size()) {
        auto iter = std::find(_updateList.begin(), _updateList.end(), pivot);
        _updateList.erase(iter);
    }
    
    if (render && _renderList.size()) {
        auto iter = std::find(_renderList.begin(), _renderList.end(), pivot);
        if (iter != _renderList.end()) {
            _renderList.erase(iter);
        }
    }
}

void Scene::addToScene(Pivot3D *pivot, bool update, bool render) {
    if (pivot->isLoock()) {
        return;
    }
    
    if (update) {
        auto iter = std::find(_updateList.begin(), _updateList.end(), pivot);
        if (iter == _updateList.end()) {
            _updateList.push_back(pivot);
        }
    }
    
    if (render) {
        auto iter = std::find(_renderList.begin(), _renderList.end(), pivot);
        if (iter != _renderList.end()) {
            return;
        }
        int left  = 0;
        int right = (int)_renderList.size();
        int value = pivot->getLayer();
        int middle= 0;
        
        while (left < right) {
            middle = (left + right) >> 1;
            if (_renderList[middle]->getLayer() == value) {
                break;
            }
            if (value > _renderList[middle]->getLayer()) {
                middle++;
                left  = middle;
            } else {
                right = middle;
            }
        }
        _renderList.insert(_renderList.begin() + middle, pivot);
    }
}

void Scene::handleTouchesBegan(monkey::TouchEvent &event) {
    dispatchEvent(event);
}

void Scene::handleTouchesEnd(monkey::TouchEvent &event) {
    dispatchEvent(event);
}

void Scene::handleTouchMove(monkey::TouchEvent &event) {
    dispatchEvent(event);
}

void Scene::handleMouseWheel(monkey::TouchEvent &event) {
    dispatchEvent(event);
}

void Scene::handleKeyDown(monkey::KeyboardEvent &event) {
    dispatchEvent(event);
}

void Scene::handleKeyUp(monkey::KeyboardEvent &event) {
    dispatchEvent(event);
}

void Scene::setLayerSortMode(int layer, SortMode mode) {
    
}

void Scene::freeMemory() {
    
}

void Scene::dispose() {
    
}

NS_MONKEY_END

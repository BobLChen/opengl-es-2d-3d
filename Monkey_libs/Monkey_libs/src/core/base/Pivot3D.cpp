//
//  Pivot3D.cpp
//  Monkey_libs
//
//  Created by Neil on 30/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/base/Pivot3D.h"
#include "core/scene/Scene.h"
#include "platform/PlatformMacros.h"

#include <algorithm>

NS_MONKEY_BEGIN

const std::string Pivot3D::ADDED_EVENT              = "ADDED_EVENT";
const std::string Pivot3D::REMOVED_EVENT            = "REMOVED_EVENT";
const std::string Pivot3D::ADDED_TO_SCENE_EVENT     = "ADDED_TO_SCENE_EVENT";
const std::string Pivot3D::REMOVED_FROM_SCENE_EVENT = "REMOVED_FROM_SCENE_EVENT";
const std::string Pivot3D::ANIMATION_COMPLETE_EVENT = "ANIMATION_COMPLETE_EVENT";
const std::string Pivot3D::ENTER_FRAME_EVENT        = "ENTER_FRAME_EVENT";
const std::string Pivot3D::EXIT_FRAME_EVENT         = "EXIT_FRAME_EVENT";
const std::string Pivot3D::ENTER_DRAW_EVENT         = "ENTER_DRAW_EVENT";
const std::string Pivot3D::EXIT_DRAW_EVENT          = "EXIT_DRAW_EVENT";
const std::string Pivot3D::UPDATE_TRANSFORM_EVENT   = "UPDATE_TRANSFORM_EVENT";
const std::string Pivot3D::UPLOAD_EVENT             = "UPLOAD_EVENT";
const std::string Pivot3D::DOWN_LOAD_EVENT          = "DOWN_LOAD_EVENT";
const std::string Pivot3D::UPDATE_EVENT             = "UPDATE_EVENT";

Event Pivot3D::_addedEvent               = Event(ADDED_EVENT, false);
Event Pivot3D::_removedEvent             = Event(REMOVED_EVENT, false);
Event Pivot3D::_addedToSceneEvent        = Event(ADDED_TO_SCENE_EVENT, false);
Event Pivot3D::_removedFromSceneEvent    = Event(REMOVED_FROM_SCENE_EVENT, false);
Event Pivot3D::_animationCompleteEvent   = Event(ANIMATION_COMPLETE_EVENT, false);
Event Pivot3D::_enterFrameEvent          = Event(ENTER_FRAME_EVENT, false);
Event Pivot3D::_exitFrameEvent           = Event(EXIT_FRAME_EVENT, false);
Event Pivot3D::_enterDrawEvent           = Event(ENTER_DRAW_EVENT, false);
Event Pivot3D::_exitDrawEvent            = Event(EXIT_DRAW_EVENT, false);
Event Pivot3D::_updateTransformEvent     = Event(UPDATE_TRANSFORM_EVENT, false);
Event Pivot3D::_uploadEvent              = Event(UPLOAD_EVENT, false);
Event Pivot3D::_downLoadEvent            = Event(DOWN_LOAD_EVENT, false);
Event Pivot3D::_updateEvent              = Event(UPDATE_EVENT, false);

Vector3D Pivot3D::_tempVec30 = Vector3D(0.0f, 0.0f, 0.0f, 1.0f);
Vector3D Pivot3D::_tempVec31 = Vector3D(0.0f, 0.0f, 0.0f, 1.0f);
Vector2D Pivot3D::_tempVec20 = Vector2D(0.0f, 0.0f);
Vector2D Pivot3D::_tempVec21 = Vector2D(0.0f, 0.0f);

Pivot3D::Pivot3D() : EventDispatcher(),
_fps(60.0f),
_fpsSpeed(1.0f / 60.0f),
_frameSpeed(1.0f),
_layer(0),
_dirty(true),
_dirtyInv(true),
_lock(false),
_visible(true),
_inScene(false),
_animationEnabled(false),
_from(0.0f),
_to(0.0f),
_currentFrame(0.0f),
_laseFrame(0.0f),
_isPlaying(false),
_updatable(false),
_drable(false),
_parent(nullptr),
_scene(nullptr),
name("Pivot3D")
{
    _children.clear();
    _components.clear();
    _transform.identity();
    _world.identity();
    _invWorld.identity();
}

Pivot3D::~Pivot3D() {
    _components.clear();
    _children.clear();
}

float Pivot3D::getFps() const {
    return _fps;
}

void Pivot3D::setFps(float value) {
    _fps = value;
    _fpsSpeed = 1.0f / _fps;
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->setFps(value);
    }
}

float Pivot3D::getFpsSpeed() const {
    return _fpsSpeed;
}

int Pivot3D::getLayer() const {
    return _layer;
}

bool Pivot3D::isLoock() const {
    return _lock;
}

void Pivot3D::setLoock(bool value) {
    _lock = value;
    
}

void Pivot3D::setVisiable(bool value) {
    _visible = value;
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->setVisiable(value);
    }
}

bool Pivot3D::getVisiable() const {
    return _visible;
}

bool Pivot3D::getInScene() const {
    return _inScene;
}

bool Pivot3D::isAnimationEnabled() const {
    return _animationEnabled;
}

bool Pivot3D::isMouseEnabled() const {
    return _mouseEnabled;
}

void Pivot3D::enableMouse(bool value) {
    _mouseEnabled = value;
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->enableMouse(value);
    }
}

void Pivot3D::enableAnimation(bool value) {
    _animationEnabled = value;
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->enableAnimation(value);
    }
}

void Pivot3D::setFrameSpeed(float value) {
    _frameSpeed = value;
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->setFrameSpeed(value);
    }
}

Matrix3D& Pivot3D::getTransform() {
    return _transform;
}

void Pivot3D::setTransform(const Matrix3D &mt) {
    _transform.copyFrom(mt);
    updateTransforms(true);
}

bool Pivot3D::getDirty() {
    return _dirty;
}

void Pivot3D::setDirty(bool value) {
    _dirty = value;
}

bool Pivot3D::addComponent(IComponent *component) {
    
    if (component->added(this)) {
        _components.push_back(component);
        return true;
    } else {
        return false;
    }
    
    return true;
}

bool Pivot3D::removeComponent(IComponent *component) {
    if (component->removed()) {
        auto iter = std::find(_components.begin(), _components.end(), component);
        if (iter != _components.end()) {
            _components.erase(iter);
            return true;
        }
        return false;
    } else {
        return false;
    }
}

void Pivot3D::upload(bool includeChildren) {
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->upload(includeChildren);
        }
    }
}

void Pivot3D::download(bool includeChildren) {
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->download(includeChildren);
        }
    }
}

void Pivot3D::copyFrom(Pivot3D *pivot) {
    
}

void Pivot3D::setPosition(float x, float y, float z, float smooth, bool local) {
    _tempVec30.setTo(x, y, z, 1.0f);
    if (local == false && _parent) {
        _parent->globalToLocal(_tempVec30, _tempVec30);
    }
    Matrix3DUtils::setPosition(_transform, _tempVec30.x, _tempVec30.y, _tempVec30.z, smooth);
    updateTransforms(true);
}

void Pivot3D::setPosition(const Vector3D &pos, float smooth, bool local) {
    _tempVec30.copyFrom(pos);
    _tempVec30.w = 1.0f;
    if (local == false && _parent) {
        _parent->globalToLocal(_tempVec30, _tempVec30);
    }
    Matrix3DUtils::setPosition(_transform, _tempVec30.x, _tempVec30.y, _tempVec30.z, smooth);
    updateTransforms(true);
}

void Pivot3D::getPosition(Vector3D &dest, bool local) {
    Matrix3DUtils::getPosition(local ? _transform : getWorld(), dest);
}

void Pivot3D::setScale(float x, float y, float z, float smooth) {
    Matrix3DUtils::setScale(_transform, x, y, z, smooth);
    updateTransforms();
}

void Pivot3D::setScale(const Vector3D &scale, float smooth) {
    Matrix3DUtils::setScale(_transform, scale.x, scale.y, scale.z, smooth);
    updateTransforms();
}

void Pivot3D::getScale(Vector3D &dest, bool local) {
    Matrix3DUtils::getScale(local ? _transform : getWorld(), dest);
}

float Pivot3D::getRotationX(bool local) {
    getFront(_tempVec30);
    return atan2f(_tempVec30.y, _tempVec30.z) * 180.0f / PI;
}

float Pivot3D::getRotationY(bool local) {
    getFront(_tempVec30);
    return atan2f(_tempVec30.x, _tempVec30.z) * 180.0f / PI;
}

/**
 *  TODO:实现rotationZ。目前还未做z的逻辑
 *  @param local local
 *  @return
 */
float Pivot3D::getRotationZ(bool local) {
    return 0.0f;
}

void Pivot3D::setRoatation(const Vector3D &rotation) {
    setRotation(rotation.x, rotation.y, rotation.z);
}

void Pivot3D::setRotation(float x, float y, float z) {
    Matrix3DUtils::setRotation(_transform, x, y, z);
    updateTransforms(true);
}

void Pivot3D::getRotation(Vector3D &dest, bool local) {
    Matrix3DUtils::getRotation(local ? _transform : getWorld(), dest);
}

void Pivot3D::lookAt(float x, float y, float z, const Vector3D &up, float smooth) {
    Matrix3DUtils::lookAt(_transform, x, y, z, up, smooth);
    updateTransforms();
}

void Pivot3D::lookAt(const Vector3D &target, const Vector3D &up, float smooth) {
    lookAt(target.x, target.y, target.z, up, smooth);
}

void Pivot3D::setOrientation(float x, float y, float z, const Vector3D &up, float smooth) {
    _tempVec30.setTo(x, y, z, 1.0f);
    Matrix3DUtils::setOrientation(_transform, _tempVec30, up, smooth);
    updateTransforms();
}

void Pivot3D::setOrientation(const Vector3D &dir, const Vector3D &up, float smooth) {
    Matrix3DUtils::setOrientation(_transform, dir, up, smooth);
    updateTransforms();
}

void Pivot3D::rotateX(float angle, bool local, Vector3D *pivotPoint) {
    Matrix3DUtils::rotateX(_transform, angle, local, pivotPoint);
    updateTransforms();
}

void Pivot3D::rotateY(float angle, bool local, Vector3D *pivotPoint) {
    Matrix3DUtils::rotateY(_transform, angle, local, pivotPoint);
    updateTransforms();
}

void Pivot3D::rotateZ(float angle, bool local, Vector3D *pivotPoint) {
    Matrix3DUtils::rotateZ(_transform, angle, local, pivotPoint);
    updateTransforms();
}

void Pivot3D::rotateAxis(float angle, const Vector3D &axis, Vector3D *pivotPoint) {
    Matrix3DUtils::rotateAxis(_transform, angle, axis, pivotPoint);
    updateTransforms();
}

void Pivot3D::setScaleX(float value) {
    Matrix3DUtils::scaleX(_transform, value);
    updateTransforms();
}

void Pivot3D::setScaleY(float value) {
    Matrix3DUtils::scaleY(_transform, value);
    updateTransforms();
}

void Pivot3D::setScaleZ(float value) {
    Matrix3DUtils::scaleZ(_transform, value);
    updateTransforms();
}

float Pivot3D::getScaleX() const {
    Matrix3DUtils::getRight(_transform, _tempVec30);
    return _tempVec30.length();
}

float Pivot3D::getScaleY() const {
    Matrix3DUtils::getUp(_transform, _tempVec30);
    return _tempVec30.length();
}

float Pivot3D::getScaleZ() const {
    Matrix3DUtils::getDir(_transform, _tempVec30);
    return _tempVec30.length();
}

void Pivot3D::setTranslation(float x, float y, float z, bool local) {
    Matrix3DUtils::setTranslation(_transform, x, y, z);
    updateTransforms();
}

void Pivot3D::setTranslation(const Vector3D &pos, bool local) {
    setTranslation(pos.x, pos.y, pos.z, local);
    updateTransforms();
}

void Pivot3D::translateX(float distance, bool local) {
    Matrix3DUtils::translateX(local ? _transform : getWorld(), distance);
    updateTransforms();
}

void Pivot3D::translateY(float distance, bool local) {
    Matrix3DUtils::translateY(local ? _transform : getWorld(), distance);
    updateTransforms();
}

void Pivot3D::translateZ(float distance, bool local) {
    Matrix3DUtils::translateZ(local ? _transform : getWorld(), distance);
    updateTransforms();
}

void Pivot3D::translateAxis(float distance, float x, float y, float z) {
    _tempVec30.setTo(x, y, z, 1.0f);
    Matrix3DUtils::translateAxis(_transform, distance, _tempVec30);
    updateTransforms();
}

void Pivot3D::translateAxis(float distance, const Vector3D &axis) {
    Matrix3DUtils::translateAxis(_transform, distance, axis);
    updateTransforms();
}

void Pivot3D::copyTransformFrom(Pivot3D *source, bool local) {
    if (local) {
        _transform.copyFrom(source->getTransform());
    } else {
        setWorld(source->getWorld());
    }
    updateTransforms();
}

void Pivot3D::resetTransform() {
    _transform.identity();
    updateTransforms();
}

float Pivot3D::getX() {
    _transform.copyColumnTo(3, _tempVec30);
    return _tempVec30.x;
}

float Pivot3D::getY() {
    _transform.copyColumnTo(3, _tempVec30);
    return _tempVec30.y;
}

float Pivot3D::getZ() {
    _transform.copyColumnTo(3, _tempVec30);
    return _tempVec30.z;
}

void Pivot3D::setX(float value) {
    _transform.copyColumnTo(3, _tempVec30);
    _tempVec30.x = value;
    _transform.copyColumnFrom(3, _tempVec30);
    updateTransforms();
}

void Pivot3D::setY(float value) {
    _transform.copyColumnTo(3, _tempVec30);
    _tempVec30.y = value;
    _transform.copyColumnFrom(3, _tempVec30);
    updateTransforms();
}

void Pivot3D::setZ(float value) {
    _transform.copyColumnTo(3, _tempVec30);
    _tempVec30.z = value;
    _transform.copyColumnFrom(3, _tempVec30);
    updateTransforms();
}

void Pivot3D::getRight(Vector3D &dest, bool local) {
    Matrix3DUtils::getRight(local ? _transform : getWorld(), dest);
}

void Pivot3D::getLeft(Vector3D &dest, bool local) {
    Matrix3DUtils::getLeft(local ? _transform : getWorld(), dest);
}

void Pivot3D::getUP(Vector3D &dest, bool local) {
    Matrix3DUtils::getUp(local ? _transform : getWorld(), dest);
}

void Pivot3D::getDown(Vector3D &dest, bool local) {
    Matrix3DUtils::getDown(local ? _transform : getWorld(), dest);
}

void Pivot3D::getFront(Vector3D &dest, bool local) {
    Matrix3DUtils::getDir(local ? _transform : getWorld(), dest);
}

void Pivot3D::getBackward(Vector3D &dest, bool local) {
    Matrix3DUtils::getBackward(local ? _transform : getWorld(), dest);
}

void Pivot3D::localToGlobal(Vector3D &dest, const Vector3D &src) {
    Matrix3DUtils::transformVector(getWorld(), src, dest);
}

void Pivot3D::localToGlobalVector(Vector3D &dest, const Vector3D &src) {
    Matrix3DUtils::deltaTransformVector(getWorld(), src, dest);
}

void Pivot3D::globalToLocal(Vector3D &dest, const Vector3D &src) {
    Matrix3DUtils::transformVector(getInvWorld(), src, dest);
}

void Pivot3D::globalToLocalVector(Vector3D &dest, const Vector3D &src) {
    Matrix3DUtils::deltaTransformVector(getInvWorld(), src, dest);
}

Matrix3D& Pivot3D::getWorld() {
    
    if (_dirty) {
        _transform.copyToMatrix3D(_world);
        if (_parent && _parent != _scene) {
            _world.append(_parent->getWorld());
        }
        _dirty    = false;
        _dirtyInv = true;
    }
    
    return _world;
}

void Pivot3D::setWorld(const Matrix3D &mt) {
    _transform.copyFrom(mt);
    if (_parent) {
        _transform.append(_parent->getInvWorld());
    }
    updateTransforms();
}

Matrix3D& Pivot3D::getInvWorld() {
    if (_dirtyInv || _dirtyInv) {
        _invWorld.copyFrom(getWorld());
        _invWorld.invert();
        _dirtyInv = false;
    }
    return _invWorld;
}

void Pivot3D::updateTransforms(bool includeChildren) {
    _updateTransformEvent.reset();
    dispatchEvent(_updateTransformEvent);
    
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->updateTransforms(includeChildren);
        }
        _dirtyInv = true;
        _dirty    = true;
    }
}

std::vector<Pivot3D*>& Pivot3D::getChildren() {
    return _children;
}

Pivot3D* Pivot3D::getParent() {
    return _parent;
}

void Pivot3D::setParent(Pivot3D *parent) {
    if (parent == _parent) {
        return;
    }
    if (_parent) {
        auto iter = std::find(_parent->getChildren().begin(), _parent->getChildren().end(), this);
        if (iter != _parent->getChildren().end()) {
            _parent->getChildren().erase(iter);
            _removedEvent.reset();
            dispatchEvent(_removedEvent);
        }
    }
    _parent = parent;
    if (_parent) {
        _parent->getChildren().push_back(this);
        updateTransforms(true);
        _addedEvent.reset();
        dispatchEvent(_addedEvent);
    }
    
    if (!_inScene) {
        // 未在场景中
        if (_parent) {
            Scene *scene = dynamic_cast<Scene*>(_parent);
            if (scene) {
                addedToScene(scene);
            } else if (_parent->getInScene()) {
                addedToScene(_parent->getScene());
            }
        }
    } else {
        // 在场景中
        if (!_parent) {
            removedFromScene();
        } else {
            Scene *scene = dynamic_cast<Scene*>(_parent);
            if (!scene && !_parent->getInScene()) {
                removedFromScene();
            }
        }
    }
}

void Pivot3D::addedToScene(Scene *scene) {
    _scene = scene;
    _scene->addToScene(this, _updatable, _drable);
    _inScene = true;
    _addedToSceneEvent.reset();
    dispatchEvent(_addedToSceneEvent);
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->addedToScene(_scene);
    }
}

void Pivot3D::removedFromScene() {
    _scene->removeFromScene(this, true, _drable);
    _scene = nullptr;
    _inScene = false;
    
    _removedFromSceneEvent.reset();
    dispatchEvent(_removedFromSceneEvent);
    
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->removedFromScene();
    }
    
}

void Pivot3D::addChildAt(Pivot3D *pivot, int index, bool useGlobalSpace) {
    addChild(pivot, useGlobalSpace);
    // stupid methodd
    auto iter = std::find(_children.begin(), _children.end(), pivot);
    _children.erase(iter);
    _children.insert(_children.begin() + index, pivot);
}

void Pivot3D::addChild(Pivot3D *pivot, bool useGlobalSpace) {
    if (pivot->getParent() == this || pivot == this) {
        return;
    }
    if (useGlobalSpace == false) {
        pivot->setParent(this);
    } else {
        pivot->getWorld().copyToMatrix3D(pivot->getTransform());
        Matrix3DUtils::invert(getWorld(), _invWorld);
        pivot->setParent(this);
        pivot->getTransform().append(_invWorld);
        pivot->updateTransforms();
    }
}

void Pivot3D::removeChild(Pivot3D *pivot) {
    pivot->setParent(nullptr);
}

Pivot3D* Pivot3D::getChildByName(const std::string &name, int startIndex, bool includeChildren) {
    
    for (auto iter = _children.begin() + startIndex; iter != _children.end(); iter++) {
        if ((*iter)->name == name) {
            return (*iter);
        }
    }
    
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            Pivot3D* child = (*iter)->getChildByName(name, startIndex, includeChildren);
            if (child) {
                return child;
            }
        }
    }
    
    return nullptr;
}

// TODO
void Pivot3D::gotoAndStop(float frame) {
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->gotoAndStop(frame);
    }
    _isPlaying = false;
    setCurrentFrame(frame);
}

void Pivot3D::gotoAndPlay(float frame, AnimationType type) {
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->gotoAndPlay(frame);
    }
    _isPlaying = true;
    setCurrentFrame(frame);
}

float Pivot3D::getCurrentFrame() {
    return _currentFrame;
}

void Pivot3D::setCurrentFrame(float value) {
    _currentFrame = value;
}

void Pivot3D::play(AnimationType type) {
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->play(type);
    }
    _animationType = type;
    _isPlaying = true;
}

void Pivot3D::stop() {
    for (auto iter = _children.begin(); iter != _children.end(); iter++) {
        (*iter)->stop();
    }
    _isPlaying = false;
}

void Pivot3D::prevFrame(float advancedTime) {
    if (_frameSpeed > 0) {
        nextFrame(advancedTime);
        return;
    }
    _currentFrame += _frameSpeed * (advancedTime / _frameSpeed);
    bool animComplete = false;
    if (_currentFrame < _from) {
        switch (_animationType) {
            case AnimationType::LOOP:
                animComplete = true;
                _currentFrame = _to;
                break;
            case AnimationType::STOP:
                animComplete = false;
                _currentFrame = _from;
                stop();
                break;
            case AnimationType::PING_PONG:
                animComplete = true;
                _currentFrame = _from;
                _frameSpeed *= -1;
                break;
            default:
                break;
        }
    }
    setCurrentFrame(_currentFrame);
    if (animComplete) {
        _animationCompleteEvent.reset();
        dispatchEvent(_animationCompleteEvent);
    }
}

void Pivot3D::nextFrame(float advancedTime) {
    if (_frameSpeed < 0) {
        prevFrame(advancedTime);
        return;
    }
    _currentFrame += _frameSpeed * (advancedTime / _fpsSpeed);
    bool animComplete = false;
    if (_currentFrame > _to - 1) {
        switch (_animationType) {
            case AnimationType::LOOP:
                animComplete = true;
                _currentFrame = 0;
                break;
            case AnimationType::STOP:
                animComplete = true;
                _currentFrame = _to - 1;
                stop();
                break;
            case AnimationType::PING_PONG:
                animComplete = true;
                _currentFrame = _to - 1;
                _frameSpeed *= -1;
                break;
            default:
                break;
        }
    }
    setCurrentFrame(_currentFrame);
    if (_currentFrame) {
        _animationCompleteEvent.reset();
        dispatchEvent(_animationCompleteEvent);
    }
}

void Pivot3D::update(float advancedTime, bool includeChildren) {
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->update(advancedTime, includeChildren);
        }
    }
    _enterFrameEvent.reset();
    dispatchEvent(_enterFrameEvent);
    if (_isPlaying) {
        nextFrame(advancedTime);
    }
    _exitFrameEvent.reset();
    dispatchEvent(_exitFrameEvent);
}

Scene* Pivot3D::getScene() {
    return _scene;
}

void Pivot3D::show() {
    _visible = true;
}

void Pivot3D::hide() {
    _visible = false;
}

void Pivot3D::draw(bool includeChildren, Material3D* shader) {
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->draw(includeChildren, shader);
        }
    }
}

void Pivot3D::drawDepth(bool includeChildren, Material3D* shader) {
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->drawDepth(includeChildren, shader);
        }
    }
}

bool Pivot3D::inView() {
    return true;
}

void Pivot3D::setLayer(int layer, bool includeChildren ) {
    if (_scene && layer != _layer) {
        _scene->removeFromScene(this, false, _drable);
        _layer = layer;
        _scene->addToScene(this, false, _drable);
    } else {
        _layer = layer;
    }
    
    if (includeChildren) {
        for (auto iter = _children.begin(); iter != _children.end(); iter++) {
            (*iter)->setLayer(layer, includeChildren);
        }
    }
}

bool Pivot3D::getUpdatable() {
    return _updatable;
}

void Pivot3D::setUpdatable(bool value) {
    _updatable = value;
}

bool Pivot3D::getDrable() {
    return _drable;
}

void Pivot3D::setDrable(bool value) {
    _drable = value;
}

NS_MONKEY_END

//
//  DisplayObject.cpp
//  Opengl2D
//
//  Created by Neil on 6/9/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/entities/DisplayObject.h"
#include "core/event/TouchEvent.h"
#include "core/material/Geometry3D.h"
#include "2d/scene/Scene2D.h"
#include "App.h"

NS_MONKEY_BEGIN

DisplayObject::DisplayObject() :
Pivot3D(),
_geometry(nullptr),
_blendMode(BlendMode::NORMAL),
_alpha(1.0f),
_width(0.0f),
_height(0.0f),
_boundsDirty(true),
_touchIn(false)
{
    _anchorPoint.setTo(0, 0);
    _drable       = true;
    _updatable    = true;
    enableMouse(false);
}

DisplayObject::~DisplayObject() {
    if (_geometry) {
        delete _geometry;
    }
}

void DisplayObject::parent(DisplayObject *parent) {
    if (_parent) {
        setParent(nullptr);
    }
    _parent = parent;
}

void DisplayObject::setAlpha(float value) {
    _alpha = value;
}

float DisplayObject::getAlpha() {
    return _alpha;
}

void DisplayObject::setBlendMode(BlendMode mode) {
    _blendMode = mode;
    switch (_blendMode) {
        case BlendMode::ADD:
            _srcFactor = GL_ONE;
            _dstFactor = GL_ONE;
            break;
        case BlendMode::ALPHA:
            _srcFactor = GL_SRC_ALPHA;
            _dstFactor = GL_ONE_MINUS_SRC_ALPHA;
            break;
        case BlendMode::ALPHA_PREMULTIPILED:
            _srcFactor = GL_ONE;
            _dstFactor = GL_ONE_MINUS_SRC_ALPHA;
            break;
        case BlendMode::MULTIPLE:
            _srcFactor = GL_DST_COLOR;
            _dstFactor = GL_ONE_MINUS_SRC_ALPHA;
            break;
        case BlendMode::NORMAL:
            _srcFactor = GL_ONE;
            _dstFactor = GL_ZERO;
            break;
        case BlendMode::SCREEN:
            _srcFactor = GL_ONE;
            _dstFactor = GL_ONE_MINUS_SRC_COLOR;
            break;
        default:
            break;
    }
}

BlendMode DisplayObject::getBlendMode() {
    return _blendMode;
}


void DisplayObject::setGPUStats() {
    if (_blendMode != BlendMode::NORMAL) {
        glBlendFunc(_srcFactor, _dstFactor);
    }
}

void DisplayObject::disableGPUStats() {
    if (_blendMode != BlendMode::NORMAL) {
        glBlendFunc(GL_ONE, GL_ZERO);
    }
}

void DisplayObject::updateBounds(bool force) {
    
    if (!_boundsDirty && !force) {
        return;
    }
    
    _boundsDirty = false;
    
    float dw = _width  * _anchorPoint.x;
    float dh = _height * _anchorPoint.y;
    
    float vertices[12] = {
        -dw,             -_height + dh,      0.0f,
        -dw,             dh,                 0.0f,
        _width - dw,     -_height + dh,      0.0f,
        _width - dw,     dh,                 0.0f
    };
    
    _min.setTo(MAX_B, MAX_B);
    _max.setTo(MIN_B, MIN_B);
    
    for (int i = 0; i < 4; i++) {
        _tempVec30.setTo(vertices[i * 3 + 0], vertices[i * 3 + 1], 0.0f, 1.0f);
        Matrix3DUtils::transformVector(getWorld(), _tempVec30, _tempVec30);
        if (_min.x > _tempVec30.x) {
            _min.x = _tempVec30.x;
        }
        if (_min.y > _tempVec30.y) {
            _min.y = _tempVec30.y;
        }
        if (_max.x < _tempVec30.x) {
            _max.x = _tempVec30.x;
        }
        if (_max.y < _tempVec30.y) {
            _max.y = _tempVec30.y;
        }
    }
}

float DisplayObject::getWidth() {
    updateBounds();
    return absf(_max.x - _min.x);
}

float DisplayObject::getHeight() {
    updateBounds();
    return absf(_max.y - _min.y);
}

Vector2D DisplayObject::getMin() {
    updateBounds(true);
    return _min;
}

Vector2D DisplayObject::getMax() {
    updateBounds(true);
    return _max;
}

bool DisplayObject::hitTestPoint(float x, float y) {
    
    _tempVec30.setTo(x, -y, 0.0f, 1.0f);
    Matrix3DUtils::transformVector(getInvWorld(), _tempVec30, _tempVec30);
    
    float dw =  getWidth()  * _anchorPoint.x;
    float dh = -getHeight() * _anchorPoint.y;
    float l  = -dw;
    float r  =  _width  - dw;
    float b  = -_height - dh;
    float t  = dh;
    
    if (_tempVec30.x < l || _tempVec30.x > r || _tempVec30.y > t || _tempVec30.y < b) {
        return false;
    }
    
    return true;
}

bool DisplayObject::hitTestPoint(const Point2D &point) {
    return hitTestPoint(point.x, point.y);
}

void DisplayObject::setAnchor(float x, float y) {
    _anchorPoint.setTo(x, y);
}

Vector2D DisplayObject::getAnchor() {
    return _anchorPoint;
}

bool DisplayObject::inView() {
    // 屏幕宽高
    float screenWidth  = App::getInstance()->getWidth();
    float screenHeight = App::getInstance()->getHeight();
    // 取矩形区域来进行inView判定、不实时计算宽高。
    float w = getHeight() > getWidth() ? getHeight() : getWidth();
    
    float dw = w  * _anchorPoint.x;
    float dh = w  * _anchorPoint.y;
    // 获取坐标
    _transform.copyColumnTo(3, _tempVec30);
    float x = _tempVec30.x  - dw;
    float y = -_tempVec30.y - dh;
    
    if (x > screenWidth || x + w < 0 || y > screenHeight || y + w < 0) {
        return false;
    }
    
    return true;
}

Geometry3D* DisplayObject::getGeometry3d() {
    return _geometry;
}

void DisplayObject::setLayer(int layer, bool includeChildren) {
    
}

void DisplayObject::dispatchEvent(monkey::Event &event) {
    EventDispatcher::dispatchEvent(event);
    // 对父级进行冒泡
    DisplayObject *tp = dynamic_cast<DisplayObject*>(getParent());
    TouchEvent    *te = dynamic_cast<TouchEvent*>(&event);
    if (tp && te) {
        tp->acceptTouchEvent(*te);
    }
}

bool DisplayObject::acceptTouchEvent(TouchEvent &event) {
    
    if (!_mouseEnabled) {
        return false;
    }
    // 没有该事件并且也没有 TOUCH_OUT TOUCH_HIT RIGHT_MOUSE_CLICK MIDDLE_MOUSE_CLICK
    if (!hasEventListener(event.type) &&
        !hasEventListener(TouchEvent::TOUCH_IN) &&
        !hasEventListener(TouchEvent::TOUCH_OUT) &&
        !hasEventListener(TouchEvent::TOUCH_HIT) &&
        !hasEventListener(TouchEvent::RIGHT_MOUSE_CLICK) &&
        !hasEventListener(TouchEvent::MIDDLE_MOUSE_CLICK)
        ) {
        return false;
    }
    
    // 多点触控
    bool isIn = false;
    for (int i = 0; i < event.size; i++) {
        isIn = hitTestPoint(event.points[i].x, event.points[i].y);
        if (!isIn && event.size > 1) { // 多点触控，如果多点都未在显示对象内部，则视为未选中
            _touchBegan = false;
            _touchIn    = false;
            return false;
        }
    }
    // TOUCH_OUT事件
    if (_touchIn && !isIn) {
        if (hasEventListener(TouchEvent::TOUCH_OUT)) {
            TouchEvent touchOutEvent(TouchEvent::TOUCH_OUT, true, event.points, event.size);
            dispatchEvent(touchOutEvent);
            _touchIn    = false;
            _touchBegan = false;
            return true;  // TOUCH_OUT事件，事件接受成功。
        }
    }
    // TOUCH_IN事件
    if (!_touchIn && isIn) {
        if (hasEventListener(TouchEvent::TOUCH_IN)) {
            TouchEvent touchInEvent(TouchEvent::TOUCH_IN, true, event.points, event.size);
            dispatchEvent(touchInEvent);
        }
    }
    // not in, 不派发事件
    if (!isIn) {
        _touchIn    = false;
        _touchBegan = false;
        return false;
    }
    // Touch_Began
    if (event.type == TouchEvent::TOUCH_BEGAN || event.type == TouchEvent::RIGHT_MOUSE_DOWN || event.type == TouchEvent::MIDDLE_MOUSE_DOWN) {
        _touchBegan = true;
    }
    // in 派发事件
    dispatchEvent(event);
    // click事件
    if (_touchBegan && event.type == TouchEvent::TOUCH_END && hasEventListener(TouchEvent::TOUCH_HIT)) {
        TouchEvent touchHitEvent(TouchEvent::TOUCH_HIT, true, event.points, event.size);
        dispatchEvent(touchHitEvent);
    } else if (_touchBegan && event.type == TouchEvent::RIGHT_MOUSE_UP && hasEventListener(TouchEvent::RIGHT_MOUSE_CLICK)) {
        TouchEvent rightClickEvnet(TouchEvent::RIGHT_MOUSE_CLICK, true, event.points, event.size);
        dispatchEvent(rightClickEvnet);
    } else if (_touchBegan && event.type == TouchEvent::MIDDLE_MOUSE_UP && hasEventListener(TouchEvent::MIDDLE_MOUSE_CLICK)) {
        TouchEvent middleClickEvent(TouchEvent::MIDDLE_MOUSE_CLICK, true, event.points, event.size);
        dispatchEvent(middleClickEvent);
    }
    _touchIn = true;
    return true;
}

NS_MONKEY_END
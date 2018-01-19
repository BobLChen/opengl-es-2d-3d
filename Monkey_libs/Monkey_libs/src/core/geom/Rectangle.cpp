//
//  Rectangle.cpp
//  TestOpenglES
//
//  Created by Neil on 27/8/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/geom/Vector2D.h"
#include "core/geom/Rectangle.h"

#include "platform/PlatformMacros.h"

NS_MONKEY_BEGIN

Rectangle::Rectangle() {
    
}

Rectangle::Rectangle(float x, float y, float width, float height) {
    set(x, y, width, height);
}

Rectangle::~Rectangle() {
    
}

float Rectangle::getX() const {
    return _x;
}

float Rectangle::getY() const {
    return _y;
}

float Rectangle::getHeight() const {
    return _height;
}

float Rectangle::getWidth() const {
    return _width;
}

float Rectangle::getTop() const {
    return _top;
}

float Rectangle::getLeft() const {
    return _left;
}

float Rectangle::getRight() const {
    return _right;
}

float Rectangle::getBottom() const {
    return _bottom;
}

bool Rectangle::contains(float x, float y) const {
    if (x < _left || x > _right || y < _top || y > _bottom) {
        return false;
    }
    return true;
}

bool Rectangle::containsPoint(const Vector2D &point) const {
    return contains(point.x, point.y);
}

bool Rectangle::containsRect(const Rectangle &rect) const {
    if (rect.getLeft() >= _left && rect.getRight() <= _right && rect.getTop() >= _top && rect.getBottom() <= _bottom) {
        return true;
    }
    return false;
}

bool Rectangle::equals(const Rectangle &rect) const {
    if (_left == rect.getLeft() && _right == rect.getRight() && _top == rect.getTop() && _bottom == rect.getBottom()) {
        return true;
    }
    return false;
}

float Rectangle::getCenterX() const {
    return _centerX;
}

float Rectangle::getCenterY() const {
    return _centerY;
}

bool Rectangle::intersects(const Rectangle &rect) const {
    
    float cx0 = getCenterX();
    float cy0 = getCenterY();
    float cx1 = rect.getCenterX();
    float cy1 = rect.getCenterY();
    
    float w = cx1 - cx0;
    float h = cy1 - cy0;
    
    w = w < 0 ? -w : w;
    h = h < 0 ? -h : h;
    
    if (w > _width / 2 + rect.getWidth() / 2) {
        return false;
    }
    
    if (h > _height / 2 + rect.getHeight() / 2) {
        return false;
    }
    
    return true;
}

void Rectangle::copyFrom(const Rectangle &rect) {
    _x      = rect.getX();
    _y      = rect.getY();
    _width  = rect.getWidth();
    _height = rect.getHeight();
    _left   = _x;
    _right  = _x + _width;
    _top    = _y;
    _bottom = _y + _height;
}

void Rectangle::set(const float x, const float y, const float width, const float height) {
    _x      = x;
    _y      = y;
    _width  = width;
    _height = height;
    _left   = _x;
    _right  = _x + _width;
    _top    = _y;
    _bottom = _y + _height;
    _centerX = _x + width / 2;
    _centerY = _y + height / 2;
}

NS_MONKEY_END
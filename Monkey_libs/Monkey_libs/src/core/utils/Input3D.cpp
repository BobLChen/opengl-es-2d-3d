//
//  Input3D.cpp
//  Monkey_libs
//
//  Created by Neil on 4/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "core/utils/Input3D.h"

NS_MONKEY_BEGIN

std::vector<unsigned int> Input3D::_ups   = std::vector<unsigned int>(300);
std::vector<unsigned int> Input3D::_downs = std::vector<unsigned int>(300);
std::vector<unsigned int> Input3D::_hits  = std::vector<unsigned int>(300);

int Input3D::_keyCode   = 0;
float Input3D::_deltaX  = 0;
float Input3D::_deltaY  = 0;
int Input3D::_deltaMove = 0;
int Input3D::_mouseUp   = 0;
int Input3D::_mouseHit  = 0;
int Input3D::_mouseDown = 0;
int Input3D::_rightMouseUp   = 0;
int Input3D::_rightMouseHit  = 0;
int Input3D::_rightMouseDown = 0;
int Input3D::_middleMouseUp  = 0;
int Input3D::_middleMouseDown= 0;
int Input3D::_middleMouseHit = 0;
int Input3D::_mouseDoubleClick = 0;
float Input3D::_stageX = 0.0f;
float Input3D::_stageY = 0.0f;
float Input3D::_mouseX = 0.0f;
float Input3D::_mouseY = 0.0f;
float Input3D::_mouseXSpeed = 0.0f;
float Input3D::_mouseYSpeed = 0.0f;
bool  Input3D::_mouseUpdated= false;
int   Input3D::_currFrame   = 0;
float Input3D::_movementX   = 0.0f;
float Input3D::_movementY   = 0.0f;

/*
 * TODO:暂时只支持单点触控
 */

void Input3D::mouseMove(Point2D *points, int num) {
    _stageX = points[0].x;
    _stageY = points[0].y;
}

void Input3D::mouseUP(Point2D *points, int num) {
    _mouseDown = 0;
    _mouseHit  = 0;
    _mouseUp   = _currFrame + 1;
}

void Input3D::mouseDown(Point2D *points, int num) {
    _mouseDown = 1;
    _mouseUp   = 0;
    _mouseHit  = _currFrame + 1;
}

void Input3D::mouseWheel(float deltaX, float deltaY) {
    _deltaX = deltaX;
    _deltaY = deltaY;
    _deltaMove = _currFrame + 1;
}

void Input3D::rightMouseDown(Point2D *points, int num) {
    _rightMouseDown = 1;
    _rightMouseUp   = 0;
    _rightMouseHit  = _currFrame + 1;
}

void Input3D::rightMouseUp(Point2D *points, int num) {
    _rightMouseDown = 0;
    _rightMouseUp   = _currFrame + 1;
    _rightMouseHit  = 0;
}

void Input3D::middleMouseDown(Point2D *points, int num) {
    _middleMouseDown = 1;
    _middleMouseUp   = 0;
    _middleMouseHit  = _currFrame + 1;
}

void Input3D::middleMouseUp(Point2D *points, int num) {
    _middleMouseDown = 0;
    _middleMouseUp   = _currFrame + 1;
    _middleMouseHit  = 0;
}

void Input3D::doubleClick(Point2D *points, int num) {
    _mouseDoubleClick = _currFrame + 1;
}

void Input3D::keyDown(KeyboardEvent::KeyCode keycode) {
    if (!_downs[keycode]) {
        _hits[keycode] = _currFrame + 1;
    }
    _downs[keycode] = 1;
    _keyCode = keycode;
}

void Input3D::keyUp(KeyboardEvent::KeyCode  keycode) {
    _downs[keycode] = 0;
    _hits[keycode]  = 0;
    _ups[keycode]   = _currFrame + 1;
    _keyCode        = 0;
}

int Input3D::getKeycode() {
    return _keyCode;
}

bool Input3D::isKeydown(KeyboardEvent::KeyCode keycode) {
    return _downs[keycode] > 0;
}

bool Input3D::isKeyUp(int keycode) {
    return _ups[keycode] == _currFrame;
}

bool Input3D::isKeyHit(int keycode) {
    return _hits[keycode] == _currFrame;
}

bool Input3D::isMouseDoubleClick() {
    return _mouseDoubleClick == _currFrame;
}

float Input3D::getDeltaX() {
    return _deltaX;
}

float Input3D::getDeltaY() {
    return _deltaY;
}

float Input3D::getMouseX() {
    return _mouseX;
}

float Input3D::getMouseY() {
    return _mouseY;
}

float Input3D::getMouseXSpeed() {
    return _mouseXSpeed;
}

float Input3D::getMouseYSpeed() {
    return _mouseYSpeed;
}

bool Input3D::isMouseHit() {
    return _mouseHit == _currFrame;
}

bool Input3D::isMouseUP() {
    return _mouseUp == _currFrame;
}

bool Input3D::isMouseDown() {
    return _mouseDown > 0;
}

bool Input3D::isRightMouseHit() {
    return _rightMouseHit == _currFrame;
}

bool Input3D::isRightMouseDown() {
    return _rightMouseDown > 0;
}

bool Input3D::isRightMouseUp() {
    return _rightMouseUp == _currFrame;
}

bool Input3D::isMiddleMouseHit() {
    return _middleMouseHit == _currFrame;
}

bool Input3D::isMiddleMouseUp() {
    return _middleMouseUp == _currFrame;
}

bool Input3D::isMiddleMouseDown() {
    return _middleMouseDown > 0;
}

float Input3D::getMovementX() {
    return _movementX;
}

float Input3D::getMovementY() {
    return _movementY;
}

void Input3D::clear() {
    _movementX = 0;
    _movementY = 0;
    _deltaX    = 0;
    _deltaY    = 0;
}

void Input3D::update() {
    _currFrame++;
    if (_mouseUpdated) {
        _mouseXSpeed = _stageX - _mouseX;
        _mouseYSpeed = _stageY - _mouseY;
        _mouseUpdated = false;
    } else {
        _mouseXSpeed = 0.0f;
        _mouseYSpeed = 0.0f;
    }
    _mouseX = _stageX;
    _mouseY = _stageY;
}

NS_MONKEY_END
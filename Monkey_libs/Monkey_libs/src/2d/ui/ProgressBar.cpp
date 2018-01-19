//
//  ProgressBar.cpp
//  Monkey_libs
//
//  Created by Neil on 26/10/14.
//  Copyright (c) 2014 neil. All rights reserved.
//

#include "2d/ui/ProgressBar.h"

NS_MONKEY_BEGIN

ProgressBar::ProgressBar() :
Widget(),
_direction(ProgressBar::Direction::RIGHT),
_percent(0.0f),
_renderer(nullptr),
_totalLength(100.0f),
_baseWidth(0.0f)
{
    
}

ProgressBar::~ProgressBar() {
    
}

void ProgressBar::initWithTexture(const std::string &textureName, Type type, Direction direction) {
    
    if (_renderer) {
        removeWidget(_renderer);
        delete _renderer;
        _renderer = nullptr;
    }
    
    switch (type) {
        case Type::TEXTURE:
            _renderer = Image::create(textureName);
            break;
        case Type::TEXTURE_FRAME:
            _renderer = Image::createFrameTexture(textureName);
            break;
        default:
            break;
    }
    
    addWidget(_renderer);
    
    _baseWidth = _renderer->getWidth();
    setDirection(direction);
}

ProgressBar::Direction ProgressBar::getDirection() const {
    return _direction;
}

void ProgressBar::setDirection(ProgressBar::Direction direction) {
    _direction = direction;
    
    if (!_renderer) {
        return;
    }
    
    switch (direction) {
        case Direction::LEFT:
            _renderer->setAnchor(1.0f, 0.5f);
            break;
        case Direction::RIGHT:
            _renderer->setAnchor(0.0f, 0.5f);
            break;
        default:
            break;
    }
    
}

void ProgressBar::setPercent(float percent) {
    _percent = percent;
    if (!_renderer) {
        return;
    }
    float scale = _percent * _totalLength / _baseWidth;
    _renderer->setScaleX(scale);
}

float ProgressBar::getPercent() const {
    return _percent;
}

void ProgressBar::setTotalLength(float value) {
    _totalLength = value;
    setPercent(_percent);
}

float ProgressBar::getTotalLength() const {
    return _totalLength;
}

void ProgressBar::draw(bool includeChildren, Material3D* shader) {
    
    if (!_renderer) {
        return;
    }
    
    Widget::draw(includeChildren, shader);
}

NS_MONKEY_END